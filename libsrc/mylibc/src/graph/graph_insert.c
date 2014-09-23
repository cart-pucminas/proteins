/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * graph/graph_insert.c - graph_insert() implementation.
 */

#include <assert.h>
#include <graph.h>
#include <list.h>
#include <object.h>

/*
 * Arguments sanity check.
 */
#define SANITY_CHECK()               \
	assert(g != NULL);               \
	assert(g->info->getkey != NULL); \
	assert(g->info->hash != NULL);   \
	assert(g != NULL);               \
	assert(obj != NULL);             \

/*
 * Inserts an object in a graph.
 */
int graph_insert(struct graph *g, void *obj)
{
	int i;     /* Loop index. */
	int id;    /* Object ID.  */
	void *key; /* Object key. */
	
	SANITY_CHECK();
	
	key = GETKEY(g->info, obj);
	id = HASH(g->info, key)%g->size;
	
	/* Index found. */
	if (g->nodes[id].obj == NULL)
		goto found;
	
	/* Find available index not available. */
	for (i = (id + 1)%g->size; i != id; i = (i + 1)%g->size)
	{
		/* Found. */
		if (g->nodes[i].obj == NULL)
		{
			id = i;
			goto found;
		}
	}
	
	return (-1);

found:

	/* Insert object in the graph. */
	g->nodes[id].adj = list_create(&_gedge);
	g->nodes[id].obj = obj;
	
	return (0);
}
