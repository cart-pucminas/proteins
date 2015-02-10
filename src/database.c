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
#include <util.h>

/**
 * @brief Parses the database.
 *
 * @details Parses the database so that we can determine the largest number of
 *          amino acids for all proteins.
 *
 * @param files Input files.
 * @nproteins   Number of proteins (number of input files).
 * @nfeatures   Number of features for all proteins.
 *
 * @returns The largest number of amino acids for all proteins.
 */
unsigned database_parse(FILE **files, unsigned nproteins, unsigned nfeatures)
{
	unsigned naminoacids;

	/* Sanity checks. */
	assert(files != NULL);
	assert(nproteins != 0);
	assert(nfeatures != 0);

	naminoacids = 0;

	/* Find largest number of amino acids for all proteins. */
	for (unsigned i = 0; i < nproteins; i++)
	{
		fseek(files[i], 0, SEEK_SET);

		char ch;    /* Working character. */
		unsigned x; /* Accumulator.       */

		x = 0;

		/* Get number of aminoacids. */
		while ((ch = getc(files[i])) != EOF)
		{
			if (ch == '\n')
				x++;
		}

		/* Largest number of amino acids found*/
		if (naminoacids < x)
			x = naminoacids;
	}

	return (naminoacids);
}


/**
 * @brief Reads the database into memory.
 *
 * @details Reads the database into memory so we can speedup computation.
 *
 * @param files       Input files.
 * @param nproteins   Number of proteins (number of input files).
 * @param nfeatures   Number of features for all proteins.
 * @param naminoacids Largest number of amino acids for all proteins.
 *
 * @returns The database.
 */
float **database_read(FILE **files, unsigned nproteins, unsigned nfeatures, unsigned naminoacids)
{
	float **database;

	/* Sanity check. */
	assert(files != NULL);
	assert(nproteins != 0);
	assert(nfeatures != 0);
	assert(naminoacids != 0);

	/* Allocate database. */
	database = smalloc(nfeatures*sizeof(float *));
	for (unsigned i = 0; i < nfeatures; i++)
		database[i] = smalloc(naminoacids*nproteins*sizeof(float));

	/* Read database. */
	for (unsigned wprotein = 0; wprotein < nproteins; wprotein++)
	{
		char *line;          /* Working line.        */
		unsigned waminoacid; /* Current namino acid. */
		unsigned base;       /* waminoacid*nproteins */

		fseek(files[wprotein], 0, SEEK_SET);
		
		/* Read file. */
		waminoacid = 0;
		base = waminoacid*nproteins;
		while ((line = readline(files[wprotein])) != NULL)
		{
			unsigned wfeature;

			/* Read line. */
			wfeature = 0;
			token = strtok(line, ";");
			while (token != NULL)
			{
				token = strtok(line, "NULL");

				sscanf(token, "%f", database[wfeature][base + wprotein]);

				wfeature++;
			}

			waminoacid++;
			free(line);
		}
	}

	return (database);
}

