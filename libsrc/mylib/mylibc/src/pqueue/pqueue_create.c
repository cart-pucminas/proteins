/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * pqueue/pqueue_create.c - pqueue_create() implementation.
 */

#include <assert.h>
#include <object.h>
#include <pqueue.h>
#include <util.h>

/*
 * Arguments sanity check.
 */
#define SANITY_CHECK()    \
	assert(info != NULL); \
	assert(maxsize > 0);  \

/*
 * Creates a priority queue.
 */
struct pqueue *pqueue_create(objinfo_t info, int maxsize)
{
	int i;             /* Loop index.     */
	void **objects;    /* Objects.        */
	struct pqueue *pq; /* Priority queue. */
	
	SANITY_CHECK();
	
	/* Allocate structures. */
	pq = smalloc(sizeof(struct pqueue));
	objects = smalloc((maxsize + 1)*sizeof(void **));
	
	/* Initializes the priority queue. */
	for (i = 0; i < maxsize; i++)
		objects[i] = NULL;
	pq->heap.maxsize = maxsize;
	pq->heap.size = 0;
	pq->heap.objects = objects;
	pq->heap.priority = smalloc((maxsize + 1)*sizeof(int));
	pq->info = info;
	
	return (pq);
}
