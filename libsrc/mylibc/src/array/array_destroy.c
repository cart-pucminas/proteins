/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * array/array_destroy.c - array_destroy() implementation.
 */

#include <array.h>
#include <stdlib.h>

/*
 * Destroys an array.
 */
void array_destroy(struct array *a)
{
	free(a->objects);
	free(a);
}
