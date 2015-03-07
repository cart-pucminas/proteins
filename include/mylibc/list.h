/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * <list.h> - Linked list library.
 */

#ifndef LIST_H_
#define LIST_H_

	#include "object.h"

/*============================================================================*
 *                               Private Interface                            *
 *============================================================================*/

	/*
	 * Linked list node.
	 */
	struct list_node
	{
		void *obj;              /* Object.    */
		struct list_node *next; /* Next node. */
	};

	/*
	 * Linked list.
	 */
	struct list
	{
		int length;             /* Number of nodes.    */
		struct list_node *head; /* Head node.          */
		struct list_node *last; /* Last node.          */
		objinfo_t info;         /* Object information. */
	};

/*============================================================================*
 *                                Public Interface                            *
 *============================================================================*/

	/*
	 * Opaque pointer to a linked list.
	 */
	typedef struct list * list_t;
	
	/*
	 * Opaque pointer to a linked list node.
	 */
	typedef struct list_node * lnode_t;

	/*
	 * Creates a linked list.
	 */
	extern list_t list_create(objinfo_t info);
	
	/*
	 * Destroys a linked list.
	 */
	extern void list_destroy(list_t l);
		
	/*
	 * Inserts an object after a given node in a linked list.
	 */
	extern int list_insert_after(list_t l, lnode_t n, void *obj);
	
	/*
	 * Inserts an object in the end of a linked list.
	 */
	#define list_insert_last(l, n, obj) \
		(list_insert_after((l), (list_t)(l)->last), (obj))
	
	/*
	 * Removes an object from a linked list.
	 */
	extern void *list_remove(list_t l, const void *key);
	
	/*
	 * Removes the object after a given node from a linked list.
	 */
	extern void *list_remove_after(list_t l, lnode_t n);

	/*
	 * Searches for an object in a linked list.
	 */
	extern void *list_search(list_t l, const void *key);

	/*
	 * Returns the first node of a linked list.
	 */
	#define list_first(l) \
		(((list_t)(l))->head->next)
		
	/*
	 * Returns the head node of a linked list.
	 */
	#define list_head(l) \
		(((list_t)(l))->head)
	
	/*
	 * Inserts an object in a linked list.
	 */
	#define list_insert(l, obj) \
		(list_insert_after((l), list_head((l)), (obj)))

	/*
	 * Returns the length of a linked list.
	 */
	#define list_length(l) \
		(((list_t)(l))->length)

	/*
	 * Returns the next linked list node.
	 */
	#define list_next(n) \
		(((lnode_t)(n))->next)
	
	/*
	 * Returns the object stored in a linked list node.
	 */
	#define list_object(n) \
		(((lnode_t)(n))->obj)
	
	/*
	 * Removes the first object of a linked list.
	 */
	#define list_remove_first(l) \
		list_remove_after((l), list_head((l)))

#endif /* LIST_H_ */
