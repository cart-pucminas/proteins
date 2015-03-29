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
 * @brief N-Dimension Vector Library
 */

#ifndef VECTOR_H_
#define VECTOR_H_
	
	#include <math.h>
	#include <assert.h>
	#include <stdbool.h>
	#include <stdlib.h>
	
	/*========================================================================*
	 *                          Private Interface                             *
	 *========================================================================*/
	 
	 /**
	  * @brief N-Dimension vector.
	  */
	 struct vector
	 {
		 unsigned dimension;         /**< Dimension. */
		 double * restrict elements; /**< Elements.  */
	 };
	 
	 /**
	  * @brief Opaque pointer to a N-dimension vector.
	  */
	 typedef struct vector * vector_t;
	 
	 /**
	  * @brief Opaque pointer to a constant N-dimension vector.
	  */
	 typedef const struct vector * const_vector_t;	

	/*========================================================================*
	 *                           Public Interface                             *
	 *========================================================================*/

	/* Forward definitions. */
	extern vector_t vector_create(unsigned);
	extern void vector_destroy(vector_t);
	extern void vector_assign(vector_t restrict, const_vector_t restrict);
	extern bool vector_cmp(const_vector_t restrict, const_vector_t restrict);
	extern void vector_add(vector_t restrict, const_vector_t restrict);
	extern void vector_sub(vector_t restrict, const_vector_t restrict);
	extern void vector_scalar(vector_t, double);
	extern void vector_invert(vector_t);
	extern void vector_cross(vector_t restrict, const_vector_t restrict);
	extern double vector_dot(const_vector_t restrict, const_vector_t restrict);
	extern void vector_normalize(vector_t);
	extern void vector_clear(vector_t);
	extern double vector_distance(const_vector_t restrict,const_vector_t restrict);
	extern vector_t vector_random(unsigned);

	/**
	 * @defgroup VectorN N-Dimension Vector Library
	 */
	/**@{*/
	
	/**
	 * @brief Gets the ith element in a vector.
	 * 
	 * @details Gets the element at position @p i of the vector pointed to by 
	 *          @p v.
	 * 
	 * @param v Vector to be considered.
	 * @param i Vector index.
	 * 
	 * @returns The ith object in the vector. 
	 */
	inline double vector_get(const struct vector *v, unsigned i)
	{
		/* Sanity check. */
		assert(v != NULL);
		assert(i < v->dimension);
		
		return (v->elements[i]);
	}

	/**
	 * @brief Sets the ith element in a vector.
	 * 
	 * @details Sets the element at position @p i of the vector pointed to by
	 *          @p v to @p e.
	 * 
	 * @param v Vector to be considered.
	 * @param i Vector index.
	 * @param e Element.
	 */
	inline void vector_set(const struct vector *v, unsigned i, double e)
	{
		/* Sanity check. */
		assert(v != NULL);
		assert(i < v->dimension);
		
		v->elements[i] = e;
	}
	
	/**
	 * @brief Returns the dimension of a vector.
	 * 
	 * @details Returns the dimension of the vector pointed to by @p v.
	 * 
	 * @param v Vector to be queried about.
	 * 
	 * @returns The dimension of the vector.
	 */
	inline unsigned vector_dimension(const struct vector *v)
	{
		/* Sanity check. */
		assert(v != NULL);
		
		return (v->dimension);
	}
	
	/**@}*/

#endif /* VECTOR_H_ */
