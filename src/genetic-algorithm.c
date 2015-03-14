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
#include <mylibc/ai.h>
#include <mylibc/graph.h>
#include <mylibc/matrix.h>
#include <mylibc/util.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h> 
#include "predict.h"


/**
 * @brief Number of coefficients.
 */
#define NCOEFFICIENTS 75

/**
 * @brief Gene.
 */
struct gene
{
	unsigned *features; /**< Features. */
	double gamma;       /**< Gamma.    */
	double cost;        /**< Cost.     */
	double accuracy;    /**< Accuracy. */
};


/**
 * @brief Casts a gene.
 */
#define GENE(x) ((struct gene *)(x))

/*============================================================================*
 *                              Genetic Operators                             *
 *============================================================================*/

/**
 * @brief Asserts if a gene has a feature.
 * 
 * @returns One if the gene has the feature, and zero otherwise.
 */
static int has_feature(struct gene *g, unsigned feature)
{
	for (unsigned i = 0; i < nselected; i++)
	{
		if (g->features[i] == feature)
			return (1);
	}
	
	return (0);
}

/**
 * @brief Creates a gene.
 * 
 * @returns A new gene.
 */
static struct gene *gene_create(void)
{
    struct gene *g;
    
    g = smalloc(sizeof(struct gene));
	g->features = scalloc(nselected, sizeof(unsigned));
	g->gamma = 0;
	g->cost = 0;
	g->accuracy = 0;

	return (g);
}

/**
 * @brief Destroys a gene.
 */
static void gene_destroy(void *g)
{
	/* Sanity check. */
	assert(g != NULL);
	
	/* House keeping. */
	free(GENE(g)->features);
	free(g);
}

/**
 * @brief Generates a random gene.
 * 
 * @returns A random gene.
 */
static void *gene_random(void)
{
	struct gene *g;
    
    g = gene_create();
    
    /* Generate gene. */
    for (unsigned i = 0; i < nselected; i++)
    {
		unsigned feature;
		
		do
		{
			feature = randnum()%nfeatures + 1;
		} while (has_feature(g, feature));

		g->features[i] = feature;
    }
	
	return (g);
}

/**
 * @brief Searches for SVM parameters.
 */
static double grid_search(float *feature_matrix, double *bestg, double *bestc)
{
	/*
	 * Adjust these
	 * at your will.
	 */
	double step = 2;
	
	double bestacc;
	
	/* Sanity check. */
	assert(feature_matrix != NULL);
	assert(bestg != NULL);
	assert(bestc != NULL);
	
	bestacc = 0, *bestg = 0, *bestc = 0;
	
	/* Search parameters. */
	for (double cost = -5; cost < 15; cost = cost + step)
	{
		for (double gamma = 3; gamma > -15; gamma = gamma - step)
		{
			double acc;    /* Accuracty. */
			double gamma2; /* 2^gamma.   */
			double cost2;  /* 2^cost.    */
			
			gamma2 = pow(2,gamma);
			cost2 = pow(2, cost);

			acc =
				svm(database.labels,
					feature_matrix,
					NCOEFFICIENTS,
					nproteins,
					gamma2,
					cost2);
			
			/* Best arameters found. */
			if (acc >= bestacc)
			{
				bestacc = acc; 
				*bestc = cost2; 
				*bestg = gamma2;
			}
		}
	}
	
	return (bestacc);
}

/**
 * @brief Evaluates the fitness of a gene.
 */
static double gene_evaluate(void *g)
{
	float *feature_matrix;
	
	/* Sanity check. */
	assert(g != NULL);
	
	feature_matrix = smalloc(NCOEFFICIENTS*nproteins*sizeof(float));
	
	/* Build feature matrix. */
	for (unsigned wprotein = 0; wprotein < nproteins; wprotein++)
	{
		float *data;    
		float *protein;
		
		protein = 
			smalloc(nselected*database.naminoacids[wprotein]*sizeof(float));
		
		for (unsigned i = 0; i < nselected; i++)
		{
			data = &database.data[i][wprotein*database.maxaminoacids];
			memcpy(protein, data, database.naminoacids[wprotein]*sizeof(float));
		}
		
		dct(protein, database.naminoacids[wprotein]);
		
		memcpy(&feature_matrix[wprotein*NCOEFFICIENTS], protein,NCOEFFICIENTS*sizeof(float));
		
		free(protein);
	}
	
	GENE(g)->accuracy =
		grid_search(feature_matrix, &GENE(g)->gamma, &GENE(g)->cost);
	
	free(feature_matrix);
	
	return (GENE(g)->accuracy);
}

/**
 * @brief Crossovers two genes.
 * 
 * @param gene1 First gene.
 * @param gene2 Second gene.
 * @param n     Child number.
 */
static void *gene_crossover(void *gene1, void *gene2, int n)
{
	unsigned point1;                /* First crossover point.   */
	unsigned point2;                /* Second crsossover point. */
	unsigned nbegin, nmiddle, nend; /* Size of gene parts.      */
	unsigned *begin, *middle, *end; /* Gene parts.              */
	struct gene *offspring;         /* Offspring.               */
	
	/* Sanity check. */
	assert(gene1 != NULL);
	assert(gene2 != NULL);
	assert(n >= 0);
	
	offspring = gene_create();
	
	/* Crossover points. */
	point1 = randnum()%(n - 1);
	point2 = randnum()%(n - point1 - 1) + point1;
	
	/* Size of gene parts. */
	nbegin = point1;
	nmiddle = point2 - point1;
	nend = n -(nbegin+nmiddle);
	
	/* Gene parts. */
	begin = smalloc(nbegin*sizeof(unsigned));
	middle = smalloc(nmiddle*sizeof(unsigned));
	end = smalloc(nend*sizeof(unsigned));
	
	memcpy(begin, GENE(gene1)->features, nbegin*sizeof(unsigned));
	memcpy(middle, GENE(gene2)->features + nbegin, nmiddle*sizeof(unsigned));
	memcpy(end, GENE(gene1)->features + (nbegin - nmiddle), nend*sizeof(unsigned));
	
	for (unsigned i = 0; i < nmiddle; i++)
	{
		for (unsigned j = 0; j < nbegin; j++)
		{
			if (middle[i] == begin[j] )
			{
				for (int k = 0; k < n; k++ )
				{
					if (GENE(gene2)->features[k] == begin[j])
					{
						begin[j] = GENE(gene1)->features[k];
						break;
					}
				}
			}
		}
		
		for (unsigned j = 0; j < nend; j++)
		{
			if (middle[i] == end[j])
			{
				for (int k = 0; k < n; k++ )
				{
					if (GENE(gene2)->features[k] == end[j])
					{
						end[j] = GENE(gene1)->features[k];
						break;
					}
				}
			}
		}
	}

	memcpy(offspring->features, begin, nbegin*sizeof(unsigned)); 
	memcpy(offspring->features + nbegin, middle, nmiddle*sizeof(unsigned));
	memcpy(offspring->features + nbegin + nmiddle, end, nend*sizeof(unsigned));
	
	/* House keeping. */
	free(begin);
	free(middle);
	free(end);

	return (offspring);
}

/**
 * @brief Mutates a gene.
 * 
 * @returns The mutated gene.
 */
static void *gene_mutation(void *g)
{
	unsigned i;       /* Mutation point. */
	unsigned feature; /* Feature.        */
	
	/* Sanity check. */
	assert(g != NULL);
	
	i = randnum()%nselected;
	
	do
	{
		feature = randnum()%nfeatures + 1;
	} while (has_feature(g, feature));

	GENE(g)->features[i] = feature;
		
	return (g);
}

/*============================================================================*
 *                              Genetic Operators                             *
 *============================================================================*/

/*
 * Problem's genome.
 */
static struct genome problem = 
{
	0.05,           /* Mutation rate.    */
	0.80,           /* Crossover rate.   */
	0.01,           /* Elitism rate.     */
	0.90,           /* Replacement rate. */
	gene_random,    /* random().         */
	gene_evaluate,  /* evaluate().       */
	gene_crossover, /* crossover().      */
	gene_mutation,  /* mutation().       */
	gene_destroy    /* destroy().        */
};

/*
 * Genetic algorithm for function prediction.
 */
void predict(int popsize, int ngen)
{
	genetic_algorithm(&problem, popsize, ngen, 0
					| GA_POPULATION_STATISTICS
					| GA_MINIMIZATION);
}
