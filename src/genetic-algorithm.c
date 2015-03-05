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
#include <time.h>
#include <cmath> 
#include "predict.h"


/**
 * @brief Number of coefficients.
 */
#define NCOEFFICIENTS 75

/**
 * @brief Casts a gene.
 */
#define GENE(x) ((unsigned *)(x))

/*============================================================================*
 *                              Genetic Operators                             *
 *============================================================================*/

/*
 * Creates a gene.
 */
static int *gene_create(void)
{
    srand((unsigned)time(NULL));
    
    int number = rand()%325; /*325 is a number of features*/
    int i;    
    int *individual = smalloc(int,ngen);
    
    for(i = 0; i < ngen; i++)
    {
        while(isRepeated(individual, number))
        {
               individual[i] = number;
        }
    }
	return (individual);
}

/*
 * Destroys a gene.
 */
static void gene_destroy(void *gene)
{
	((void)gene); /* Unused. */
}

/*
 * Generates a random gene.
 */
static void *gene_random(void)
{
	/* You may want to use this. */
	gene_create();
	
	return (NULL);
}

/*
 * @brief Searches for SVM parameters.
 */
static double grid_search(float *feature_matrix)
{
	double Acc = 0, gamma = 0, cost = 0;
	double bestAcc = 0, bestg = 0, bestc = 0;
	int step = 2;
	
        for (cost = -5; cost < 15; cost = cost + step)
        {
                for(gamma = 3; gamma > -15, gamma = gamma - step)
                {
                         gamma = pow(2,gamma);
                         cost = pow(2, cost);
                         best = svm(feature_matrix, NCOEFFICIENTS, nproteins, gamma, cost);
                         if (Acc >= bestAcc)
                         {
                             bestAcc = cv; 
                             bestc = cost; 
                             bestg = gamma;
                         }
                }
        }
}

/*
 * Evaluates the fitness of a gene.
 */
static double gene_evaluate(void *gene)
{
	float accuracy;        /* Fitness value.  */
	float *feature_matrix; /* Feature matrix. */
	
	/* Sanity check. */
	assert(gene != NULL);
	
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
			data = database.data[GENE(i)][wprotein*database.maxaminoacids];
			memcpy(protein, data, database.naminoacids[wprotein]*sizeof(float));
		}
		
		dct(protein, database.naminoacids[wprotein]);
		
		memcpy(&feature_matrix[wprotein*NCOEFFICIENTS], protein,NCOEFFICIENTS*sizeof(float));
		
		free(protein);
	}
	
	accuracy = grid_search(feature_matrix);
	
	free(feature_matrix);
	
	return (accuracy);
}

/*
 * Crossovers two genes.
 */
static void *gene_crossover(void *gene1, void *gene2, int n)
{
	int point1 = rand()%(n - 1);
	int point2 = rand()%(n - point1 - 1) + point1;
	int i,j,k;
        int Nbegin = point1 , Nmiddle = point2 - point1 , Nend = n -(nbegin+nmiddle) ;
	int *begin = smalloc(int,Nbegin);
	int *middle = smalloc(int,Nmiddle);
	int *end; = smalloc(int,Nend);
	
	
	memmove(begin,gene1,Nbeing);
	memmove(middle,gene2+Nbegin,Nmiddle);
	memmove(end,gene1+(Nbegin-Nmiddle),Nend);
	
	for(i = 0; i < Nmiddle; i++){
		for(j = 0; j < Nbegin; j++)
			if( middle[i] == begin[j] )
				for(k = 0; k < n; k++ )
					if(gene2[k] == begin[j]){
						begin[j] = gene1[k];
						break;
					}
		for(j = 0; j < Nend; j++)
			if(middle[i] == end[j])
				for(k = 0; k < n; k++ )
					if(gene2[k] == end[j]){
						end[j] = gene1[k];
						break;
					}
	}

	int * offspring = smalloc(int, n); 
	
	//offspring = begin + middle + end;
	memcpy(offspring,begin,  Nbegin* sizeof(int)); 
        memcpy(offspring + Nbegin, middle, Nmiddle* sizeof(int))
        memcpy(offspring + (Nbegin+Nmiddle), end, Nend* sizeof(int))
	
		
	return offspring;
}

/*
 * Mutates a gene.
 */
static void *gene_mutation(void *gene)
{
	((void)gene); /* Unused. */
	
	return (NULL);
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
