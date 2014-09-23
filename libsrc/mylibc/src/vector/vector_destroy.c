/*
 * Copyright (C) 2013 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 *
 * vector/vector_destroy.c - vector_destroy() implementation.
 */

#include <assert.h>
#include <stdlib.h>
#include <vector.h>

/*
 * Arguments sanity check.
 */
#define SANITY_CHECK() \
	assert(v != NULL); \

/*
 * Destroys a vector.
 */
void vector_destroy(struct vector *v)
{
	SANITY_CHECK();
	
	free(v->elements);
	free(v);
}
