/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * table/table_create.c - table_create() implementation.
 */

#include <assert.h>
#include <object.h>
#include <table.h>
#include <util.h>

/*
 * Arguments sanity check.
 */
#define SANITY_CHECK()    \
	assert(info != NULL); \
	assert(height > 1);   \
	assert(width > 1);    \

/*
 * Creates a table .
 */
struct table *table_create(objinfo_t info, int height, int width)
{
	void **objects;  /* Objects. */
	struct table *t; /* Tqble.   */
	
	SANITY_CHECK();
	
	/* Allocate data. */
	t = smalloc(sizeof(struct table));
	objects = smalloc(height*width*sizeof(void *));

	/* Initialize table. */
	t->height = height;
	t->width = width;
	t->objects = objects;
	t->info = info;

	return (t);
}
