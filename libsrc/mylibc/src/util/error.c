/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * util/error.c - error() implementation.
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * Prints an error message and exits.
 */
void error(const char *msg)
{
	fprintf(stderr, "error: %s\n", msg);
	exit(EXIT_FAILURE);
}
