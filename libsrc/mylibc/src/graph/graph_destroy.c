/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * graph/graph_destroy.c - graph_destroy() implementation.
 */

#include <assert.h>
#include <graph.h>
#include <list.h>
#include <stdlib.h>

/*
 * Arguments sanity check.
 */
#define SANITY_CHECK() \
	assert(g != NULL); \

/*
 * Destroys a graph.
 */
void graph_destroy(struct graph *g)
{
	int i;
	
	SANITY_CHECK();
	
	/* House keeping. */
	for (i = 0; i < g->size; i++)
	{
		/* Valid ajdacent list. */
		if (g->nodes[i].adj != NULL)
		{
			/* Destroy list. */
			while (list_length(g->nodes[i].adj) > 0)
				graph_edge_destroy(list_remove_first(g->nodes[i].adj));
			list_destroy(g->nodes[i].adj);
		}
	}
	free(g->nodes);
	free(g);
}
