/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * array/array_shuffle.c - array_shuffle() implementation.
 */

#include <array.h>
#include <util.h>

/*
 * Shuffles an array.
 */
void array_shuffle(struct array *a)
{
	int i, j;  /* Loop index.       */
	void *tmp; /* Temporary object. */
	
	/* Shuffle array. */
	for (i = 0; i < array_size(a) - 1; i++) 
	{
		j = i + (randnum() % (array_size(a) - i -1)) + 1;
		
		while ((j <= i) || (j >= array_size(a)))
		;
		
		tmp = ARRAY(a, i);
		ARRAY(a, i) = ARRAY(a, j);
		ARRAY(a, j) = tmp;
	}
}
