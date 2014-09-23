/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * graph/graph_edge.c - Graph edge object information.
 */

#include <graph.h>
#include <object.h>
#include <util.h>

/*
 * Compares two nodes.
 */
static int gnode_cmp(const void *key1, const void *key2)
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
static void *gnode_getkey(const void *obj)
{
	return (&(((struct gnode *)obj)->id));
}

/*
 * Object graph node information.
 */
struct objinfo _gnode =
{
	NULL,         /* read()   */
	NULL,         /* write()  */
	gnode_cmp,    /* cmp()    */
	gnode_getkey, /* getkey() */
	NULL,         /* hash()   */
	NULL          /* clone()  */
};
