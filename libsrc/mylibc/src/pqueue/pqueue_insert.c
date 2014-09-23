/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * pqueue/pqueue_insert.c - pqueue_insert() implementation.
 */

#include <assert.h>
#include <pqueue.h>

/*
 * Arguments sanity check.
 */
#define SANITY_CHECK()     \
	assert(pq != NULL);    \
	assert(obj != NULL);   \
	assert(priority >= 0); \

/*
 * Inserts an object in a priority queue.
 */
int pqueue_insert(struct pqueue *pq, void *obj, int priority)
{
	int i;
	
	SANITY_CHECK();
	
	/* Heap is full. */
	if (pqueue_full(pq))
		return (-1);
	
	i = ++pq->heap.size;
	
	pq->heap.objects[i] = obj;
	pq->heap.priority[i] = priority;
	
	_pqueue_upheap(pq, i);
	
	return (0);
}
