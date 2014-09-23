/*
 * Copyright (C) 2013 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 *
 * vector/vector_distance.c - vector_distance() implementation.
 */

#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <vector.h>

/*
 * Arguments sanity check.
 */
#define SANITY_CHECK() \
	assert(a != NULL); \
	assert(b != NULL); \

/*
 * Computes the euclidean distance between two points.
 */
double vector_distance(struct vector *a, struct vector *b)
{
	int i;           /* Loop index. */
	double distance; /* Distance.   */
	
	SANITY_CHECK();
	
	/* Vectors do not agree on size. */
	if (a->size != b->size)
		return (-1);

	/* Computes the euclidean distance. */
	distance = 0.0;
	for (i = 0; i < a->size; i++)
		distance +=  pow(VECTOR(a, i) - VECTOR(b, i), 2);
	distance = sqrt(distance);
	
	return (distance);
}

