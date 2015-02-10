/*
 * matrix_destroy.c - matrix_destroy() implementation.
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
#include <stdlib.h>
#include <matrix.h>

/*
 * Safe matrix_destroy().
 */
static void _matrix_destroy(struct matrix *m)
{
	free(m->elements);
	free(m);
}

/*
 * Destroys a matrix.
 */
void matrix_destroy(struct matrix *m)
{
	/* Sanity check. */
	assert(m != NULL);

	_matrix_destroy(m);
}
