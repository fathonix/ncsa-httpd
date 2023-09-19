/***************************************************************************
 * This file contains the request queue for file descriptors from accepted *
 * connections.                                                            *
 * Copyright 1995 Brandon Long (blong@uiuc.edu)                            *
 * For ACM@UIUC HTTPD 1.3.3                                                *
 ***************************************************************************/

/*http_rqueue.c,v 1.1 1995/02/23 09:18:49 blong Exp
**http_rqueue.c,v
 * Revision 1.1  1995/02/23  09:18:49  blong
 * Update to 1.4beta from ACM 1.3.3
 * Adds round robin stay alive children processes and Error Document direction
 *
 */


#include "httpd.h"
#include "queue.h"

queue* createQueue() {
    queue* newq;

    newq = (queue *)malloc(sizeof(queue));
    newq->Front = NULL;
    newq->Back = NULL;
    newq->num = 0;

    return newq;
}


/* Some may disagree, but I've allows thought of queues as you put it in
on the front, and take it out the back, so this is how I made it. */

int enQueue(queue* q, int newfd) {
    queueRec* Rec;

    Rec = (queueRec *)malloc(sizeof(queue));

    Rec->Data = newfd;

    if ((q->Front == NULL) && (q->Back == NULL)) {
	Rec->Next = NULL;
	Rec->Prev = NULL;
	q->Front = Rec;
	q->Back = Rec;
    } else {
	Rec->Next = q->Front;
	q->Front->Prev = Rec;
	Rec->Prev = NULL;
	q->Front = Rec;
    }

    q->num++;
    return q->num;
}
    
int deQueue(queue* q) {
    queueRec* tmp;
    int oldfd;

    if ((q->Front != NULL) && (q->Back != NULL)) {
	if (q->Front == q->Back) {
	    tmp = q->Back;
	    oldfd = tmp->Data;
	    free(tmp);
	    q->Back = NULL;
	    q->Front = NULL;
	    q->num = 0;
	    return oldfd;
	} else {	
	    tmp = q->Back;
	    oldfd = q->Back->Data;
	    q->Back = q->Back->Prev;
	    q->Back->Next = NULL;
	    q->num--;
	    free(tmp);
	    return oldfd;
	}
    } else return -1; /* return -1 on error (queue empty) */
}
    
int numQueue(queue* q) {
    return q->num;
}
