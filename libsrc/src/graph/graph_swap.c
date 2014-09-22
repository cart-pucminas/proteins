/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * graph/graph_swap.c - graph_swap() implementation.
 */

#include <assert.h>
#include <graph.h>
#include <util.h>

/*
 * Arguments sanity check.
 */
#define SANITY_CHECK()               \
	assert(g != NULL);               \
	assert(g->info->hash != NULL);   \
	assert(g->info->getkey != NULL); \
	assert(g->info->cmp != NULL);    \
	assert(u_key != NULL);           \
	assert(v_key != NULL);           \

/*
 * Swaps two nodes of a graph.
 */
int graph_swap(graph_t g, void *u_key, void *v_key)
{
	void *tmp;    /* Swap variable. */
	int uid, vid; /* Node IDs.      */
	
	SANITY_CHECK();
		
	uid = _graph_nodeid(g, u_key);
	vid = _graph_nodeid(g, v_key);
	
	/* Invalid key(s). */
	if ((uid < 0) || (vid < 0))
	{
		warning("cannot graph_link()");
		return (-1);
	}
	
	swap(g->nodes[uid].obj, g->nodes[vid].obj, tmp);
	
	return (0);
}
