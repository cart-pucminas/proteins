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
 * @brief Matrix Library
 */

#ifndef MATRIX_H_
#define MATRIX_H_
	
	#include <assert.h>
	#include <stdbool.h>
	
	/*========================================================================*
	 *                          Private Interface                             *
	 *========================================================================*/
	 
	 /**
	  * @brief 2D Matrix.
	  */
	 struct matrix
	 {
		 unsigned nrows;     /**< Number of rows.                         */
		 unsigned ncols;     /**< Number of columns.                      */
		 unsigned dimension; /**< Number of rows times number of columns. */
		 double *elements;   /**< Elements of the matrix.                 */
	 };
	 
	 /**
	  * @brief Opaque pointer to a matrix.
	  */
	 typedef struct matrix * matrix_t;
	 
	 /**
	  * @brief Opaque pointer to a constant matrix.
	  */
	 typedef const struct matrix * const_matrix_t;

	/*========================================================================*
	 *                           Public Interface                             *
	 *========================================================================*/

	/* Forward definitions. */
	extern matrix_t matrix_create(unsigned, unsigned);
	extern void matrix_destroy(matrix_t);
	extern matrix_t matrix_random(unsigned, unsigned);
	extern bool matrix_cmp(const_matrix_t restrict, const_matrix_t restrict);
	extern void matrix_add(matrix_t restrict, const_matrix_t restrict);
	extern void matrix_sub(matrix_t restrict, const_matrix_t restrict);
	extern void matrix_scalar(matrix_t, double);
	extern matrix_t matrix_mult(const_matrix_t restrict,const_matrix_t restrict);
	
	/**
	 * @defgroup Matrix Matrix Library
	 */
	/**@{*/
	
	/**
	 * @brief Gets the element [i, j] of a 2D matrix.
	 * 
	 * @details Gets the element [i, j] of the 2D matrix pointed to by @p m.
	 * 
	 * @param m Matrix.
	 * @param i Row index.
	 * @param j Column index.
	 * 
	 * @returns The element [i, j] of the matrix.
	 */
	inline double matrix_get(const struct matrix *m, unsigned i, unsigned j)
	{
		/* Sanity check. */
		assert(m != NULL);
		assert(i < m->nrows);
		assert(j < m->ncols);
		
		return (m->elements[i*m->ncols + j]);
	}
	
	/**
	 * @brief Sets the element [i, j] of a 2D matrix.
	 * 
	 * @details sets the element [i, j] of the 2D matrix pointed to by @p m to
	            @p e.
	 * 
	 * @param m Matrix.
	 * @param i Row index.
	 * @param j Column index.
	 * @param e Element.
	 */
	inline void matrix_set(struct matrix *m, unsigned i, unsigned j, double e)
	{
		/* Sanity check. */
		assert(m != NULL);
		assert(i < m->nrows);
		assert(j < m->ncols);
		
		m->elements[i*m->ncols + j] = e;
	}
	
	/**@}*/

#endif /* MATRIX_H_ */
