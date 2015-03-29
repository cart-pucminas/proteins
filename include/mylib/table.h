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
 * @brief Table Library
 */

#ifndef TABLE_H_
#define TABLE_H_
	
	#include <assert.h>
	
	#include "object.h"
	
	/*========================================================================*
	 *                          Private Interface                             *
	 *========================================================================*/

	/**
	 * @brief Table.
	 */
	struct table
	{
		unsigned width;             /**< Width.              */
		unsigned height;            /**< Height.             */
		object_t *objects;          /**< Objects.            */
		const struct objinfo *info; /**< Object information. */
	};
	
	/**
	 * @brief Opaque pointer to a table.
	 */
	typedef struct table * table_t;
	
	/**
	 * @brief Opaque pointer to a constant table.
	 */
	typedef const struct table * const_table_t;

	/*========================================================================*
	 *                           Public Interface                             *
	 *========================================================================*/

	/* Forward definitions. */
	extern table_t table_create(const struct objinfo *, unsigned, unsigned);
	extern void table_destroy(table_t);

	/**
	 * @defgroup Table Table Container
	 */
	/**@{*/
	
	/**
	 * @brief Gets the [i, j] object in a table.
	 * 
	 * @details Gets the object at row @p i and column @p j of the table pointed
	 *          to by @p t.
	 * 
	 * @param t Table to be considered.
	 * @param i Row number.
	 * @param j Column number.
	 * 
	 * @returns The [i, j] object in the table. 
	 */
	inline object_t table_get(const struct table *t, unsigned i, unsigned j)
	{
		/* Sanity check. */
		assert(t != NULL);
		assert(i < t->height);
		assert(j < t->width);
		
		return (t->objects[i*t->width + j]);
	}

	/**
	 * @brief Sets the [i, j] object in a table.
	 * 
	 * @details Sets the object at row @p i and column @p j of the table pointed
	 *          to by @p t to @p obj.
	 * 
	 * @param t   Table to be considered.
	 * @param i   Row number.
	 * @param j   Column number.
	 * @param obj Object.
	 */
	inline void table_set(struct table *t, unsigned i, unsigned j, object_t obj)
	{
		/* Sanity check. */
		assert(t != NULL);
		assert(i < t->height);
		assert(j < t->width);
		
		t->objects[i*t->width + j] = obj;
	}
	
	/**@}*/

#endif /* TABLE_H_ */
