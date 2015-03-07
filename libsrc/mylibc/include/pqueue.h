/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * <pqueue.h> - Priority queue library.
 */

#ifndef PQUEUE_H_
#define PQUEUE_H_

	#include "object.h"

/*============================================================================*
 *                               Private Interface                            *
 *============================================================================*/

	/*
	 * Priority queue.
	 */
	struct pqueue
	{
		struct {
			int maxsize;     /* Maximum size. */
			int size;        /* Current size. */
			void **objects;  /* Objects.      */
			int *priority;   /* Priority.     */
		} heap;
		objinfo_t info; /* Object information. */
	};

	/*
	 * Fixes the heap property top-bottom.
	 */
	extern void _pqueue_downheap(struct pqueue *pq, int k);

	/*
	 * Fixes the heap property bottom-up.
	 */
	extern void _pqueue_upheap(struct pqueue *pq, int k);

/*============================================================================*
 *                               Public Interface                             *
 *============================================================================*/

	/*
	 * Opaque pointer to a priority queue.
	 */
	typedef struct pqueue * pqueue_t;
	
	/*
	 * Creates a priority queue.
	 */
	extern pqueue_t pqueue_create(objinfo_t info, int maxsize);
	
	/*
	 * Destroys a priority queue.
	 */
	extern void pqueue_destroy(pqueue_t pq);
	
	/*
	 * Asserts if a priority queue is empty.
	 */
	#define pqueue_empty(pq) \
		((pq)->heap.size == 0)
		
	/*
	 * Asserts if a priority queue is full.
	 */
	#define pqueue_full(pq) \
		((pq)->heap.size == (pq)->heap.maxsize)
	
	/*
	 * Changes the priority of an item.
	 */
	extern int pqueue_change(pqueue_t pq, void *obj, int newpriority);
	
	/*
	 * Inserts an object in a priority queue.
	 */
	extern int pqueue_insert(pqueue_t pq, void *obj, int priority);
	
	/*
	 * Removes an object from a priority queue.
	 */
	extern void *pqueue_remove(pqueue_t pq, int *priority);

#endif /* PQUEUE_H_ */
