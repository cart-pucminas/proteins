/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * list/list_insert_after.c - list_insert_after() implementation().
 */

#include <list.h>
#include <util.h>

/*
 * Creates a list node.
 */
static struct list_node *list_node_create(void *obj)
{
	struct list_node *node;
	
	node = smalloc(sizeof(struct list_node));
	node->obj = obj;
	node->next = NULL;
	
	return (node);
}

/*
 * Inserts an object after a given node in a linked list.
 */
int list_insert_after(struct list *l, struct list_node *n, void *obj)
{
	struct list_node *new;
	
	new = list_node_create(obj);
	
	/* Insert new node in the list. */
	new->next = n->next;
	n->next = new;
	l->length++;
	
	/* Update last node. */
	if (l->last == n)
		l->last = new;
	
	return (l->length);
}
