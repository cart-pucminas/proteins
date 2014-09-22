/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * pqueue/pqueue_destroy.c - pqueue_destroy() implementation.
 */

#include <assert.h>
#include <pqueue.h>
#include <stdlib.h>

/*
 * Arguments sanity check.
 */
#define SANITY_CHECK()  \
	assert(pq != NULL); \

/*
 * Destroys a priority queue.
 */
void pqueue_destroy(struct pqueue *pq)
{
	SANITY_CHECK();

	free(pq->heap.objects);
	free(pq->heap.priority);
	free(pq);
}
