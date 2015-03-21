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


#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mylibc/util.h>
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
(const char **filenames, unsigned nproteins, unsigned nfeatures)
{
	/* Sanity checks. */
	assert(filenames != NULL);
	assert(nproteins != 0);
	assert(nfeatures != 0);

	database.maxaminoacids = 0;
	database.naminoacids = smalloc(nproteins*sizeof(unsigned));

	/* Find largest number of amino acids among all proteins. */
	for (unsigned wprotein = 0; wprotein < nproteins; wprotein++)
	{
		char ch;     /* Working character. */
		FILE *wfile; /* Working file.      */
		
		/* Open working file. */
		wfile = fopen(filenames[wprotein], "r");
		if (wfile == NULL)
			error ("cannot open input file");
		
		/* Skip first line. */
		while ((ch = getc(wfile) != '\n'))
			/* noop. */;

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
 * @brief Transposes the database.
 * 
 * @details Transposes the database, so that the data tables will be
 *          maxaminoacids x nproteins.
 */
static void database_transpose(void)
{
	/* Transpose database. */
	for (unsigned wfeature = 0; wfeature < nfeatures; wfeature++)
	{
		double *data;      /* Original data table.  */
		double *transpose; /* Transpose data table. */
		
		data = database.data[wfeature];
		transpose = smalloc(database.maxaminoacids*nproteins*sizeof(double));
			
		/* Transpose data tables. */
		for (unsigned i = 0; i < database.maxaminoacids; i++)
		{			
			for (unsigned j = 0; j < nproteins; j++)
			{
				transpose[j*database.maxaminoacids + i] =
					data[i*database.nproteins + j];
			}
		}
					
		database.data[wfeature] = transpose;
		free(data);
	}
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
void database_read
(const char **filenames, unsigned nproteins, unsigned nfeatures)
{
	unsigned width;
	
	/* Sanity check. */
	assert(filenames != NULL);
	assert(nproteins != 0);
	assert(nfeatures != 0);

	/* Allocate database. */
	database.nproteins = nproteins;
	database.labels = smalloc(nproteins*sizeof(unsigned));
	database.data = smalloc(nfeatures*sizeof(double *));
	width = database.maxaminoacids*nproteins;
	for (unsigned i = 0; i < nfeatures; i++)
		database.data[i] = smalloc(width*sizeof(double));

	/* Read database. */
	for (unsigned wprotein = 0; wprotein < nproteins; wprotein++)
	{
		char *line;          /* Working line.        */
		unsigned waminoacid; /* Current amino acid. */
		FILE *wfile;         /* Working file.        */

		/* Open working file. */
		wfile = fopen(filenames[wprotein], "r");
		if (wfile == NULL)
			error ("cannot open input file");
		
		/* Read label. */
		line = readline(wfile);
		sscanf(line, "%u", &database.labels[wprotein]);
		free(line);
		
		/* Read amino acid. */
		waminoacid = 0;
		while (!feof(wfile))
		{
			char *token;       /* Working token.                  */
			unsigned wfeature; /* Working feature.                */
			unsigned j;        /* waminoacid*nproteins + wprotein */
			
			line = readline(wfile);
			
			/* Read line. */
			wfeature = 0;
			token = strtok(line, ";");
			j = waminoacid*nproteins + wprotein;
			while (token != NULL)
			{
				sscanf(token, "%lf", &database.data[wfeature][j]);
				
				token = strtok(NULL, ";");
				wfeature++;
				
				if (wfeature > nfeatures)
					error("bad input file");
				if (waminoacid > database.maxaminoacids)
					error("bad input file");
			}
			
			waminoacid++;
			free(line);
		}
		
		fclose(wfile);
	}
	
	database_transpose();
}

/**
 * @brief Destroys the database.
 * 
 * @details Destroys the database, freeing underlying resources.
 */
void database_destroy(void)
{
	free(database.labels);
	free(database.naminoacids);
	for (unsigned i = 0; i < nfeatures; i++)
		free(database.data[i]);
	free(database.data);
}
