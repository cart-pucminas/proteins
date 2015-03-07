/*
 * matrix.h - Matrix library.
 * 
 * Copyright (C) 2011-2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MATRIX_H_
#define MATRIX_H_

/*============================================================================*
 *                             Private Interface                              *
 *============================================================================*/

	/*
	 * Matrix.
	 */
	struct matrix
	{
		int width;        /* Width.    */
		int height;       /* Height.   */
		double *elements; /* Elements. */
	};

/*============================================================================*
 *                             Public Interface                               *
 *============================================================================*/
 
	/*
	 * Opaque pointer to a matrix.
	 */
	typedef struct matrix * matrix_t;
	
	/*
	 * Creates a matrix.
	 */
	extern matrix_t matrix_create(int height, int width);
	
	/*
	 * Destroys a matrix.
	 */
	extern void matrix_destroy(matrix_t m);
	
	/*
	 * Returns the height of a matrix.
	 */
	#define matrix_height(m) \
		((m)->height)
		
	/*
	 * Returns the width of a matrix.
	 */
	#define matrix_width(m) \
		((m)->width)
	
	/*
	 * Returns the element [i, j] in a matrix.
	 */
	#define MATRIX(m, i, j) \
		((m)->elements[(i)*(m)->width + (j)])
	 
#endif /* MATRIX_H_ */
