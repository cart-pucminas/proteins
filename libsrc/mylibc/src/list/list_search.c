/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * list/list_search.c - list_search() implementation.
 */

#include <list.h>
#include <util.h>

/*
 * Searches for an object in a linked list.
 */
void *list_search(struct list *l, const void *key)
{
	struct list_node *np; /* Node pointer. */
	struct list_node *w;  /* List walker.  */
	
	/* Invalid argument(s). */
	if ((l->info->cmp == NULL) || (l->info->getkey == NULL))
	{
		warning("cannot list_search()");
		return (NULL);
	}
	
	/* Search for object. */
	for (w = l->head; w->next != NULL; w = w->next)
	{
		/* Found. */
		if (!CMP(l->info, GETKEY(l->info, w->next->obj), key))
			goto found;
	}

	return (NULL);

found:

	/* Speed up next search. */
	np = w->next;
	w->next = np->next;
	np->next = l->head->next;
	l->head->next = np;

	return (list_object(np));
}
