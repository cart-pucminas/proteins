/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * graph/graph_unlink.c - graph_unlink() implementation.
 */
 
#include <graph.h>
#include <stdlib.h>
#include <util.h>

/*
 * Destroys a graph edge.
 */
void graph_edge_destroy(struct gedge *e)
{
	free(e);
}

/*
 * Internal implementation of graph_unlink().
 */
int _graph_unlink(struct graph *g, int uid, int vid)
{
	struct gedge *u, *v;

	/* Destroy graph node. */
	v = list_remove(g->nodes[uid].adj, &vid);
	if (v == NULL)
		return (-1);
		
	graph_edge_destroy(v);
	
	/* Bidirectional graph. */
	if (!(g->flags & GRAPH_DIRECTED))
	{
		u = list_remove(g->nodes[vid].adj, &uid);
		
		/* Destroy graph node. */
		if (u == NULL)
			error("broken graph");
		
		graph_edge_destroy(u);
	}
	
	return (0);
}

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
 * Unlinks two nodes of a graph.
 */
int graph_unlink(struct graph *g, void *u_key, void *v_key)
{
	int uid, vid;
	
	uid = _graph_nodeid(g, u_key);
	vid = _graph_nodeid(g, v_key);
	
	/* Invalid argument(s). */
	if ((uid < 0) || (vid < 0))
	{
		warning("cannot graph_unlink()");
		return (-1);
	}
	
	return (_graph_unlink(g, uid, vid));
}
