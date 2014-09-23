/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * <stack.h> - Stack library.
 */

#ifndef STACK_H_
#define STACK_H_

	#include "object.h"

/*============================================================================*
 *                               Private Interface                            *
 *============================================================================*/

	/*
	 * Stack node.
	 */
	struct stack_node
	{
		void *obj;               /* Object.                   */
		struct stack_node *next; /* Next object in the stack. */
	};
	
	/*
	 * Stack.
	 */
	struct stack
	{
		int size;               /* Stack size.                  */
		struct stack_node *top; /* Topmost object in the stack. */
		objinfo_t info;         /* Object information.          */    
	};

/*============================================================================*
 *                                Public Interface                            *
 *============================================================================*/
	
	/*
	 * Opaque pointer to a stack.
	 */
	typedef struct stack *stack_t;
	
	/*
	 * Creates a stack.
	 */
	extern stack_t stack_create(objinfo_t info);
	
	/*
	 * Destroys a stack.
	 */
	extern void stack_destroy(stack_t s);
	
	/*
	 * Asserts if the stack is empty.
	 */
	#define stack_empty(s) \
		((stack_t)(s)->size == 0)
	
	/*
	 * Pops an object from a stack.
	 */
	extern void *stack_pop(stack_t s);
	
	/*
	 * Pushes an object on a stack.
	 */
	extern void stack_push(stack_t s, void *obj);
	
	/*
	 * Returns the size of a stack.
	 */
	#define stack_size(s) \
		((stack_t)(s)->size)

#endif /* STACK_H_ */
