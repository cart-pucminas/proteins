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

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <util.h>
#include "predict.h"

/**
 * @brief Parses the database.
 *
 * @details Parses the database so that we can determine the largest number of
 *          amino acids among all proteins.
 *
 * @param filenames Name of input files.
 * @nproteins       Number of proteins (number of input files).
 * @nfeatures       Number of features for all proteins.
 *
 * @returns The largest number of amino acids among all proteins.
 * 
 * @todo Check for bad file format.
 */
void database_parse
(const char *filenames, unsigned nproteins, unsigned nfeatures)
{
	/* Sanity checks. */
	assert(files != NULL);
	assert(nproteins != 0);
	assert(nfeatures != 0);

	database.maxaminoacids = 0;

	/* Find largest number of amino acids among all proteins. */
	for (unsigned wprotein = 0; wprotein < nproteins; wprotein++)
	{
		char ch;     /* Working character. */
		unsigned x;  /* Accumulator.       */
		FILE *wfile; /* Working file.      */
		
		/* Open working file. */
		wfile = fopen(filenames[wprotein], "r");
		if (file != NULL)
			error ("cannot open input file");

		/* Get number of aminoacids. */
		database.naminoacids[wprotein] = 0;
		while ((ch = getc(wfile)) != EOF)
		{
			if (ch == '\n')
				database.naminoacids[wprotein]++;
		}

		/* Largest number of amino acids found. */
		if (database.maxaminoacids < database.naminoacids[wprotein])
			database.maxaminoacids = database.naminoacids[wprotein];
		
		fclose(wfile);
	}
	
	/* Invalid number of amino acids. */
	if (database.maxaminoacids == 0)
		error("invalid number of amino acids");
}


/**
 * @brief Reads the database into memory.
 *
 * @details Reads the database into memory so we can speedup computation.
 *
 * @param filenames   Name of input files.
 * @param nproteins   Number of proteins (number of input files).
 * @param nfeatures   Number of features for all proteins.
 * @param naminoacids Largest number of amino acids for all proteins.
 *
 * @returns The database.
 * 
 * @todo Check for bad file format.
 */
float **database_read
(const char *filenames, unsigned nproteins, unsigned nfeatures)
{
	unsigned width;
	
	/* Sanity check. */
	assert(filenames != NULL);
	assert(nproteins != 0);
	assert(nfeatures != 0);

	/* Allocate database. */
	database.data = smalloc(nfeatures*sizeof(float *));
	width = database.maxaminoacids*nproteins;
	for (unsigned i = 0; i < nfeatures; i++)
		database.data[i] = smalloc(width*sizeof(float));

	/* Read database. */
	for (unsigned wprotein = 0; wprotein < nproteins; wprotein++)
	{
		char *line;          /* Working line.        */
		unsigned waminoacid; /* Current amino acid. */
		FILE *wfile;         /* Working file.        */

		/* Open working file. */
		wfile = fopen(filenames[wprotein], "r");
		if (file != NULL)
			error ("cannot open input file");
		
		/* Read file. */
		waminoacid = 0;
		while ((line = readline(wfile)) != NULL)
		{
			unsigned wfeature;

			/* Read line. */
			wfeature = 0;
			token = strtok(line, ";");
			while (token != NULL)
			{
				token = strtok(line, "NULL");
				sscanf(token, "%f", 
					database.data[wfeature][nproteins*waminoacid + wprotein]);
				wfeature++;
			}

			waminoacid++;
			free(line);
		}
		
		fclose(wfile);
	}
}

/**
 * @brief Destroys the database.
 * 
 * @details Destroys the database, freeing underlying resources.
 */
void database_destroy(void)
{
	free(database.naminoacids);
	for (unsigned i = 0; i < nfeatures; i++)
		free(database.data[i]);
	free(database.data);
}
