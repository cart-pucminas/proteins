/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * graph/graph_nodeid.c - graph_nodeid() implementation.
 */

#include <assert.h>
#include <graph.h>
#include <object.h>

/*
 * Arguments sanity check.
 */
#define SANITY_CHECK()               \
	assert(g != NULL);               \
	assert(g->info->hash != NULL);   \
	assert(g->info->getkey != NULL); \
	assert(g->info->cmp != NULL);    \
	assert(key != NULL);             \

/*
 * Gets the graph node ID of an object.
 */
int _graph_nodeid(struct graph *g, void *key)
{ 
	int i;  /* Loop index. */
	int id; /* Node ID.    */
	
	SANITY_CHECK();
	
	id = HASH(g->info, key)%g->size;
	
	/* Check for perfect hash. */
	if (g->nodes[id].obj != NULL)
	{
		/* Found. */
		if (!CMP(g->info, GETKEY(g->info, g->nodes[id].obj), key))
			return (id);
	}
	
	/* Solve collision. */
	for (i = (id + 1)%g->size; i != id; i = (i + 1)%g->size)
	{
		/* Found. */
		if (!CMP(g->info, GETKEY(g->info, g->nodes[i].obj), key))
		{
			id = i;
			return (id);
		}
	}

	return (-1);
}
