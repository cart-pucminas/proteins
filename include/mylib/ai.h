/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 *
 * This file is part of MyLib.
 *
 * MyLib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * MyLib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with MyLib. If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file
 * 
 * @brief Artificial Intelligence Library
 */

#ifndef AI_H_
#define AI_H_

	#include "vector.h"

	/*========================================================================*
	 *                           Genetic Algorithm                            *
	 *========================================================================*/

	/**
	 * @brief Opaque pointer to gene.
	 */
	typedef void * gene_t;
	
	/**
	 * @defgroup GA Genetic Algorithm
	 */
	/**@{*/

	/**
	 * @brief Genome.
	 */
	struct genome
	{
		/**
		 * @name Attributes
		 */
		/**@{*/
		double m_rate; /**< Mutation rate.    */
		double c_rate; /**< Crossover rate.   */
		double e_rate; /**< Elitism rate.     */
		double r_rate; /**< Replacement rate. */
		/**@}*/
		
		/**
		 * @name Operations.
		 */
		/**@{*/
		gene_t (*generate)(void);                 /**< Generates a gene.    */
		double (*evaluate)(gene_t);               /**< Evaluation function. */
		gene_t (*crossover)(gene_t, gene_t, int); /**< Crossover operator.  */
		gene_t (*mutation)(gene_t);               /**< Mutation operator.   */
		void (*destroy)(gene_t);                  /**< Destroys a gene.     */
		/**@}*/
	};
	
	/**
	 * @brief Genetic algorithm options.
	 */
	enum ga_options
	{
		GA_OPTIONS_STATISTICS = (1 << 0) /**< Get statistics. */
	};
	
	/**@}*/
	
	/* Forward definitions. */
	extern gene_t 
	genetic_algorithm(const struct genome*,unsigned,unsigned,enum ga_options);

	/*========================================================================*
	 *                            Kmeans Algorithm                            *
	 *========================================================================*/
	
	/* Forward definitions. */
	extern int *kmeans(const vector_t *, int, int, double);

#endif /* AI_H_ */
