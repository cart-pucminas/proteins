/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * util/smalloc.c - smalloc() implementation.
 */

#include <stdlib.h>
#include <util.h>

/*
 * Safe malloc().
 */
void *smalloc(size_t size)
{
	void *ptr;
	
	ptr = malloc(size);
	
	/* Failed to allocate memory. */
	if (ptr == NULL)
		error("cannot malloc()");
	
	return (ptr);	
}
