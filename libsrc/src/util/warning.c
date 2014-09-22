/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * util/warning.c - warning() implementation.
 */

#include <stdio.h>

/*
 * Prints a warning message.
 */
void warning(const char *msg)
{
	fprintf(stderr, "warning: %s\n", msg);
}
