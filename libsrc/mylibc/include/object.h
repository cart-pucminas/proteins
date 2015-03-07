/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * <object.h> - Object library.
 */

#ifndef OBJECT_H_
#define OBJECT_H_

	#include <stdio.h>

/*============================================================================*
 *                               Private Interface                            *
 *============================================================================*/

	/*
	 * Object information.
	 */
	struct objinfo
	{
		/* Object functions. */
		void *(*read)(FILE *);                  /* Read.         */
		void (*write)(FILE *, const void *);    /* Write.        */
		int (*cmp)(const void *, const void *); /* Compare keys. */
		void *(*getkey)(const void *);          /* Get key.      */
		int (*hash)(const void *);              /* Compute hash. */
		void *(*clone)(const void *);           /* Clone object. */
	};

/*============================================================================*
 *                                Public Interface                            *
 *============================================================================*/

	/*
	 * Opaque pointer to object information.
	 */
	typedef struct objinfo * objinfo_t;

	/*
	 * Clones an object.
	 */
	#define CLONE(info, obj) \
		((info)->clone(obj))
	
	/*
	 * Compares two keys.
	 */
	#define CMP(info, key1, key2) \
		((info)->cmp(key1, key2))
	
	/*
	 * Gets object's key.
	 */
	#define GETKEY(info, obj) \
		((info)->getkey(obj))
	
	/*
	 * Computes hash value.
	 */
	#define HASH(info, key) \
		((info)->hash(key))
	
	/*
	 * Reads object from a file.
	 */
	#define READ(info, file) \
		((info)->read((file)))
	
	/*
	 * Writes object to a file.
	 */
	#define WRITE(info, file, obj) \
		((info)->write((file), (obj)))
	
	/*
	 * Integer object information.
	 */
	extern struct objinfo integer;
	
	/*
	 * Vector object information.
	 */
	extern struct objinfo vector;

#endif /* OBJECT_H_ */
