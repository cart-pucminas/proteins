/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * graph/graph_remove.c - graph_remove() implementation.
 */

#include <assert.h>
#include <graph.h>
#include <list.h>
#include <stdlib.h>

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
 * Removes an object from a graph.
 */
void *graph_remove(struct graph *g, void *key)
{
	int i;     /* Loop index. */
	int uid;   /* Node id.    */
	void *obj; /* Object.     */
	
	SANITY_CHECK();
	
	uid = _graph_nodeid(g, key);
	
	/* Node not found. */
	if (uid < 0)
		return (NULL);
	
	/* Unlink node from all adjacent lists. */
	for (i = 0; i < g->size; i++)
	{
		/* Valid node. */
		if (g->nodes[i].obj != NULL)
			_graph_unlink(g, i, uid);
	}
		
	list_destroy(g->nodes[uid].adj);
	
	obj = g->nodes[uid].obj;
	g->nodes[uid].obj = NULL;
	g->nodes[uid].adj = NULL;
	
	return (obj);
}
