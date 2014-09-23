/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * pqueue/_pqueue_downheap.c - _pqueue_downheap() implementation.
 */

#include <pqueue.h>
#include <limits.h>

/*
 * Fixes the heap property top-bottom.
 */
void _pqueue_downheap(struct pqueue *pq, int k)
{
	int j;
	int priority;
	void *obj;
	
	priority = pq->heap.priority[k];
	obj = pq->heap.objects[k];
	
	while (k <= pq->heap.size >> 1)
	{
		j = k << 1;
		
		if (j < pq->heap.size)
		{
			if (pq->heap.priority[j] > pq->heap.priority[j + 1])
				j++;
		}
		
		if (priority <= pq->heap.priority[j])
			break;
		
		pq->heap.priority[k] = pq->heap.priority[j];
		pq->heap.objects[k] = pq->heap.objects[j];
		
		k = j;
	}
	
	pq->heap.priority[k] = priority;
	pq->heap.objects[k] = obj;
}
