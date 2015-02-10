/*
 * Copyright(C) 2015 Pedro H. Penna  <pedrohenriquepenna@gmail.com>,
 *                   Larissa Leijoto <larissa.leijoto@gmail.com>
 * 
 * This file is part of Proteins.
 * 
 * Proteins is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Proteins is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Proteins. If not, see <http://www.gnu.org/licenses/>.
 */

#include <mylib/util.h>
#include <stdio.h>
#include <stdlib.h>

/* Program parameters. */
static const char *filenames = NULL; /* Name of input files.              */
static unsigned nproteins = 0;       /* Number of proteins (input files). */
static unsigned nfeatures = 0;       /* Number of features.               */

/* Forward declarations. */
extern void predict(int popsize, int ngen);

/**
 * @brief Prints program usage and exits.
 * 
 * @details Prints program usage and exits.
 */
static void usage(void)
{
	printf("Usage: proteins <nfeatures> <input files>");
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
	((void)argc); /* Unused. */
	((void)argv); /* Unused. */
	
	/* Missing arguments. */
	if (argc < 3)
		error("missing arguments");
	
	/*
	 * TODO: read and parse command line
	 *       arguments.
	 */
	
	/* Assert program parameters. */
	if (nproteins == 0)
		error("invalid number of proteins");
	else if (nfeatures == 0);
		error("invalid number of features");
}

int main(int argc, char **argv)
{
	unsigned naminoacids; /* Number of amino acids. */
	float **database;     /* Data base.             */
	
	readargs(argc, argv);
	
	/*
	 * Parse database in order to determine the largest
	 * number of amino acids among all proteins.
	 */
	naminoacids = database_parse(filename, nproteins, nfeatures);
	if (naminoacids == 0)
		error("invalid number of amino acids");
	
	/* Read database. */
	database = database_read(filenames, nproteins, nfeatures, naminoacids);
	
	predict(100, 100);
	
	/* House keeping. */
	free(database);
	
	return (EXIT_SUCCESS);
}
