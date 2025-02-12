/*
 * http_ipc.c                                                            
 *    Handles the file descriptor passing.  Should work under BSD and    
 *   SYSV.                                                               
 *
 * All code contained herein is covered by the Copyright as distributed
 * in the README file in the main directory of the distribution of 
 * NCSA HTTPD.
 *
 * Based (with modifications) on code by W. Richard Stevens, 
 *	in _Advanced Programming in the UNIX Environment_
 *                                                                       
 * 03-06-95  blong
 *    Added #ifdefs to handle not using this at all for machines like 
 *     Linux.
 *
 * 04-17-95  blong
 *    Added NEED_SPIPE with s_pipe from Stevens _Unix Network Programming_
 *     for SVR3.2 systems without socketpair.
 */

#ifndef NO_PASS

#include "httpd.h"

#include <sys/types.h>
#if defined(FD_BSD)
#include <sys/uio.h>
#include <errno.h>
#include <stddef.h>
#elif defined(FD_SYSV)
#ifdef NEED_SPIPE
#define SPX_DEVICE	"/dev/spx"
#include <sys/stream.h>
#endif
#include <stropts.h>
#endif
#include "new.h"

#ifdef FD_SYSV

int pass_fd(int clifd, int fd) {
    char buf[2];

    buf[0] = 0;
    if (fd < 0) {
	buf[1] = -fd;
	if (buf[1] == 0)
	    buf[1] = 1;
    } else {
	buf[1] = 0;
    }

    if (write(clifd, buf, 2) != 2) {
	fprintf(stderr,"pass_fd: write failed\n");
	perror("pass_fd");
	return -1;
    }
    if (fd >= 0)
	if (ioctl(clifd, I_SENDFD, fd) < 0) {
	    fprintf(stderr,"pass_fd: ioctl failed\n");
	    perror("ioctl");
	    return -1;
	}
    return 0;
} 

int recv_fd(int servfd) {
    int  newfd, nread, flag, status;
    char  *ptr, buf[IOBUFSIZE];
    struct strbuf dat;
    struct strrecvfd recvfd;

    status = -1;
    for ( ; ; ) {
	dat.buf = buf;
	dat.maxlen = IOBUFSIZE;
	flag = 0;
	if (getmsg(servfd, NULL, &dat, &flag) < 0) {
	    fprintf(stderr,"httpd:getmsg error recv_fd\n");
	    perror("getmsg");
	    exit(1);
	}
	nread = dat.len;
	if (nread == 0) {
	    fprintf(stderr,"httpd: connection closed by server\n");
	    exit(1);
	}
	
	for (ptr = buf; ptr < &buf[nread]; ) {
	    if (*ptr++ == 0) {
		if (ptr != &buf[nread-1]) {
		    fprintf(stderr,"httpd: message format error recv_fd\n");
		    perror("recv_fd");
		    exit(1);
		}
		status = *ptr & 255;
		if (status == 0) {
		    if (ioctl(servfd, I_RECVFD, &recvfd) < 0)
			return -1;
		    newfd = recvfd.fd;
		} else 
		    newfd = -status;
		nread -= 2;
	    }
	}
	if (status >= 0)
	    return (newfd);
    }
} 

#ifdef NEED_SPIPE

int s_pipe(int fd[2]) {
  struct strfdinsert ins;
  queue_t  *pointer;

  /*
   * First open the stream clone device "/dev/spx" twice,
   * obtaining the two file descriptors.
   */

  if ((fd[0] = open(SPX_DEVICE, O_RDWR)) < 0) 
    return -1;
  if ((fd[1] = open(SPX_DEVICE, O_RDWR)) < 0)
    return -1;

  /* 
   * Now link these two streams together with an I_FDINSERT ioctl
   */

  ins.ctlbuf.buf = (char *) &pointer;
  ins.ctlbuf.maxlen = sizeof(queue_t *);
  ins.ctlbuf.len = sizeof(queue_t *);

  ins.databuf.buf = (char *) 0;
  ins.databuf.len = -1;
  ins.databuf.maxlen = 0;

  ins.fildes = fd[1];
  ins.flags = 0;
  ins.offset = 0;

  if (ioctl(fd[0], I_FDINSERT, (char *) &ins) < 0) {
    close(fd[0]);
    close(fd[1]);
    return -1;
  }

  return 0;

}

#endif /* NEED_SPIPE */

#endif /* FD_SYSV */

#ifdef FD_BSD

#ifdef FD_BSDRENO
static struct cmsghdr *cmptr = NULL;
#define CONTROLLEN (sizeof(struct cmsghdr) + sizeof(int))
#endif

int pass_fd(int clifd, int fd) {
  struct iovec iov[1];
  struct msghdr msg;
  char  buf[2];

  iov[0].iov_base = buf;
  iov[0].iov_len = 2;
  msg.msg_iov = iov;
  msg.msg_iovlen = 1;
  msg.msg_name = NULL;
  msg.msg_namelen = 0;
  if (fd < 0) {
#ifdef FD_BSDRENO
    msg.msg_control = NULL;
    msg.msg_controllen = 0;
#else
    msg.msg_accrights = NULL;
    msg.msg_accrightslen = 0;
#endif
    buf[1] = -fd;
    if (buf[1] == 0)
      buf[1] = 1;
  } else {
#ifdef FD_BSDRENO
    if (cmptr == NULL && (cmptr = malloc(CONTROLLEN)) == NULL)
      return -1;
    cmptr->cmsg_level = SOL_SOCKET;
    cmptr->cmsg_type = SCM_RIGHTS;
    cmptr->cmsg_len = CONTROLLEN;
    msg.msg_control = (caddr_t) cmptr;
    msg.msg_controllen = CONTROLLEN;
    *(int *)CMSG_DATA(cmptr) = fd;
#else
    msg.msg_accrights = (caddr_t) &fd;
    msg.msg_accrightslen = sizeof(int);
#endif
    buf[1] = 0;
  }
  buf[0] = 0;

/*  if (write(clifd, buf, 2) != 2)
   return -1; */

  if (sendmsg(clifd, &msg, 0) != 2)
    return -1;
  
  return 0;
}


int recv_fd(int servfd) {
  int  nread, status;
  int newfd = -1;
  char *ptr, buf[IOBUFSIZE];
  struct iovec  iov[1];
  struct msghdr  msg;
  
  status = -1;
  for ( ; ; ) {
    iov[0].iov_base = buf;
    iov[0].iov_len = sizeof(buf);
    msg.msg_iov = iov;
    msg.msg_iovlen = 1;
    msg.msg_name = NULL;
    msg.msg_namelen = 0;
#ifdef FD_BSDRENO
    if (cmptr == NULL && (cmptr = malloc(CONTROLLEN)) == NULL)
      return -1;
    msg.msg_control = (caddr_t) cmptr;
    msg.msg_controllen = CONTROLLEN;
#else
    msg.msg_accrights = (caddr_t) &newfd;
    msg.msg_accrightslen = sizeof(int);
#endif
    
    if ((nread = recvmsg(servfd, &msg, 0)) < 0) {
      fprintf(stderr,"httpd: recvmsg error");
      perror("recvmsg");
      exit(1);
    } else if (nread == 0) {
      fprintf(stderr, "httpd: connection closed by server");
      exit(1);
    }
    
    for (ptr = buf; ptr < &buf[nread]; ) {
      if (*ptr++ == 0) {
	if (ptr != &buf[nread-1]) {
	  fprintf(stderr, "httpd:message format error");
	  exit(1);
	}
	status = *ptr & 255;
	if (status == 0) {
#ifdef FD_BSDRENO
	  if (msg.msg_controllen != CONTROLLEN) 
#else
	    if (msg.msg_accrightslen != sizeof(int)) 
#endif	
	      {
		fprintf(stderr, "httpd: status = 0 but no fd");
		exit(1);
	      }
#ifdef FD_BSDRENO
	  newfd = *(int *)CMSG_DATA(cmptr);
#endif
	} else 
	  newfd = -status;
	  nread -= 2;
      }
    }
    if (nread > 0)
      return -1;
    if (status >= 0)
      return newfd;
  }
}
  

#endif

#endif 
