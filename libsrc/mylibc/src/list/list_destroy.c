/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * list/list_destroy.c - list_destroy() implementation.
 */

#include <list.h>
#include <stdlib.h>

/*
 * Destroys a linked list.
 */
void list_destroy(struct list *l)
{
	/* Remove all objects from the list. */
	while (list_length(l) > 0)
		list_remove_after(l, list_head(l));
	
	/* House keeping. */
	free(l->head);
	free(l);
}
