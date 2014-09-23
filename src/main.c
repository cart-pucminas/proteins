/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>,
 *                   Larissa Leijôto <larissa.leijoto@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>

/* Forward declarations. */
extern void predict(int popsize, int ngen);

/*
 * Reads command line arguments. 
 */
static void readargs(int argc, char **argv)
{
	((void)argc); /* Unused. */
	((void)argv); /* Unused. */
	
	/*
	 * TODO: read and parse command line
	 *       arguments.
	 */
}

int main(int argc, char **argv)
{
	
	readargs(argc, argv);
	
	predict(100, 100);
	
	return (EXIT_SUCCESS);
}
