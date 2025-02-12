/*
 * httpd.h: header for simple (ha! not anymore) http daemon
 *
 * All code contained herein is covered by the Copyright as distributed
 * in the README file in the main directory of the distribution of 
 * NCSA HTTPD.
 *
 */

/* Define one of these according to your system. */
#if defined(SUNOS4)
#define BSD
#undef NO_KILLPG
#undef NO_SETSID
#define FD_BSD
char *crypt(char *pw, char *salt);

#elif defined(SOLARIS2)
#undef BSD
#define NO_KILLPG
#undef NO_SETSID
#define FD_BSD
#define bzero(a,b) memset(a,0,b)
#define getwd(d) getcwd(d,MAX_STRING_LEN)
#define JMP_BUF sigjmp_buf

#elif defined(IRIX)
#undef BSD
#undef NO_KILLPG
#undef NO_SETSID
#define FD_BSD
#define JMP_BUF sigjmp_buf

#elif defined(HPUX)
#undef BSD
#define NO_KILLPG
#undef NO_SETSID
#define FD_BSD
#ifndef _HPUX_SOURCE
#define _HPUX_SOURCE
#endif
#define getwd(d) getcwd(d,MAX_STRING_LEN)
#define JMP_BUF sigjmp_buf

#elif defined(AIX)
#undef BSD
#undef NO_KILLPG
#undef NO_SETSID
#define FD_BSD
#define NEED_SELECT_H
#define JMP_BUF sigjmp_buf

#elif defined(ULTRIX)
#define BSD
#define FD_BSD
#undef NO_KILLPG
#undef NO_SETSID
#define ULTRIX_BRAIN_DEATH
#define NEED_STRDUP
/* If you have Ultrix 4.3, and are using cc, const is broken */
#ifndef __ultrix__ /* Hack to check for pre-Ultrix 4.4 cc */
#define const /* Not implemented */
#endif
#define JMP_BUF sigjmp_buf

#elif defined(OSF1)
#define BSD
#define FD_BSD
#undef NO_KILLPG
#undef NO_SETSID
#define JMP_BUF sigjmp_buf

#elif defined(SEQUENT)
#define BSD
#undef NO_KILLPG
#define NO_SETSID
#define NEED_STRDUP
#define tolower(c) (isupper(c) ? tolower(c) : c)

#elif defined(NeXT)
#define BSD
#define FD_BSD
#undef NO_KILLPG
#define NO_SETSID
#define NEED_STRDUP
#undef _POSIX_SOURCE
#ifndef S_IXUSR
#define S_IXUSR _S_IXUSR
#endif
#ifndef S_IXGRP
#define S_IXGRP 0000010
#endif
#ifndef S_IXOTH
#define S_IXOTH 0000001
#endif
#ifndef S_IRUSR
#define S_IRUSR _S_IRUSR
#endif
#ifndef S_IWUSR
#define S_IWUSR _S_IWUSR
#endif
#ifndef S_IRGRP
#define S_IRGRP 0000040
#endif
#ifndef S_IROTH
#define S_IROTH 0000004
#endif
#ifndef S_IWGRP
#define S_IWGRP 0000020
#endif
#ifndef S_IWOTH
#define S_IWOTH 0000002
#endif
#ifndef S_IRWXU
#define S_IRWXU 0000700
#endif
#ifndef S_IRWXG
#define S_IRWXG 0000070
#endif
#ifndef S_IRWXO
#define S_IRWXO 0000007
#endif
#ifndef S_ISBLK
#define S_ISBLK(m)	(((m)&(_S_IFMT)) == (_S_IFBLK))
#endif
#ifndef S_ISCHR
#define S_ISCHR(m)	(((m)&(_S_IFMT)) == (_S_IFCHR))
#endif
#ifndef S_ISDIR
#define S_ISDIR(m)      (((m)&(_S_IFMT)) == (_S_IFDIR))
#endif
#ifndef S_ISFIFO
#define S_ISFIFO(m)	(((m)&(_S_IFMT)) == (_S_IFIFO))
#endif
#ifndef S_ISREG
#define S_ISREG(m)      (((m)&(_S_IFMT)) == (_S_IFREG))
#endif
#define STDIN_FILENO  0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2
#define waitpid(a,b,c) wait4(a,b,c,NULL)
typedef int pid_t;
typedef int mode_t;
#define JMP_BUF jmp_buf

#elif defined(LINUX)
#define NO_PASS
#undef BSD
#undef NO_KILLPG
#undef NO_SETSID
#undef NEED_STRDUP
#define FD_SET __FD_SET
#define FD_ZERO __FD_ZERO
#define FD_ISSET __FD_ISSET
#define JMP_BUF sigjmp_buf

#elif defined(NETBSD)
#define BSD
#define FD_BSD
#define FD_BSDRENO

#elif defined(SCO)
#undef BSD
#undef NO_KILLPG
#undef NO_SETSID
#define NEED_INITGROUPS

#elif defined(SCO3)
#undef BSD
#define FD_SYSV
#define NEED_SPIPE
#undef NO_KILLPG
#undef NO_SETSID
#define NEED_INITGROUPS
#define CALL_TZSET
#define getwd(d) getcwd(d,MAX_STRING_LEN)
#define JMPBUF sigjmp_buf


#elif defined(CONVEXOS)
#define BSD
#define NEED_STRDUP
#define getwd(d) getcwd(d,MAX_STRING_LEN)

#elif defined(AUX)
#define BSD
#undef NO_KILLPG
#undef NO_SETSID
#define NEED_STRDUP
#ifdef _POSIX_SOURCE
# define JMP_BUF sigjmp_buf
#else
# define siglongjmp longjmp
# define sigsetjmp setjmp
# define JMP_BUF jmp_buf
# define STDIN_FILENO 0
# define STDOUT_FILENO 1
# define STDERR_FILENO 2
#endif

#elif defined(SVR4)
#define NO_KILLPG
#undef  NO_SETSID
#undef NEED_STRDUP
#define NEED_STRCASECMP
#define NEED_STRNCASECMP
#define bzero(a,b) memset(a,0,b)
#define JMP_BUF sigjmp_buf
#define getwd(d) getcwd(d,MAX_STRING_LEN)

#elif defined(__NetBSD__)
#define BSD
#define FD_BSD
#define FD_BSDRENO
#undef NO_KILLPG
#undef NO_SETSID

#elif defined(UTS21)
#undef BSD
#undef NO_KILLPG
#define NO_SETSID
#define NEED_WAITPID
#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2
#define strftime(buf,bufsize,fmt,tm)    ascftime(buf,fmt,tm)
#include <sys/types.h>

#elif defined(APOLLO)
#define BSD
#undef NO_KILLPG
#undef NO_SETSID
#define timezone	_bky_timezone

#elif defined(ATTSVR3)
#define NO_SETSID
#undef BSD
#undef NO_KILLPG
#define NO_STRFTIME
#undef NEED_STRDUP
#undef NEED_STRCASECMP
#undef NEED_STRNCASECMP
#define SIGCHLD SIGCLD
#define STDIN_FILENO fileno(stdin)
#define STDOUT_FILENO fileno(stdout)
#define STDERR_FILENO fileno(stderr)
#ifndef S_ISDIR
#define S_ISDIR(m)    (((m)&(S_IFMT)) == (S_IFDIR))
#endif
#ifndef S_ISREG
#define S_ISREG(m)    (((m)&(S_IFMT)) == (S_IFREG))
#endif
#define lstat stat
#define strftime(buf,bufsize,fmt,tm)    ascftime(buf,fmt,tm)
#define getwd(d) getcwd(d,MAX_STRING_LEN)
#define readlink(a,b,c) -1
typedef int uid_t;
typedef int gid_t;
typedef int pid_t;
extern struct group *getgrnam();
extern char *getenv();

#elif defined(__QNX__)
#define _POSIX_SOURCE
#define NEED_SELECT_H
#define NEED_INITGROUPS
#define wait3(a,b,c) waitpid(-1,a,b)



/* Unknown system - Edit these to match */
#else
/* BSD is whether your system uses BSD calls or System V calls. */
#define BSD
/* NO_KILLPG is set on systems that don't have killpg */
#undef NO_KILLPG
/* NO_SETSID is set on systems that don't have setsid */
#undef NO_SETSID
/* NEED_STRDUP is set on stupid systems that don't have strdup. */
#undef NEED_STRDUP
/* NO_PASS is set on systems that don't allow file descriptor passing */
#undef NO_PASS
/* FD_BSD is set on systems which pass file descriptors in a BSD way */
#undef FD_BSD
/* FD_BSDRENO is for BSD 4.3RENO systems for file descriptor passing */
#undef FD_BSDRENO
/* FD_SYSV is set on systems which pass file descriptor in a SYSV way */
#undef FD_SYSV
/* NEED_SPIPE is set on systems which are using FD_SYSV but don't have
   socketpair */
#undef NEED_SPIPE
/* CALL_TZSET on systems which need to call tzset() before detaching from
   the shell (some systems don't keep environment variables after detach) */
#undef CALL_TZSET
#endif

/* If we haven't set anything about file descriptor passing, set NO_PASS */
#if !defined(FD_BSD) && !defined(FD_SYSV) && !defined(NO_PASS)
#define NO_PASS
#endif

/*
 * The particular directory style your system supports. If you have dirent.h
 * in /usr/include (POSIX) or /usr/include/sys (SYSV), #include 
 * that file and define DIR_TYPE to be dirent. Otherwise, if you have 
 * /usr/include/sys/dir.h, define DIR_TYPE to be direct and include that
 * file. If you have neither, I'm confused.
 */

#include <sys/types.h>

#if !defined(NeXT) && !defined(CONVEXOS) && !defined(APOLLO)
#if defined(ATTSVR3)
#include <malloc.h>
#endif
#include <dirent.h>
#define DIR_TYPE dirent
#else
#include <sys/dir.h>
#define DIR_TYPE direct
#endif

/* ----------------------------- config dir ------------------------------ */

/* Define this to be the default server home dir. Anything later in this
 * file with a relative pathname will have this added.
 */
#define HTTPD_ROOT "/usr/local/etc/httpd"

/* Root of server */
#define DOCUMENT_LOCATION "/usr/local/etc/httpd/htdocs"

/* Max. number of aliases */
#define MAX_ALIASES 20

/* Max. number of security defines */
#define MAX_SECURITY 50

/* Default administrator's address */
#define DEFAULT_ADMIN "[no address given]"

/* 
 * --------- You shouldn't have to edit anything below this line ----------
 *
 * Any modifications to any defaults not defined above should be done in the 
 * respective config. file. 
 *
 */


/* -------------- Port number for server running standalone --------------- */

#define DEFAULT_PORT 80

/* --------- Default user name and group name running standalone ---------- */
/* --- These may be specified as numbers by placing a # before a number --- */

#define DEFAULT_USER "#-1"
#define DEFAULT_GROUP "#-1"

/* The name of the log files */
#define DEFAULT_XFERLOG "logs/access_log"
#define DEFAULT_AGENTLOG "logs/agent_log"
#define DEFAULT_REFERERLOG "logs/referer_log"
#define DEFAULT_ERRORLOG "logs/error_log"
#define DEFAULT_PIDLOG "logs/httpd.pid"

/* The referer documents to ignore */
#define DEFAULT_REFERERIGNORE ""

/* Define this to be what your HTML directory content files are called */
#define DEFAULT_INDEX "index.html"

/* Define this to 1 if you want fancy indexing, 0 otherwise */
#define DEFAULT_INDEXING 0

/* Define this to be what type you'd like returned for files with unknown */
/* suffixes */
#define DEFAULT_TYPE "text/html"

/* Define this to be what your per-directory security files are called */
#define DEFAULT_ACCESS_FNAME ".htaccess"

/* The name of the server config file */
#define SERVER_CONFIG_FILE "conf/httpd.conf"

/* The name of the document config file */
#define RESOURCE_CONFIG_FILE "conf/srm.conf"

/* The name of the MIME types file */
#define TYPES_CONFIG_FILE "conf/mime.types"

/* The name of the access file */
#define ACCESS_CONFIG_FILE "conf/access.conf"

/* Whether we should enable rfc931 identity checking */
#define DEFAULT_RFC931 0
/* The default directory in user's home dir */
#define DEFAULT_USER_DIR "public_html"

/* The default path for CGI scripts if none is currently set */
#define DEFAULT_PATH "/bin:/usr/bin:/usr/ucb:/usr/bsd:/usr/local/bin"

/* The path to the Bourne shell, for parsed docs */
#define SHELL_PATH "/bin/sh"

/* The default string lengths */
#define MAX_STRING_LEN 256
#define HUGE_STRING_LEN 8192

/* The timeout for waiting for messages */
#define DEFAULT_TIMEOUT 1200

/* The size of the server's internal read-write buffers */
#define IOBUFSIZE 8192

/* The number of header lines we will accept from a client */
#define MAX_HEADERS 200

/* Hi Roy. */
/* #define HTTP_TIME_FORMAT "%A, %d-%b-%y %T GMT" */
/* HTTP/1.0 specifies we use RFC 822 type date strings, so here we do */
#define HTTP_TIME_FORMAT "%a, %d %b %Y %T GMT" 

/* ------------------------------ error types ------------------------------ */

#define SERVER_VERSION "NCSA/1.4"
#define SERVER_PROTOCOL "HTTP/1.0"
#define SERVER_SUPPORT "httpd@void.ncsa.uiuc.edu"

#define DOCUMENT_FOLLOWS 200
#define REDIRECT 302
#define REDIRECT_LOCAL 3020
#define USE_LOCAL_COPY 304
#define BAD_REQUEST 400
#define AUTH_REQUIRED 401
#define FORBIDDEN 403
#define NOT_FOUND 404
#define SERVER_ERROR 500
#define NOT_IMPLEMENTED 501
#define NO_MEMORY 6992
#define CONF_ERROR 6993

#define METHODS 4
#define M_GET 0
#define M_PUT 1
#define M_POST 2
#define M_DELETE 3

/* Object types */
#define REDIRECT_URL -1
#define STD_DOCUMENT 0
#define SCRIPT_NCSA 1
#define SCRIPT_CGI 2

#define OPT_NONE 0
#define OPT_INDEXES 1
#define OPT_INCLUDES 2
#define OPT_SYM_LINKS 4
#define OPT_EXECCGI 8
#define OPT_UNSET 16
#define OPT_INCNOEXEC 32
#define OPT_SYM_OWNER 64
#define OPT_ALL (OPT_INDEXES|OPT_INCLUDES|OPT_SYM_LINKS|OPT_EXECCGI)

#define OR_NONE 0
#define OR_LIMIT 1
#define OR_OPTIONS 2
#define OR_FILEINFO 4
#define OR_AUTHCFG 8
#define OR_INDEXES 16
#define OR_ALL (OR_LIMIT|OR_OPTIONS|OR_FILEINFO|OR_AUTHCFG|OR_INDEXES)

#define CGI_MAGIC_TYPE "application/x-httpd-cgi"
#define INCLUDES_MAGIC_TYPE "text/x-server-parsed-html"

/* For directory indexing */
#define BY_PATH 0
#define BY_TYPE 1
#define BY_ENCODING 2

#define FANCY_INDEXING 1
#define ICONS_ARE_LINKS 2
#define SCAN_HTML_TITLES 4
#define SUPPRESS_LAST_MOD 8
#define SUPPRESS_SIZE 16
#define SUPPRESS_DESC 32

#include <stdio.h>
#ifndef ATTSVR3
#include <stdlib.h>
#include <sys/wait.h>
#endif
#include <string.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <sys/socket.h>
#ifdef NEED_SELECT_H
#include <sys/select.h>
#endif
#include <ctype.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>  /* for inet_ntoa */
#include <time.h>  /* for ctime */
#include <signal.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>
#include <fcntl.h>

#ifndef NeXT
#include <unistd.h>
#endif

#ifdef ultrix
#define ULTRIX_BRAIN_DEATH
#endif

#ifndef JMP_BUF
#define JMP_BUF sigjmp_buf
#endif


/* Just in case your linefeed isn't the one the other end is expecting. */
#define LF 10
#define CR 13

/* For access control */
#define DENY_THEN_ALLOW 0
#define ALLOW_THEN_DENY 1
#define MUTUAL_FAILURE 2

/* Struct shared by access and auth */
typedef struct {
    char *d;
    char opts;
    char override;

    int order[METHODS];

    int num_allow[METHODS];
    char *allow[METHODS][MAX_SECURITY];
    int num_auth[METHODS];
    char *auth[METHODS][MAX_SECURITY];

    char *auth_type;
    char *auth_name;
    char *auth_pwfile;
    char *auth_grpfile;

    int num_deny[METHODS];
    char *deny[METHODS][MAX_SECURITY];
} security_data;

/* Global, global, who's got the globals? */

/* Server config */
extern int standalone;
extern int port;
extern uid_t user_id;
extern gid_t group_id;
extern char server_root[MAX_STRING_LEN];
extern char annotation_server[MAX_STRING_LEN];  /* SSG 4/4/95 */
extern char error_fname[MAX_STRING_LEN];
extern char xfer_fname[MAX_STRING_LEN];
extern char agent_fname[MAX_STRING_LEN];
extern char referer_fname[MAX_STRING_LEN];
extern char pid_fname[MAX_STRING_LEN];
extern char server_admin[MAX_STRING_LEN];
extern char *server_hostname;
extern char server_confname[MAX_STRING_LEN];
extern char srm_confname[MAX_STRING_LEN];
extern char access_confname[MAX_STRING_LEN];
extern char types_confname[MAX_STRING_LEN];
extern int timeout;
extern int do_rfc931;
#ifdef PEM_AUTH
extern char auth_pem_decrypt[MAX_STRING_LEN];
extern char auth_pem_encrypt[MAX_STRING_LEN];
extern char auth_pem_entity[MAX_STRING_LEN];
extern char auth_pgp_decrypt[MAX_STRING_LEN];
extern char auth_pgp_encrypt[MAX_STRING_LEN];
extern char auth_pgp_entity[MAX_STRING_LEN];
#endif

/* Document config */
extern char user_dir[MAX_STRING_LEN];
extern char index_name[MAX_STRING_LEN];
extern char access_name[MAX_STRING_LEN];
extern char document_root[MAX_STRING_LEN];
extern char default_type[MAX_STRING_LEN];
extern char local_default_type[MAX_STRING_LEN];
extern char default_icon[MAX_STRING_LEN];
extern char local_default_icon[MAX_STRING_LEN];
extern char blank_icon[MAX_STRING_LEN];
extern int fancy_indexing;
extern char readme_fname[MAX_STRING_LEN];

/* Security config */
extern int num_sec;
extern security_data sec[MAX_SECURITY];

/* Auth config */
extern char *auth_type;
extern char *auth_name;
extern char *auth_pwfile;
extern char *auth_grpfile;
extern char user[MAX_STRING_LEN];
extern char groupname[MAX_STRING_LEN];
#ifdef PEM_AUTH
extern int doing_pem;
#endif

/* Request information */
extern int assbackwards;
extern int header_only;
extern char *remote_host;
extern char *remote_ip;
extern char *remote_name;
extern char *remote_logname;
extern int allow;
extern char allow_options;
extern int num_includes;
extern int dirs_in_alias;

/* MIME */
extern char auth_line[MAX_STRING_LEN];
extern int content_length;
extern char content_type[MAX_STRING_LEN];
extern char content_encoding[MAX_STRING_LEN];
extern char location[MAX_STRING_LEN];
extern char **in_headers_env;

/* http_log */
extern FILE *error_log;
extern int bytes_sent;
extern int status;

/* Function prototypes. */

/* http_config */
void read_config();
void parse_htaccess(char *dir, char override, FILE *out);
int get_pw(char *user, char *pw, FILE *errors);
int in_group(char *user, char *group);
int init_group(char *grpfile, FILE *out);
void kill_group();

/* http_alias */
void reset_aliases();
void dump_aliases();
void add_alias(char *f, char *r, int is_script);
void add_redirect(char *f, char *url);
int translate_name(char *name,FILE *fd);
void unmunge_name(char *name);
void save_aliases();
void reset_to_saved_aliases();

/* http_request */
void process_request(int in, FILE *out);
long send_fd(FILE *f, FILE *fd, void (*onexit)());
void send_fd_timed_out();
int find_script(char *method, char *name, char *args, int in, FILE *out);

/* http_get */
void send_cgi(char *method, char *file, char *path_args, char *args,
	      struct stat *finfo, int in, FILE *fd);
void send_file(char *file, FILE *fd, struct stat *fi, 
               char *path_args, char *args);
void process_include(FILE *f, FILE *fd, char *incstring, char *args);
void send_node(char *name, char *args, int in, FILE *fd);
void process_get(int in, FILE *out, char *m, char *url, char *args);

/* http_post */
void post_node(char *name, char *args, int in, FILE *out);

/* http_put */
void put_node(char *name, char *args, int in, FILE *out);

/* http_delete */
void delete_node(char *name, char *args, int in, FILE *out);

/* http_script */
void exec_cgi_script(char *method, char *path, char *args, int in, FILE *out);
int cgi_stub(char *method, char *path, char *path_args, char *args,
             char **env, struct stat *finfo, int in, FILE *out);
void exec_get_NCSA(char *path, char *args, int in, FILE *fd);
void exec_post_NCSA(char *path, char *args, int in, FILE *out);
char **add_common_vars(char **env, FILE *out);
void get_path_info(char *path, char *path_args, FILE *out, 
                   struct stat *finfo);

/* http_dir */
void index_directory(char *name, FILE *fd);
void add_icon(int type, char *icon, char *to, char *path, FILE *out);
void add_alt(int type, char *alt, char *to, char *path, FILE *out);
void add_desc(int type, char *desc, char *to, char *path, FILE *out);
void add_ignore(char *ext, char *path, FILE *out);
void add_header(char *name, char *path, FILE *out);
void add_readme(char *name, char *path, FILE *out);
void add_opts(char *optstr, char *path, FILE *out);
void add_opts_int(int opts, char *path, FILE *out);
void send_size(size_t size, FILE *fd);

void init_indexing();
void kill_indexing();

/* http_log */
void record_request(char *cmd_line);
void log_error(char *err);
void log_error_noclose(char *err);
void log_reason(char *reason, char *file);
int die(int type, char *err_string, FILE *fd);
void open_logs();
void close_logs();
void begin_http_header(FILE *fd, const char *msg); 
void error_log2stderr();
void log_transaction();
void htexit(int status, FILE *out);

/* http_mime */
void get_mime_headers(int fd, FILE *out, char* url);
void init_header_vars();
void send_http_header(FILE *fd);
void set_content_type(char *fn);
int set_last_modified(time_t t, FILE *out);
void probe_content_type(char *fn);
int scan_script_header(FILE *f, FILE *fd);
void add_type(char *fn, char *t,FILE *out);
void add_encoding(char *fn, char *t,FILE *out);
void set_content_length(int l);
void dump_types();
void init_mime();
void kill_mime();
int is_content_type(char *type);
void dump_default_header(FILE *fd);

/* http_access */
void evaluate_access(char *path, struct stat *finfo,int m, int *allow, 
                            char *op, FILE *out);
void kill_security();

/* http_auth */
void check_auth(security_data *s, int m, FILE *out);
#ifdef PEM_AUTH
int decrypt_request(int sfd, char *req, FILE **out);
void pem_cleanup(int status, FILE *out);
#endif

/* http_include */
void send_parsed_file(char *file, FILE *fd, char *path_args, char *args,
                      int noexec);

/* util */
void inststr(char *dst[], int argc, char *src);
void chdir_file(char *file);
void http2cgi(char *w);
int later_than(struct tm *tms, char *i);
int strcmp_match(char *str, char *exp);
int is_matchexp(char *str);
void strsubfirst(int start,char *dest, char *src);
void make_full_path(char *src1,char *src2,char *dst);
int is_directory(char *name);
int is_url(char *u);
void getparents(char *name);
void no2slash(char *name);
uid_t uname2id(char *name);
gid_t gname2id(char *name);
int getline(char *s, int n, int f, unsigned int timeout);
int eat_ws (FILE* fp);
int cfg_getline(char *s, int n, FILE *f);
void getword(char *word, char *line, char stop);
void cfg_getword(char *word, char *line);
void get_remote_host(int fd);
char *get_time();
char *gm_timestr_822(time_t t);
char *ht_time(time_t t, char *fmt, int gmt);
struct tm *get_gmtoff(long *tz);
void make_dirstr(char *s, int n, char *d);
int count_dirs(char *path);
void strcpy_dir(char *d, char *s);
void unescape_url(char *url);
void escape_url(char *url);
void escape_shell_cmd(char *cmd);
void plustospace(char *str);
void spacetoplus(char *str);
void str_tolower(char *str);
void uudecode(char *s,unsigned char *d,int dl);
#ifdef NEED_STRDUP
char *strdup (char *str);
#endif
#ifdef NEED_STRCASECMP
int strcasecmp(const char *s1, const char *s2);
#endif
#ifdef NEED_STRNCASECMP
int strncasecmp(const char *s1, const char *s2, int n);
#endif
char *make_env_str(char *n, char *v, FILE *out);
char **new_env(char **env, int to_add, int *pos);
void free_env(char **env);
int ind(char *s, char c);
int rind(char *s, char c);
void construct_url(char *d, char *s);
void get_local_host();
int get_portnum(int sd,FILE *out);
int can_exec(struct stat *finfo);
#ifdef NEED_INITGROUPS
int initgroups(const char *name, gid_t basegid);
#endif
char *get_remote_logname(FILE *fd);
char *rfc931(struct sockaddr_in *rmt_sin,struct sockaddr_in *our_sin);
void strncpy_dir(char *d, char *s, int n);
void lim_strcpy(char *d, char *s, int n);

