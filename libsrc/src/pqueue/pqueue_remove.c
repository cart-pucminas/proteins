/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * pqueue/pqueue_remove.c - pqueue_remove() implementation.
 */

#include <assert.h>
#include <object.h>
#include <pqueue.h>

/*
 * Arguments sanity check.
 */
#define SANITY_CHECK()   \
	assert(pq != NULL);  \
	
/*
 * Removes the higher priority object from a priority queue.
 */
void *pqueue_remove(struct pqueue *pq, int *priority)
{
	int i;     /* Priority queue index. */
	void *obj; /* Object.               */
	
	SANITY_CHECK();
	
	/* Priority queue is empty. */
	if (pqueue_empty(pq))
		return (NULL);
	
	obj = pq->heap.objects[1];
	if (priority != NULL)
		*priority = pq->heap.priority[1];
	i = pq->heap.size--;
	
	pq->heap.objects[1] = pq->heap.objects[i];
	pq->heap.priority[1] = pq->heap.priority[i];
	
	_pqueue_downheap(pq, 1);
	
	return (obj);
}
