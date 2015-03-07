/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * util/smalloc.c - scalloc() implementation.
 */

#include <stdlib.h>
#include <util.h>

/*
 * Safe calloc().
 */
void *scalloc(size_t nmemb, size_t size)
{
	void *ptr;
	
	ptr = calloc(nmemb, size);
	
	/* Failed to allocate memory. */
	if (ptr == NULL)
		error("cannot malloc()");
	
	return (ptr);	
}
