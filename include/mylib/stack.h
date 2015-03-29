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
 * @brief Stack Library
 */
 
#ifndef STACK_H_
#define STACK_H_

	#include <assert.h>
	#include <stdbool.h>

	#include "object.h"
	
	/*========================================================================*
	 *                          Private Interface                             *
	 *========================================================================*/
 
	/**
	 * @brief Stack node.
	 */
	struct snode
	{
		object_t obj;       /**< Object.                 */
		struct snode *next; /**< Next node in the stack. */
	};

	/**
	 * @brief Stack.
	 */
	struct stack
	{
		unsigned size;              /**< Current stack size. */
		struct snode head;          /**< Dummy head node.    */
		const struct objinfo *info; /**< Object information. */
	};

	/**
	 * @brief Opaque pointer to a stack.
	 */
	 typedef struct stack * stack_t;
	 
	 /**
	  * @brief Opaque pointer to a constant stack.
	  */
	 typedef const struct stack * const_stack_t;

	/*========================================================================*
	 *                           Public Interface                             *
	 *========================================================================*/
	 
	 /* Forward definitions. */
	 extern stack_t stack_create(const struct objinfo *);
	 extern void stack_destroy(stack_t);
	 extern void stack_push(stack_t, object_t);
	 extern object_t stack_pop(stack_t);
	
	/**
	 * @defgroup Stack Stack Container
	 */
	/**@{*/

	/**
	 * @brief Returns the current size of a stack.
	 * 
	 * @details Returns the current size of the stack pointed to by @p s.
	 * 
	 * @param s Stack to be queried about.
	 * 
	 * @returns The current size of the stack.
	 */
	inline unsigned stack_size(const struct stack *s)
	{
		/* Sanity check. */
		assert(s != NULL);
		
		return (s->size);
	}

	/**
	 * @brief Asserts if a stack is empty.
	 * 
	 * @details Asserts if the stack pointed to by @p s.
	 * 
	 * @param s Stack to be queried about.
	 * 
	 * @returns True if the stack is empty, and false otherwise.
	 */
	inline bool stack_empty(const struct stack *s)
	{
		/* Sanity check. */
		assert(s != NULL);

		return (s->size == 0);
	}
	
	/**@}*/

#endif /* STACK_H_ */
