/*
 * matrix_create.c - matrix_create() implementation.
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

#include <assert.h>
#include <matrix.h>
#include <util.h>

/*
 * Safe matrix_create().
 */
static struct matrix *_matrix_create(int height, int width)
{
	double *elements; /* Elements. */
	struct matrix *m; /* Matrix.   */
	
	/* Allocate data structures. */
	m = smalloc(sizeof(struct matrix));
	elements = scalloc(height*width, sizeof(double));
	
	/* Initialize matrix. */
	m->width = width;
	m->height = height;
	m->elements = elements;
	
	return (m);
}

/*
 * Creates a matrix.
 */
struct matrix *matrix_create(int height, int width)
{
	/* Sanity check. */
	assert(width > 0);
	assert(height > 0);
	
	return (_matrix_create(height, width));
}
