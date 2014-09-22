/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * pqueue/_pqueue_upheap.c - _pqueue_upheap() implementation.
 */

#include <pqueue.h>
#include <limits.h>

/*
 * Fixes the heap property bottom-up.
 */
void _pqueue_upheap(struct pqueue *pq, int k)
{
	void *obj;    /* Object */
	int priority; /* Priority. */
	
	priority = pq->heap.priority[k];
	obj = pq->heap.objects[k];
	
	pq->heap.priority[0] = INT_MIN;
	
	while (pq->heap.priority[k >> 1] >= priority)
	{
		pq->heap.priority[k] = pq->heap.priority[k >> 1];
		pq->heap.objects[k] = pq->heap.objects[k >> 1];
		
		k >>= 1;
	}
	
	pq->heap.priority[k] = priority;
	pq->heap.objects[k] = obj;
}
