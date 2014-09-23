/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * table/table_destroy.c - table_destroy() implementation.
 */

#include <table.h>
#include <stdlib.h>

/*
 * Destroys a table
 */
void table_destroy(struct table *t)
{
	free(t->objects);
	free(t);
}
