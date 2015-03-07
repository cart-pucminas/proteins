/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * array/array_sort.c - array_sort() implementation.
 */

#include <array.h>
#include <object.h>
#include <util.h>

/*
 * Sorts an array using insertion sort.
 */
void array_sort(struct array *a)
{
	int i, j;  /* Loop index.       */
	void *tmp; /* Temporary object. */
	
	/* Cant search in array. */
	if (a->info->getkey == NULL)
		error("cannot array_search()");
		
	else if (a->info->cmp == NULL)
		error("cannot array_search()");
	
	/* Sort array. */
	for (i = 0; i < array_size(a); i++)
	{
		for (j = i + 1; j < array_size(a); j++)
		{
			/* Swap. */
			if (CMP(a->info, GETKEY(a->info, ARRAY(a, j)), GETKEY(a->info, ARRAY(a, i))) < 0)
			{
				tmp = ARRAY(a, j);
				ARRAY(a, j) = ARRAY(a, i);
				ARRAY(a, i) = tmp;
			}
		}
	}
}
