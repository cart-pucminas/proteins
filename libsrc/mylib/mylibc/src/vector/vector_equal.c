/*
 * Copyright (C) 2013 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 *
 * <vector/vector_equal.c> - vector_equal() implementation.
 */

#include <assert.h>
#include <stdlib.h>
#include <vector.h>

/*
 * Arguments sanity check.
 */
#define SANITY_CHECK() \
	assert(a != NULL); \
	assert(b != NULL); \

/*
 * Tests if two vectors are equal.
 */
int vector_equal(struct vector *a, struct vector *b)
{
	int i;
	
	SANITY_CHECK();
	
	/* Vectors differ on size. */
	if (a->size != b->size)
		return (0);
	
	/* Test all elements. */
	for (i = 0; i < a->size; i++)
	{
		if (VECTOR(a, i) != VECTOR(b, i))
			return (0);
	}
	
	return (1);
}

