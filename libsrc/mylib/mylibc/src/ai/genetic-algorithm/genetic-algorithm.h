/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * ia/genetic-algorithm/genetic-algorithm.h - Private genetic algorithm library.
 */

#ifndef _GENETIC_ALGORITHM_H_
#define _GENETIC_ALGORITHM_H_

	#include "ai.h"
	#include "array.h"

	/*
	 * Organism.
	 */
	struct organism
	{
		int birthdate;  /* Birth date. */
		void *gene;     /* Gene.       */
		double fitness; /* Fitness.    */
	};	

	/*
	 * Destroys an organism.
	 */
	extern void organism_kill(struct organism *org, int destroy_gene);
	
	/*
	 * Mates two organisms.
	 */
	extern array_t organism_mate(struct organism *mom, struct organism *dad);
	
	/*
	 * Mutates an organism.
	 */
	extern struct organism *organism_mutate(struct organism *org);
	
	/*
	 * Generates a random organism.
	 */
	extern struct organism *organism_random(void);

	/*
	 * Organism caster.
	 */
	#define ORGANISM(x) \
		((struct organism *)(x))
		
	/*
	 * Organism object information.
	 */
	extern struct objinfo organism;
		
	/* Global parameters. */
	extern int gen;          /* Number of generations elapsed. */
	extern int popsize;      /* Population size.               */
	extern struct genome *g; /* Genome.                        */

#endif /* _GENETIC_ALGORITHM_H_ */
