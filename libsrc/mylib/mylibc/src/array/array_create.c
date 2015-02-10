/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * array/array_create.c - array_create() implementation.
 */

#include <array.h>
#include <object.h>
#include <util.h>

/*
 * Creates an array.
 */
struct array *array_create(objinfo_t info, int size)
{
	void *objects;   /* Objects. */
	struct array *a; /* Array.   */
	
	a = smalloc(sizeof(struct array));
	objects = smalloc(size*sizeof(void *));

	/* Initialize array. */
	a->size = size;
	a->objects = objects;
	a->info = info;
	
	return (a);
}
