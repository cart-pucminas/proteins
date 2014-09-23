/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * <array.h> - Array library.
 */

#ifndef ARRAY_H_
#define ARRAY_H_

	#include "object.h"

/*============================================================================*
 *                               Private Interface                            *
 *============================================================================*/

	/*
	 * Array of objects.
	 */
	struct array
	{
		int size;       /* Size.               */
		void **objects; /* Stored objects.     */
		objinfo_t info; /* Object information. */
	};

/*============================================================================*
 *                                Public Interface                            *
 *============================================================================*/

	/*
	 * Opaque pointer to an array.
	 */
	typedef struct array * array_t;
	
	/*
	 * Creates an array.
	 */
	extern array_t array_create(objinfo_t info, int size);
	
	/*
	 * Destroys an array.
	 */
	extern void array_destroy(array_t a);
	
	/*
	 * Searches for an object in an array.
	 */
	extern int array_search(array_t a, void *key);
		
	/*
	 * Shuffles an array.
	 */
	extern void array_shuffle(struct array *a);
	
	/*
	 * Returns the size of an array.
	 */
	#define array_size(a) \
		(((array_t)(a))->size)

	/*
	 * Sorts an array.
	 */
	extern void array_sort(struct array *a);
	
	/*
	 * Returns the i-th object of an array.
	 */
	#define ARRAY(a, i) \
		(((array_t)(a))->objects[(i)])

#endif /* ARRAY_H_ */
