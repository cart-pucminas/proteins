/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * graph/graph_edge.c - Graph edge object information.
 */

#include <graph.h>
#include <object.h>
#include <util.h>

/*
 * Compares two edges.
 */
static int gedge_cmp(const void *key1, const void *key2)
{
	if (*INTP(key1) < *INTP(key2))
		return (-1);
	if (*INTP(key1) > *INTP(key2))
		return (1);
	
	return (0);
}

/*
 * Gets edge key.
 */
static void *gedge_getkey(const void *obj)
{
	return (&(((struct gedge *)obj)->id));
}

/*
 * Object graph edge information.
 */
struct objinfo _gedge =
{
	NULL,         /* read()   */
	NULL,         /* write()  */
	gedge_cmp,    /* cmp()    */
	gedge_getkey, /* getkey() */
	NULL,         /* hash()   */
	NULL          /* clone()  */
};
