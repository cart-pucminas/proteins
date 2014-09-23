/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * pqueue/pqueue_change.c - pqueue_change() implementation.
 */

#include <assert.h>
#include <object.h>
#include <pqueue.h>

/*
 * Arguments sanity check.
 */
#define SANITY_CHECK()        \
	assert(pq != NULL);       \
	assert(obj != NULL);      \
	assert(newpriority >= 0); \

/*
 * Changes the priority of an item.
 */
int pqueue_change(struct pqueue *pq, void *obj, int newpriority)
{
	int i;           /* Item index.   */
	int oldpriority; /* Old priority. */
	
	SANITY_CHECK();

	/* Search for item. */
	for (i = 1; i <= pq->heap.size; i++)
	{	
		/* Found. */
		if (pq->heap.objects[i] == obj)
			goto found;
	}
	
	return (-1);
	
found:

	/* Reassign priority. */
	oldpriority = pq->heap.priority[i];
	pq->heap.priority[i] = newpriority;
	if (newpriority < oldpriority)
		_pqueue_upheap(pq, i);
	else if (newpriority > oldpriority)
		_pqueue_downheap(pq, i);
	
	return (oldpriority);
}
