/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * object/integer.c - Integer object information.
 */

#include <object.h>
#include <util.h>

/*
 * Compares two keys.
 */
static int integer_cmp(const void *key1, const void *key2)
{
	if (*INTP(key1) < *INTP(key2))
		return (-1);
	if (*INTP(key1) > *INTP(key2))
		return (1);
	
	return (0);
}

/*
 * Gets integer key.
 */
static void *integer_getkey(const void *obj)
{
	return ((void *)obj);
}

/*
 * Computes hash value.
 */
static int integer_hash(const void *key)
{
	return (*INTP(key));
}

/*
 * Integer object information.
 */
struct objinfo integer =
{
	NULL,           /* read()   */
	NULL,           /* write()  */
	integer_cmp,    /* cmp()    */
	integer_getkey, /* getkey() */
	integer_hash,   /* hash()   */
	NULL            /* clone()  */
};
