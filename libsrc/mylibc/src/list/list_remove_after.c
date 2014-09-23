/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * list/list_remove_after.c - list_remove_after() implementation.
 */

#include <list.h>
#include <stdlib.h>
#include <util.h>

/*
 * Removes the object after a given node from a linked list.
 */
void *list_remove_after(struct list *l, struct list_node *n)
{
	void *obj;            /* Object        */
	struct list_node *np; /* Node pointer. */
	
	/* The list is empty. */
	if (list_length(l) == 0)
		return (NULL);
	
	/* Invalid argument. */
	if (n->next == NULL)
	{
		warning("cannot list_remove_after()");
		return (NULL);
	}
	
	/* Remove node. */
	np = n->next;
	n->next = np->next;
	l->length--;
	
	/* Update last node. */
	if (l->last == np)
		l->last = n;
	
	/* Destroy node. */
	obj = list_object(np);
	free(np);
	
	return (obj);
}
