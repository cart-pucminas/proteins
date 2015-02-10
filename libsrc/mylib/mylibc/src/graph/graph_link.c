/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * graph/graph_insert.c - graph_insert() implementation.
 */

#include <assert.h>
#include <graph.h>
#include <util.h>

/*
 * Create a graph node.
 */
static struct gedge *graph_edge_create(int id, int cost)
{
	struct gedge *e;
	
	e = smalloc(sizeof(struct gedge));
	
	e->id = id;
	e->cost = cost;
	
	return (e);
}

/*
 * Internal implementation of graph_link().
 */
void _graph_wlink(struct graph *g, int uid, int vid, int cost)
{
	struct gedge *u, *v;
	
	v = graph_edge_create(vid, cost);
	
	/* Bidirectional graph. */
	if (!(g->flags & GRAPH_DIRECTED))
	{
		u = graph_edge_create(uid, cost);
		list_insert(g->nodes[vid].adj, u);
	}
	
	list_insert(g->nodes[uid].adj, v);
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
 * Links two nodes of a weighted graph.
 */
int graph_wlink(struct graph *g, void *u_key, void *v_key, int cost)
{
	int uid, vid;
	
	SANITY_CHECK();
		
	uid = _graph_nodeid(g, u_key);
	vid = _graph_nodeid(g, v_key);
	
	/* Invalid key(s). */
	if ((uid < 0) || (vid < 0))
	{
		warning("cannot graph_wlink()");
		return (-1);
	}
	
	_graph_wlink(g, uid, vid, cost);
	
	return (0);
}

/*
 * Links two nodes of a graph.
 */
int graph_link(struct graph *g, void *u_key, void *v_key)
{
	int uid, vid;
	
	SANITY_CHECK();
		
	uid = _graph_nodeid(g, u_key);
	vid = _graph_nodeid(g, v_key);
	
	/* Invalid key(s). */
	if ((uid < 0) || (vid < 0))
	{
		warning("cannot graph_link()");
		return (-1);
	}
	
	_graph_wlink(g, uid, vid, 1);
	
	return (0);
}
