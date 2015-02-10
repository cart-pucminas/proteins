/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * ia/genetic_algorithm/genetic_algorithm.c - genetic_algorithm() implementation.
 */

#include <array.h>
#include <assert.h>
#include <list.h>
#include <math.h>
#include <util.h>
#include "genetic-algorithm.h"

/* Global parameters. */
int gen;          /* Number of generations elapsed. */
int popsize;      /* Population size.               */
struct genome *g; /* Genome.                        */

/*
 * Selects organisms for mating using roulette wheel.
 */
static void selection(array_t parents, array_t pop)
{
	int i, j;     /* Loop indexes.         */
	double sum;   /* Total sum of fitness. */
	double arrow; /* Roulette's arrow.     */
	
	/* Computer total sum of fitness. */
	sum = 0.0;
	for (i = 0; i < popsize; i++)
		sum += ORGANISM(ARRAY(pop, i))->fitness;
	
	/* Select organisms. */	
	for (i = 0; i < popsize; i++)
	{
		/* Rotate wheel. */
		arrow = (((double)randnum())/(RANDNUM_MAX))*sum; j = 0;
		while ((j < popsize) && (arrow > 0.0))
		{
			arrow -= ORGANISM(ARRAY(pop, j))->fitness;
			j++;
		}
		
		ARRAY(parents, i) = ARRAY(pop, j - 1);
	}
}

/*
 * Generates a new population.
 */
static void reproduction(list_t newpop, array_t parents)
{
	int i;                /* Loop indexes. */
	struct organism *mom; /* Mother.       */
	struct organism *dad; /* Father.       */
	array_t offspring;    /* Offspring.    */	
	
	array_shuffle(parents);
	
	/* Build new population. */
	for (i = 0; i < popsize; i += 2)
	{
		mom = ARRAY(parents, i);
		dad = ARRAY(parents, i + 1);
		
		offspring = organism_mate(mom, dad);
		
		/* No offspring. */
		if (offspring == NULL)
			continue;
		
		organism_mutate(ARRAY(offspring, 0));
		organism_mutate(ARRAY(offspring, 1));
		
		list_insert(newpop, ARRAY(offspring, 0));
		list_insert(newpop, ARRAY(offspring, 1));
		
		array_destroy(offspring);
	}
}

/*
 * Replaces old population for new population applying elitism and random kill.
 */
static void replacement(array_t pop, list_t newpop)
{
	int i;        /* Loop index.                     */
	int repidx;   /* Replace index.                  */
	int nelite;   /* Number of elite individuals.    */
	int nreplace; /* Number of organisms to replace. */
	
	/* Extract elite organisms. */
	nelite = (int)floor(g->e_rate*popsize);
	array_sort(pop);
	
	nreplace = (int)floor(g->r_rate*(popsize - nelite));
	if (nreplace > list_length(newpop))
		nreplace = list_length(newpop);
	
	/* Kill some organisms at random. */
	for (i = 0; i < nreplace; i++)
	{
		repidx = (int)floor(randnum()%(popsize - nelite));
			
		/* Skip killed organisms. */
		while (ARRAY(pop, repidx) == NULL)
			repidx = (repidx + 1)%(popsize - nelite);
			
		organism_kill(ARRAY(pop, repidx), TRUE);
		ARRAY(pop, repidx) = NULL;
	}
	
	/* Replace individuals. */
	for (i = 0; i < popsize; i++)
	{
		if (ARRAY(pop, i) == NULL)
			ARRAY(pop, i) = list_remove_first(newpop);
	}
	
	/* Discard remaining new organisms. */
	while (list_length(newpop) > 0)
		organism_kill(list_remove_first(newpop), TRUE);
	
}

/*
 * Sanity check for genetic_algorithm().
 */
#define SANITY_CHECK()          \
	assert(_popsize > 0);       \
	assert(ngen > 0);           \
	assert(_g->m_rate >= 0.0);  \
	assert(_g->m_rate <= 1.0);  \
	assert(_g->c_rate >= 0.0);  \
	assert(_g->c_rate <= 1.0);  \
	assert(_g->e_rate > 0.0);   \
	assert(_g->e_rate < 1.0);   \

/*
 * Genetic algorithm.
 */
void *genetic_algorithm(struct genome *_g, int _popsize, int ngen, int options)
{
	int i;                    /* Loop index.         */
	array_t pop;              /* Current population. */
	list_t newpop;            /* New population.     */
	array_t parents;          /* Mating pool.        */
	struct organism *bestorg; /* Best organism.      */
	double mean;              /* Mean fitness.       */
	void *bestgene;           /* Best gene.          */
	
	SANITY_CHECK();
	
	/* Set global parameters. */
	gen = 0; g = _g;
	popsize = _popsize + ((_popsize & 1) ? 1 : 0);
	
	pop = array_create(&organism, popsize);
	newpop = list_create(&organism);
	parents = array_create(&organism, popsize);
	
	/* Build initial population. */
	for (i = 0; i < popsize; i++)
		ARRAY(pop, i) = organism_random();
	
	/* Iterate over generations. */
	if (options & GA_POPULATION_STATISTICS)
		printf("population;best organism\n");
	do
	{	
		/* Print population statistics. */
		if (options & GA_POPULATION_STATISTICS)
		{
			mean = 0;
			bestorg = ARRAY(pop, 0);
			for (i = 1; i < popsize; i++)
			{
				mean += ORGANISM(ARRAY(pop, i))->fitness;
				if (ORGANISM(ARRAY(pop, i))->fitness > bestorg->fitness)
					bestorg = ORGANISM(ARRAY(pop, i));
			}
			if (options & GA_MINIMIZATION)
				printf("%f;%f\n", popsize/mean, 1.0/bestorg->fitness);
			else
				printf("%f;%f\n", mean/popsize, bestorg->fitness);
		}
		
		selection(parents, pop);
		reproduction(newpop, parents);
		replacement(pop, newpop);
	} while (++gen < ngen);
	
	/* Get best organism. */
	bestorg = ARRAY(pop, 0);
	for (i = 1; i < popsize; i++)
	{
		/* Best organism found. */
		if (ORGANISM(ARRAY(pop, i))->fitness > bestorg->fitness)
		{
			organism_kill(bestorg, TRUE);
			bestorg = ORGANISM(ARRAY(pop, i));
			continue;
		}
		
		organism_kill(ORGANISM(ARRAY(pop, i)), TRUE);
	}
	
	bestgene = bestorg->gene;
	
	/* House keeping. */
	organism_kill(bestorg, FALSE);
	array_destroy(parents);
	list_destroy(newpop);
	array_destroy(pop);
	
	return (bestgene);
}
