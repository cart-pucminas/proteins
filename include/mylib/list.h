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
 * @brief List Library
 */

#ifndef LIST_H_
#define LIST_H_

	#include <assert.h>
	#include <stdbool.h>
	
	#include "object.h"
	
	/*========================================================================*
	 *                          Private Interface                             *
	 *========================================================================*/
 
	/**
	 * @brief List node.
	 */
	struct lnode
	{
		object_t obj;       /**< Object.                */
		struct lnode *next; /**< Next node in the list. */
	};

	/**
	 * @brief List.
	 */
	struct list
	{
		unsigned size;              /**< Current list size.  */
		struct lnode head;          /**< Dummy head node.    */
		struct lnode *tail;         /**< Tail node.          */
		const struct objinfo *info; /**< Object information. */
	};
	
	/**
	 * @brief Opaque pointer to a list node.
	 */
	typedef struct lnode * lnode_t;
	
	/**
	 * @brief Opaque pointer to a constant list node.
	 */
	typedef const struct lnode * const_lnode_t;

	/**
	 * @brief Opaque pointer to a list.
	 */
	typedef struct list * list_t;
	
	/**
	 * @brief Opaque pointer to a constant list.
	 */
	typedef const struct list * const_list_t;

	/*========================================================================*
	 *                           Public Interface                             *
	 *========================================================================*/
	
	/* Forward definitions. */
	extern list_t list_create(const struct objinfo *);
	extern void list_destroy(list_t);
	extern void list_insert_after(list_t, lnode_t, object_t);
	extern void list_insert_begin(list_t, object_t);
	extern void list_insert_end(list_t, object_t);
	extern object_t list_remove_first(list_t);
	extern object_t list_remove_after(list_t, lnode_t);
	
	/**
	 * @defgroup List List Container
	 */
	/**@{*/
	
	/**
	 * @brief Returns an iterator to the begin of a list.
	 * 
	 * @details Returns an iterator to the begin of the list pointed to by @p l.
	 * 
	 * @param l List to be considered.
	 * 
	 * @returns An iterator to the begin of the list. If the list is empty, a 
	 *          null pointer is returned instead.
	 */
	inline struct lnode *list_begin(const struct list *l)
	{
		/* Sanity check. */
		assert(l != NULL);
		
		return (l->head.next);
	}

	/**
	 * @brief Returns the next iterator in the list.
	 * 
	 * @details Returns the next iterator from the current iterator pointed to
	 *          by @p i.
	 * 
	 * @param i Current iterator.
	 * 
	 * @returns The next iterator in the list. If there is no next iterator a 
	 *          null pointer is returned.
	 */
	inline struct lnode *list_next(const struct lnode *i)
	{
		/* Sanity check. */
		assert(i != NULL);
		
		return (i->next);
	}

	/**
	 * @brief Retrieves the object stored in a list iterator.
	 * 
	 * @details Retrieves the object stored in the list iterator pointed to by
	 *          @p i.
	 * 
	 * @param i List iterator.
	 * 
	 * @returns The object stored in the list iterator.
	 */
	inline object_t list_object(const struct lnode *i)
	{
		/* Sanity check. */
		assert(i != NULL);
		
		return (i->obj);
	}
	
	/**
	 * @brief Alias for list_insert_begin().
	 */
	inline void list_insert(struct list *l, object_t obj)
	{
		list_insert_begin(l, obj);
	}
	
	/**
	 * @brief Returns the current size of a list.
	 * 
	 * @details Returns the current size of the list pointed to by @p l.
	 * 
	 * @param l List to be queried about.
	 * 
	 * @returns The current size of a list.
	 */
	inline unsigned list_size(const struct list *l)
	{
		/* Sanity check. */
		assert(l != NULL);
		
		return (l->size);
	}

	/**
	 * @brief Asserts if a list is empty.
	 * 
	 * @details Asserts if the list pointed to by @p l is empty.
	 * 
	 * @param l List to be queried about.
	 * 
	 * @returns True if the list is empty, and false otherwise.
	 */
	inline bool list_empty(const struct list *l)
	{
		/* Sanity check. */
		assert(l != NULL);
		
		return (l->size == 0);
	}
	
	/**@}*/

#endif /* LIST_H_ */
