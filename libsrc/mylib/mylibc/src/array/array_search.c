/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * array/array_search.c - array_search() implementation.
 */

#include <array.h>
#include <object.h>
#include <util.h>

/*
 * Searches for an object in an array.
 */
int array_search(struct array *a, void *key)
{
	int i;
	
	/* Cant search in array. */
	if ((a->info->getkey == NULL) || (a->info->cmp == NULL))
	{
		warning("cannot array_search()");
		return (-1);
	}
	
	/* Sequential search. */
	for (i = 0; i < array_size(a); i++)
	{
		/* Found. */
		if (!CMP(a->info, GETKEY(a->info, ARRAY(a, i)), key))
			return (i);
	}
	
	return (-1);
}
