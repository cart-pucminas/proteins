/*
 * Copyright (C) 2013 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 *
 * vector/vector_create.c>- vector_create() implementation.
 */

#include <assert.h>
#include <vector.h>
#include <util.h>

/*
 * Arguments sanity check.
 */
#define SANITY_CHECK() \
	assert(n > 1);     \

/*
 * Creates a vector.
 */
struct vector *vector_create(int n)
{
	struct vector *v;
	
	SANITY_CHECK();
	
	v = smalloc(sizeof(struct vector));
	
	/* Initilize vector. */
	v->size = n;
	v->elements = scalloc(n, sizeof(double));

	return (v);
}
