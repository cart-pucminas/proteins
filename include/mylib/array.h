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
 * @brief Array Library
 */

#ifndef ARRAY_H_
#define ARRAY_H_
	
	#include <assert.h>
	
	#include "object.h"
	
	/*========================================================================*
	 *                          Private Interface                             *
	 *========================================================================*/
	
	/**
	 * @brief Array.
	 */
	struct array
	{
		unsigned size;              /**< Size.               */
		object_t *objects;          /**< Objects.            */
		const struct objinfo *info; /**< Object information. */
	};
	
	/**
	 * @brief Opaque pointer to an array.
	 */
	typedef struct array * array_t;
	
	/**
	 * @brief Opaque pointer to a constant array.
	 */
	typedef const struct array * const_array_t;

	/*========================================================================*
	 *                           Public Interface                             *
	 *========================================================================*/

	/* Forward definitions. */
	extern array_t array_create(const struct objinfo *, unsigned);
	extern void array_destroy(array_t);
	extern void array_shuffle(array_t);
	extern void array_sort(array_t);

	/**
	 * @defgroup Array Array Container
	 */
	/**@{*/
	
	/**
	 * @brief Gets the ith object in an array.
	 * 
	 * @details Gets the object at position @p i of the array pointed to by 
	 *          @p a.
	 * 
	 * @param a Array to be considered.
	 * @param i Array index.
	 * 
	 * @returns The ith object in the array. 
	 */
	inline object_t array_get(const struct array *a, unsigned i)
	{
		/* Sanity check. */
		assert(a != NULL);
		assert(i < a->size);
		
		return (a->objects[i]);
	}

	/**
	 * @brief Sets the ith object in an array.
	 * 
	 * @details Sets the object at position @p i of the array pointed to by
	 *          @p a to @p obj.
	 * 
	 * @param a   Array to be considered.
	 * @param i   Array index.
	 * @param obj Object.
	 */
	inline void array_set(struct array *a, unsigned i, object_t obj)
	{
		/* Sanity check. */
		assert(a != NULL);
		assert(i < a->size);
		
		a->objects[i] = obj;
	}
	
	/**
	 * @brief Returns the size of an array.
	 * 
	 * @details Returns the size of the array pointed to by @p a.
	 * 
	 * @param a Array to be queried about.
	 * 
	 * @returns The size of the array.
	 */
	inline unsigned array_size(const struct array *a)
	{
		/* Sanity check. */
		assert(a != NULL);
		
		return (a->size);
	}
	
	/**@}*/

#endif /* ARRAY_H_ */
