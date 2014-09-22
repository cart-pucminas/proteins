/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * list/list_remove.c - list_remove() implementation.
 */

#include <assert.h>
#include <list.h>
#include <object.h>
#include <util.h>

/*
 * Arguments sanity check.
 */
#define SANITY_CHECK()   \
	assert(l != NULL);   \
	assert(key != NULL); \

/*
 * Removes an object from a linked list.
 */
void *list_remove(struct list *l, const void *key)
{
	struct list_node *w;
	
	SANITY_CHECK();
	
	/* Invalid argument(s). */
	if ((l->info->cmp == NULL) || (l->info->getkey == NULL))
	{
		warning("cannot list_remove()");
		return (NULL);
	}
	
	/* Search for object. */
	for (w = l->head; w->next != NULL; w = w->next)
	{
		/* Found. */
		if (!CMP(l->info, GETKEY(l->info, w->next->obj), key))
			return (list_remove_after(l, w));
	}

	return (NULL);
}
