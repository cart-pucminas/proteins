/*
 * ai.h - Artificial intelligence library.
 * 
 * Copyright (C) 2011-2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef AI_H_
#define AI_H_

	/* Genetic algorithm options. */
	#define GA_POPULATION_STATISTICS 1 /* Print population statistics. */
	#define GA_MINIMIZATION          2 /* Triggers minimization mode.  */

	/*
	 * Gene.
	 */
	typedef void * gene_t;

	/*
	 * Genome.
	 */
	struct genome
	{
		/* Attributes. */
		double m_rate; /* Mutation rate.    */
		double c_rate; /* Crossover rate.   */
		double e_rate; /* Elitism rate.     */
		double r_rate; /* Replacement rate. */
		
		/* Operations. */
		gene_t (*random)(void);                   /* Generates a random gene. */
		double (*evaluate)(gene_t);               /* Evaluation function.     */
		gene_t (*crossover)(gene_t, gene_t, int); /* Crossover operator.      */
		gene_t (*mutation)(gene_t);               /* Mutation operator.       */
		void (*destroy)(gene_t);                  /* Destroys a gene.         */
	};
	
	/*
	 * Genetic algorithm.
	 */
	extern gene_t genetic_algorithm(struct genome *g, int popsize, int ngen, int options);

#endif /* AI_H_ */
