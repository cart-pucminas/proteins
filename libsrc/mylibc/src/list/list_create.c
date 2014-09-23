/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * list/list_create.c - list_create() implementation.
 */
 
#include <list.h>
#include <object.h>
#include <stdlib.h>
#include <util.h>

/*
 * Creates a linked list.
 */
struct list *list_create(objinfo_t info)
{
	struct list *l;         /* List.      */
	struct list_node *head; /* Head node. */
	
	/* Allocate objects. */
	l = smalloc(sizeof(struct list));
	head = smalloc(sizeof(struct list_node));
	
	/* Initialize list. */
	l->length = 0;
	head->next = NULL;
	l->head = head;
	l->last = head;
	l->info = info;
	
	return (l);
}
