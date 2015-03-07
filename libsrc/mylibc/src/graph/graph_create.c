/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * graph/graph_create.c - graph_create() implementation.
 */

#include <assert.h>
#include <graph.h>
#include <list.h>
#include <object.h>
#include <stdlib.h>
#include <util.h>

/*
 * Arguments sanity check.
 */
#define SANITY_CHECK()    \
	assert(info != NULL); \
	assert(size > 0);     \

/*
 * Creates a graph.
 */
struct graph *graph_create(objinfo_t info, int size, int flags)
{
	int i;               /* Loop index.  */
	struct graph *g;     /* Graph.       */
	struct gnode *nodes; /* Graph nodes. */
	
	SANITY_CHECK();
	
	/* Allocate internal data. */
	g = smalloc(sizeof(struct graph));
	nodes = smalloc(size*(sizeof(struct gnode)));
	
	/* Initialize graph. */
	for (i = 0; i < size; i++)
	{
		nodes[i].id = i;
		nodes[i].obj = NULL;
		nodes[i].adj = NULL;
	}
	g->size = size;
	g->flags = flags;
	g->nodes = nodes;
	g->info = info;
	
	return (g);
}
