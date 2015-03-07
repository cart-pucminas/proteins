/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * graph/graph_dijkstra.c - graph_dijkstra() implementation.
 */

#include <assert.h>
#include <graph.h>
#include <limits.h>
#include <list.h>
#include <object.h>
#include <pqueue.h>
#include <util.h>

/* Node colors. */
#define WHITE 0 /* White.    */
#define BLACK 1 /* Black.    */

/*
 * Internal Dijkstra's algorithm.
 */
static list_t _graph_dijkstra(struct graph *g, struct gnode *u, struct gnode *v)
{
	int i;                  /* Loop index.     */
	lnode_t it;             /* List iterator.  */
	list_t path;            /* Path.           */
	int *distance;          /* Path distances. */
	char *colors;           /* Node colors.    */
	struct gedge *e;        /* Working edge.   */
	pqueue_t fringe;        /* Fringe nodes.   */
	int newdistance;        /* New distance.   */
	struct gnode **parents; /* Node parents.   */
	
	path = list_create(g->info);
	fringe = pqueue_create(&_gnode, g->size);
	distance = smalloc(g->size*sizeof(int));
	parents = smalloc(g->size*sizeof(struct gnode *));
	colors = smalloc(g->size*sizeof(char));
	
	/* Initialize nodes. */
	distance[u->id] = 0;
	for (i = 0; i < g->size; i++)
	{
		/* Skip source node. */
		if (i != u->id)
			distance[i] = INT_MAX;
		
		parents[i] = NULL;
		colors[i] = WHITE;
		pqueue_insert(fringe, &g->nodes[i], distance[i]);
	}
	
	/* Find the shortest path. */
	while (!pqueue_empty(fringe))
	{
		u = pqueue_remove(fringe, NULL);
		
		/* Path found. */
		if (u == v)
		{
			/* Build path. */
			do
			{
				list_insert(path, u->obj);
				u = parents[u->id];
			} while (u != NULL);
			
			goto found;
		}
		
		colors[u->id] = BLACK;
		
		/* Expand children nodes. */
		for (it = list_first(u->adj); it != NULL; it = list_next(it))
		{
			e = GEDGEP(list_object(it));
			
			/* Expand this node. */
			if (colors[e->id] == WHITE)
			{
				newdistance = distance[u->id] + e->cost;
				
				/* Change distance. */
				if (newdistance < distance[e->id])
				{
					distance[e->id] = newdistance;
					parents[e->id] = u;
					pqueue_change(fringe, &g->nodes[e->id], newdistance);
				}
			}
		}
	}
	
found:
	
	/* Book keeping. */
	free(colors);
	free(parents);
	free(distance);
	pqueue_destroy(fringe);
	
	return (path);
}

/*
 * Arguments sanity check.
 */
#define SANITY_CHECK()    \
	assert(g != NULL);    \
	assert(ukey != NULL); \
	assert(vkey != NULL); \

/*
 * Dijkstra's algorithm.
 */
list_t graph_dijkstra(struct graph *g, void *ukey, void *vkey)
{
	int uid; /* ID of node u. */
	int vid; /* ID of node v. */
	
	SANITY_CHECK();
	
	uid = _graph_nodeid(g, ukey);
	vid = _graph_nodeid(g, vkey);
	
	/* Invalid argument(s). */
	if ((uid < 0) || (vid < 0))
	{
		warning("cannot get graph node IDs");
		return (NULL);
	}

	return (_graph_dijkstra(g, &g->nodes[uid], &g->nodes[vid]));
}
