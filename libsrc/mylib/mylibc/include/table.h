/*
 * Copyright(C) 2011-2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * <table.h> - Table library.
 */

#ifndef TABLE_H_
#define TABLE_H_

	#include "object.h"

/*============================================================================*
 *                               Private Interface                            *
 *============================================================================*/
 
	/*
	 * Table.
	 */
	struct table
	{
		int height;     /* Height.             */
		int width;      /* Width.              */
		void **objects; /* Objects.            */
		objinfo_t info; /* Object information. */
	};

/*============================================================================*
 *                                Public Interface                            *
 *============================================================================*/

	/*
	 * Opaque pointer to a table.
	 */
	typedef struct table * table_t;
	
	/*
	 * Creates a table.
	 */
	extern table_t table_create(objinfo_t info, int height, int width);
	
	/*
	 * Destroys a table.
	 */
	extern void table_destroy(table_t t);
	
	/*
	 * Returns the element [i, j] of a table.
	 */
	#define TABLE(t, i, j) \
		(((table_t)(t))->objects[((table_t)(t))->width*(i) + (j)])

#endif /* TABLE_H_ */
