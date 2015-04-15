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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <omp.h>
#include <time.h>

#include <mylib/util.h>
#include "predict.h"

/* Program parameters. */
static const char **filenames = NULL; /* Name of input files.              */
unsigned nproteins = 0;               /* Number of proteins (input files). */
unsigned nfeatures = 0;               /* Number of features.               */
unsigned nselected = 0;               /* Number of selected features.      */
static unsigned popsize = 10;         /* Population size.                  */
static unsigned ngen = 50;            /* Number of generations.            */
static unsigned nthreads = 1;         /* Number of threads.                */
bool nested_threads = false;          /* Enable nested threads?            */
bool verbose = false;                 /* Be verbose?                       */

/**
 * @brief Database.
 */
struct database database;

/* Forward declarations. */
extern void predict(int popsize, int ngen);

/**
 * @brief Prints program usage and exits.
 * 
 * @details Prints program usage and exits gracefully.
 */
static void usage(void)
{
	printf("Usage: predict [options] ");
	printf("--nfeatures <num> --nselected <num> --proteins <files>\n");
	printf("Brief: ");
	printf("selects the best features to determine the class of a protein\n");
	printf("Options:\n");
	printf("  --help           Display this information exit\n");
	printf("  --nested-threads Enable nested threads\n");
	printf("  --popsize <num>  Population size\n");
	printf("  --ngen <num>     Number of generations to evolve\n");
	printf("  --nthreads <num> Number of threads to use\n");
	printf("  --verbose        Be verbose\n");
	
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
	enum parsing_states {
		STATE_READ_ARG,      /* Read argument.                   */
		STATE_SET_NTHREADS,  /* Set number of threads.           */
		STATE_SET_NFEATURES, /* Set number of features.          */
		STATE_SET_NSELECTED, /* Set number of selected features. */
		STATE_SET_PROTEINS,  /* Set protein files.               */
		STATE_SET_POPSIZE,   /* Set population size.             */
		STATE_SET_NGEN       /* Set number of generations.       */
	};
	
	int state;
	
	/* Parse command line parameters. */
	state = STATE_READ_ARG;
	for (int i = 0; i < argc; i++)
	{
		char *arg = argv[i];
		
		/* Set value. */
		if (state != STATE_READ_ARG)
		{
			switch (state)
			{
				/* Set number of threads. */
				case STATE_SET_NTHREADS:
					nthreads = atoi(arg);
					state = STATE_READ_ARG;
					break;
					
				/* Set number of features. */	
				case STATE_SET_NFEATURES:
					nfeatures = atoi(arg);
					state = STATE_READ_ARG;
					break;
				
				/* Set number of selected features. */
				case STATE_SET_NSELECTED:
					nselected = atoi(arg);
					state = STATE_READ_ARG;
					break;
				
				/* Set protein files. */
				case STATE_SET_PROTEINS:
					for (int j = i; argv[j] != NULL; j++)
						nproteins++;
					filenames = smalloc(nproteins*sizeof(char *));
					for (unsigned j = 0; j < nproteins; j++)
						filenames[j] = argv[i + j];
					i = argc;
					break;
				
				/* Set population size. */
				case STATE_SET_POPSIZE:
					popsize = atoi(arg);
					state = STATE_READ_ARG;
					break;
				
				/* Set number of generations to evolve. */
				case STATE_SET_NGEN:
					ngen = atoi(arg);
					state = STATE_READ_ARG;
					break;
				
				/* Wrong usage. */
				default:
					usage();
			}
			
			continue;
		}
		
		/* Parse argument. */
		if (!strcmp(arg, "--help"))
			usage();
		else if (!strcmp(arg, "--nthreads"))
			state = STATE_SET_NTHREADS;
		else if(!strcmp(arg, "--nested-threads"))
			nested_threads = true;
		else if (!strcmp(arg, "--nfeatures"))
			state = STATE_SET_NFEATURES;
		else if (!strcmp(arg, "--popsize"))
			state = STATE_SET_POPSIZE;
		else if (!strcmp(arg, "--ngen"))
			state = STATE_SET_NGEN;
		else if (!strcmp(arg, "--nselected"))
			state = STATE_SET_NSELECTED;
		else if (!strcmp(arg, "--nselected"))
			state = STATE_SET_NFEATURES;
		else if (!strcmp(arg, "--proteins"))
			state = STATE_SET_PROTEINS;
		else if (!strcmp(arg, "--verbose"))
			verbose = true;
	}
	
	/* Assert program parameters. */
	if (nfeatures == 0)
		error("invalid number of features");
	else if (nselected == 0)
		error("invalid number of selected of features");
	else if (popsize == 0)
		error("invalid population size");
	else if (ngen == 0)
		error("invalid number of generations");
	else if (nthreads == 0)
		error("invalid number of threads");
	else if (nproteins == 0)
		error("invalid number of proteins");
}

int main(int argc, char **argv)
{
	readargs(argc, argv);
	
	/* Initialization. */
	srandnum(time(NULL));
	set_nthreads(nthreads);
	omp_set_nested(nested_threads);
	database.naminoacids = smalloc(nproteins*sizeof(unsigned));
	
	/* Parse database. */
	info("parsing database...", VERBOSE_INFO);
	database_parse(filenames, nproteins);
	
	/* Read database. */
	info("reading database...", VERBOSE_INFO);
	database_read(filenames, nproteins, nfeatures);
	
	/* Predict features. */
	info("predcting...", VERBOSE_INFO);
	predict(popsize, ngen);
	
	/* House keeping. */
	database_destroy();
	free(filenames);
	
	return (EXIT_SUCCESS);
}
