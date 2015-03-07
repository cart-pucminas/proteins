/*
 * Copyright(C) 2013 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * algorithm/auction/auction.c - Auction algorithm implementation.
 */

#include <stdlib.h>
#include <matrix.h>

/* Useful macros. */
#define WITHOUT_OBJECT -1 /* Person without an object. */
#define WITHOUT_OWNER -1  /* Object without an owner.  */

/*
 * Finds a person without an object.
 */
static int find_person(int *people, int n)
{
	int i;
	
	/* Find a person without an object. */
	for (i = 0; i < n; i++)
	{
		/* Found. */
		if (people[i] == WITHOUT_OBJECT)
			return (i);
	}
	
	return (-1);
}

/*
 * Solves the assignment problem.
 */
int *auction(matrix_t prices, double slack)
{
	int n;         /* Number of objects to assign.  */
	int i, j;      /* Loop indexes.                 */
	int first;     /* Index of girst greatest bid.  */
	int second;    /* Index of second greatest bid. */
	int *people;   /* Belongings of the people.     */
	double *bids;  /* Objects' bids.                */
	int *objects;  /* Owners of the objects.        */
	
	#define BID(i, j) \
		(MATRIX(prices, i, j) - bids[j])
	
	/* Invalid argument. */
	if (matrix_height(prices) != matrix_width(prices))
		goto error0;
	else if (matrix_height(prices) < 2)
		goto error0;
	
	n = matrix_width(prices);
	
	bids = malloc(n*sizeof(double));
	
	/* Faild to allocate bids array. */
	if (bids == NULL)
		goto error0;
		
	people = malloc(n*sizeof(int));
	
	/* Failed to allocate people array. */
	if (people == NULL)
		goto error1;
	
	objects = malloc(n*sizeof(int));
	
	/* Failed to allocate objects array. */
	if (objects == NULL)
		goto error2;
	
	/* Initialize internal data. */
	for (i = 0; i < n; i++)
	{
		bids[i] = 0;
		people[i] = WITHOUT_OBJECT;
		objects[i] = WITHOUT_OWNER;
	}
	
	/* Assign objects to the people. */
	while ((i = find_person(people, n)) != -1)
	{	
		second = 0, first = 1;
		if (BID(i, second) >= BID(i, first))
			second = 1, first = 0;
		
		/* Find bid. */
		for (j = 2; j < n; j++)
		{			
			/* First greatest bid found. */
			if (BID(i, j) >= BID(i, first))
			{
				second = first;
				first = j;
			}
			
			/* Second greatest bid found. */
			else if (BID(i, j) > BID(i, second))
				second = j;
		}
		
		bids[first] += BID(i, first) - BID(i, second) + slack;
		
		/* Assign object to person. */
		people[i] = first;
		if (objects[first] != WITHOUT_OWNER)
			people[objects[first]] = WITHOUT_OBJECT;
		objects[first] = i;
	}
	
	free(objects);
	free(bids);
	
	return (people);

error2:
	free(people);
error1:
	free(bids);
error0:
	return (NULL);
}
