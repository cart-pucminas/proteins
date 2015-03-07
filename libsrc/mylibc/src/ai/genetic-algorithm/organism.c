/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * ia/organism/organism.c - Organism library.
 */

#include <ai.h>
#include <array.h>
#include <object.h>
#include <stdlib.h>
#include <util.h>
#include "genetic-algorithm.h"

/*
 * Compares two keys.
 */
static int organism_cmp(const void *fitness1, const void *fitness2)
{
	if (*DOUBLEP(fitness1) < *DOUBLEP(fitness2))
		return (-1);
	if (*DOUBLEP(fitness1) > *DOUBLEP(fitness2))
		return (1);
	
	return (0);
}

/*
 * Gets key.
 */
static void *organism_getkey(const void *org)
{
	return (&ORGANISM(org)->fitness);
}

/*
 * Organism object.
 */
struct objinfo organism = {
	NULL,            /* read()   */
	NULL,            /* write()  */
	organism_cmp,    /* cmp()    */
	organism_getkey, /* getkey() */
	NULL,            /* hash()   */
	NULL             /* clone()  */
};

/*
 * Creates an organism.
 */
static struct organism *organism_create(void *gene)
{
	struct organism *org;
		
	org = smalloc(sizeof(struct organism));
	
	/* Initialize organism. */
	org->birthdate = gen;
	org->gene = gene;
	org->fitness = g->evaluate(gene);
	
	return (org);
}

/*
 * Destroys an organism.
 */
void organism_kill(struct organism *org, int destroy_gene)
{
	if (destroy_gene == TRUE)
		g->destroy(org->gene);
	free(org);
}

/*
 * Generates a random organism.
 */
struct organism *organism_random(void)
{
	return (organism_create(g->random()));
}

/*
 * Mates two organisms.
 */
array_t organism_mate(struct organism *mom, struct organism *dad)
{
	array_t offspring;
	
	/* Do not mate.*/
	if ((((double)randnum())/(RANDNUM_MAX)) > g->c_rate)
		return (NULL);
	
	offspring = array_create(&organism, 2);
	ARRAY(offspring, 0) = organism_create(g->crossover(mom->gene, dad->gene, 0));
	ARRAY(offspring, 1) = organism_create(g->crossover(mom->gene, dad->gene, 1));
	
	return (offspring);
}

/*
 * Mutates an organism.
 */
struct organism *organism_mutate(struct organism *org)
{
	/* Mutate. */
	if ((((double)randnum())/(RANDNUM_MAX)) < g->m_rate)
	{
		g->mutation(org->gene);
		org->fitness = g->evaluate(org->gene);
	}
	
	return (org);
}
