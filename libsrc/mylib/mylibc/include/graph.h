/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * <graph.h> - Graph library.
 */

#ifndef GRAPH_H_
#define GRAPH_H_

	#include "list.h"
	#include "object.h"

/*============================================================================*
 *                               Private Interface                            *
 *============================================================================*/

	/*
	 * Graph edge.
	 */
	struct gedge
	{
		int id;   /* Node ID.      */
		int cost; /* Cost to node. */
	};
	
	/*
	 * Graph node.
	 */
	struct gnode
	{
		int id;     /* ID.            */
		void *obj;  /* Object.        */
		list_t adj; /* Adjacent list. */
	};
	
	/*
	 * Graph.
	 */
	struct graph
	{
		int size;            /* Size (in nodes).    */
		int flags;           /* Flags (see below).  */
		struct gnode *nodes; /* Nodes.              */
		objinfo_t info;      /* Object information. */
	};
	
	/*
	 * Graph edge pointer caster.
	 */
	#define GEDGEP(x) \
		((struct gedge *)(x))
	
	/*
	 * Object graph node information.
	 */
	extern struct objinfo _gedge;
	
	/*
	 * Object graph node information.
	 */
	extern struct objinfo _gnode;
	
	/*
	 * Destroys a graph edge.
	 */
	extern void graph_edge_destroy(struct gedge *e);
	
	/*
	 * Gets the graph node ID of an object.
	 */
	extern int _graph_nodeid(struct graph *g, void *key);
	
	/*
	 * Internal implementation of graph_link().
	 */
	extern void _graph_wlink(struct graph *g, int uid, int vid, int cost);
	
	/*
	 * Internal implementation of graph_unlink().
	 */
	extern int _graph_unlink(struct graph *g, int u, int v);

/*============================================================================*
 *                                Public Interface                            *
 *============================================================================*/

	/* Graph flags. */
	#define GRAPH_WEIGHTED 1 /* Weighted graph? */
	#define GRAPH_DIRECTED 2 /* Directed graph? */

	/*
	 * Opaque pointer to a graph.
	 */
	typedef struct graph * graph_t;
	
	/*
	 * Creates a graph.
	 */
	extern graph_t graph_create(objinfo_t info, int size, int flags);
	
	/*
	 * Destroys a graph.
	 */
	extern void graph_destroy(graph_t g);
	
	/*
	 * Dijkstra's algorithm.
	 */
	extern list_t graph_dijkstra(struct graph *g, void *ukey, void *vkey);
	
	/*
	 * Inserts an object in a graph.
	 */
	extern int graph_insert(graph_t g, void *obj);
	
	/*
	 * Links two nodes of a graph. 
	 */
	extern int graph_link(graph_t g, void *u_key, void *v_key);

	/*
	 * Removes an object from a graph.
	 */
	extern void *graph_remove(graph_t g, void *key);
	
	/*
	 * Returns the size of a graph.
	 */
	#define graph_size(g)    \
		(((graph_t)(g))->size) \
	
	/*
	 * Swaps two nodes of a graph.
	 */
	extern int graph_swap(graph_t g, void *u_key, void *v_key);
	
	/*
	 * Unlinks two nodes of a graph.
	 */
	extern int graph_unlink(graph_t g, void *u_key, void *v_key);
	
	/*
	 * Links two nodes of a weighted graph.
	 */
	extern int graph_wlink(graph_t g, void *u_key, void *v_key, int cost);

#endif /* GRAPH_H_ */
