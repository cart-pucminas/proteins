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
 * @brief Queue Library
 */

#ifndef QUEUE_H_
#define QUEUE_H_

	#include <assert.h>
	#include <stdbool.h>
	
	#include "object.h"
	
	/*========================================================================*
	 *                          Private Interface                             *
	 *========================================================================*/

	/**
	 * @brief Queue node.
	 */
	struct qnode
	{
		object_t obj;       /**< Object.                 */
		struct qnode *next; /**< Next node in the queue. */
	};

	/**
	 * @brief Queue.
	 */
	struct queue
	{
		unsigned length;            /**< Current queue length. */
		struct qnode head;          /**< Dummy head node.      */
		struct qnode *tail;         /**< Tail node.            */
		const struct objinfo *info; /**< Object information.   */
	};

	/**
	 * @brief Opaque pointer to a queue.
	 */
	typedef struct queue * queue_t;
	
	/**
	 * @brief Opaque pointer to a constant queue.
	 */
	typedef const struct queue * const_queue_t;

	/*========================================================================*
	 *                           Public Interface                             *
	 *========================================================================*/
	
	/* Forward definitions. */
	extern queue_t queue_create(const struct objinfo *);
	extern void queue_destroy(queue_t);
	extern void queue_enqueue(queue_t, object_t);
	extern object_t queue_dequeue(queue_t);
	
	/**
	 * @defgroup Queue Queue Container
	 */
	/**@{*/
	
	/**
	 * @brief Returns the current length of a queue.
	 * 
	 * @details Returns the current length of the queue pointed to by @p q.
	 * 
	 * @param q Queue to be queried about.
	 * 
	 * @returns The current length of the queue.
	 */
	inline unsigned queue_length(const struct queue *q)
	{
		/* Sanity check. */
		assert(q != NULL);
		
		return (q->length);
	}

	/**
	 * @brief Asserts if a queue is empty.
	 * 
	 * @details Asserts if the queue pointed to by @p q is empty.
	 * 
	 * @param q Queue to be queried about.
	 * 
	 * @returns True if the queue is empty, and false otherwise.
	 */
	inline bool queue_empty(const struct queue *q)
	{
		/* Sanity check. */
		assert(q != NULL);
		
		return (q->length == 0);
	}
	
	/**@}*/

#endif /* QUEUE_H_ */
