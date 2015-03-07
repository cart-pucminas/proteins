/*
 * Copyright(C) 2013 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * vector/vector_assign.c - vector_assign() implementation
 */

#include <assert.h>
#include <string.h>
#include <vector.h>

/*
 * Arguments sanity check.
 */
#define SANITY_CHECK()  \
	assert(v1 != NULL); \
	assert(v2 != NULL); \

/*
 * Assigns a vector to another.
 */
struct vector *vector_assign(struct vector *v1, struct vector *v2)
{
	SANITY_CHECK();
	
	/* Invalid argument. */
	if (vector_size(v1) != vector_size(v2))
		return (NULL);

	memcpy(v1->elements, v2->elements, vector_size(v1)*sizeof(double));
	
	return (v1);
}
