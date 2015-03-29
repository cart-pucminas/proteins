/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 *
 * This file is part of MyLib.
 *
 * MyLib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * MyLib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with MyLib. If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file
 * 
 * @brief Priority Queue Library
 */

#ifndef PQUEUE_H_
#define PQUEUE_H_
	
	#include <assert.h>
	#include <stdbool.h>
	
	#include "object.h"
	
	/*========================================================================*
	 *                          Private Interface                             *
	 *========================================================================*/

	/**
	 * @brief Priority queue.
	 */
	struct pqueue
	{
		unsigned maxsize;           /**< Maximum size (in elements). */
		unsigned size;              /**< Current size (in elements). */
		object_t *objects;          /**< Objects.                    */
		int *priorities;            /**< Priorities.                 */
		const struct objinfo *info; /**< Object information.         */
	};
	
	/**
	 * @brief Opaque pointer to a priority queue.
	 */
	typedef struct pqueue * pqueue_t;
	
	/**
	 * @brief Opaque pointer to a constant priority queue.
	 */
	typedef const struct pqueue *const_pqueue_t;

	/*========================================================================*
	 *                           Public Interface                             *
	 *========================================================================*/

	/* Forward definitions. */
	extern pqueue_t pqueue_create(const struct objinfo *, unsigned);
	extern void pqueue_destroy(pqueue_t);
	extern int pqueue_change(pqueue_t, object_t, int);
	extern void pqueue_insert(pqueue_t, object_t, int);
	extern object_t pqueue_remove(pqueue_t);
	
	/**
	 * @defgroup Pqueue Priority Queue Container
	 */
	/**@{*/
	
	/**
	 * @brief Asserts if a priority queue is empty.
	 * 
	 * @details Asserts if the priority queue pointed to by @p pq is empty.
	 * 
	 * @param pq Priority queue to be queried about.
	 * 
	 * @returns True if the priority queue is empty, and false otherwise.
	 */
	inline bool pqueue_empty(const struct pqueue *pq)
	{
		/* Sanity check. */
		assert(pq != NULL);
		
		return (pq->size == 0);
	}
	
	/**
	 * @brief Asserts if a priority queue is full.
	 * 
	 * @details Asserts if the priority queue pointed to by @p pq is full.
	 * 
	 * @param pq Priority queue to be queried about.
	 * 
	 * @returns True if the priority queue is empty, and false otherwise.
	 */
	inline bool pqueue_full(const struct pqueue *pq)
	{
		/* Sanity check. */
		assert(pq != NULL);
		
		return (pq->size == pq->maxsize);
	}
	
	/**@}*/

#endif /* PQUEUE_H_ */
