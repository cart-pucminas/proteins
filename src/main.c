/*
 * Copyright(C) 2015 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 *                   Larissa Leijoto <larissa.leijoto@gmail.com>
 *
 * This file is part of Predict.
 *
 * Predict is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Predict is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Predict. If not, see <http://www.gnu.org/licenses/>.
 */

#include <mylib/util.h>
#include <stdio.h>
#include <stdlib.h>
#include "predict.h"
	

/* Program parameters. */
static const char **filenames = NULL; /* Name of input files.              */
unsigned nproteins = 0;               /* Number of proteins (input files). */
unsigned nfeatures = 0;               /* Number of features.               */
unsigned nselected = 0;               /* Number of selected features.      */
static unsigned popsize = 0;          /* Population size.                  */
static unsigned ngen = 0;             /* Number of generations.            */

/**
 * @brief Database.
 */
struct database database;

/* Forward declarations. */
extern void predict(int popsize, int ngen);

/**
 * @brief Prints program usage and exits.
 * 
 * @details Prints program usage and exits.
 */
static void usage(void)
{
	printf("Usage: predict <nfeatures> <nselected> <popsize> <ngen> <protein files>");
	exit(EXIT_SUCCESS);
}

/**
 * @brief Reads command line arguments.
 * 
 * @details Reads and parses command line arguments pointed to by @p argv.
 * 
 * @todo Read and parse command line arguments.
 */
static void readargs(int argc, char **argv)
{
	/* Missing arguments. */
	if (argc < 6)
		usage();
	
	nfeatures = atoi(argv[1]);
	nselected = atoi(argv[2]);
	popsize = atoi(argv[3]);
	ngen = atoi(argv[4]);
	
	/* Count the number of proteins. */
	for (unsigned i = 5; argv[i] != NULL; i++)
		nproteins++;
		
	filenames = smalloc(nproteins*sizeof(char *));
	
	/* Extract protein files. */
	for (unsigned i = 0; i < nproteins; i++)
		filenames[i] = argv[5 + i];
	
	/* Assert program parameters. */
	if (nfeatures == 0)
		error("invalid number of features");
	else if (nselected == 0)
		error("invalid number of selected of features");
	else if (popsize == 0)
		error("invalid population size");
	else if (ngen == 0)
		error("invalid number of generations");
}

int main(int argc, char **argv)
{
	readargs(argc, argv);
	
	database.naminoacids = smalloc(nproteins*sizeof(unsigned));
	
	fprintf(stderr, "info: parsing database...\n");
	
	/*
	 * Parse database in order to determine the largest
	 * number of amino acids among all proteins.
	 */
	database_parse(filenames, nproteins);
	
	fprintf(stderr, "info: reading database...\n");
	
	/* Read database. */
	database_read(filenames, nproteins, nfeatures);
	
	fprintf(stderr, "info: predcting...\n");
	
	predict(popsize, ngen);
	
	/* House keeping. */
	database_destroy();
	free(filenames);
	
	return (EXIT_SUCCESS);
}
