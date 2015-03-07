/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * util/srealloc.c - srealloc() implementation.
 */

#include <stdlib.h>
#include <util.h>

/*
 * Safe realloc().
 */
void *srealloc(void *ptr, size_t size)
{	
	ptr = realloc(ptr, size);
	
	/* Failed to allocate memory. */
	if (ptr == NULL)
		error("cannot realloc()");
	
	return (ptr);	
}
