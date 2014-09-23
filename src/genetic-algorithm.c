/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * genetic-algorithm.c - Genetic algorithm for mapping processes on a many-core
 *                       processor.
 */

#include <mylibc/ai.h>
#include <mylibc/graph.h>
#include <mylibc/matrix.h>
#include <mylibc/util.h>
#include <stdlib.h>

/*============================================================================*
 *                              Genetic Operators                             *
 *============================================================================*/

/*
 * Creates a gene.
 */
static int *gene_create(void)
{
	return (NULL);
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
 * Evaluates the fitness of a gene.
 */
static double gene_evaluate(void *gene)
{
	((void)gene); /* Unused. */
	
	return (0);
}

/*
 * Crossovers two genes.
 */
static void *gene_crossover(void *gene1, void *gene2, int n)
{
	((void)gene1); /* Unused. */
	((void)gene2); /* Unused. */
	((void)n);     /* Unused. */
	
	return (NULL);
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
