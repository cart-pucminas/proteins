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

#ifndef PREDICT_H_
#define PREDICT_H_

	#include <libsvm/svm.h>

	/**
	 * @brief Database.
	 */
	struct database
	{
		double **data;           /**< Data.                                   */
		unsigned maxaminoacids; /**< Number of amino acids.                  */
		unsigned *naminoacids;  /**< Number of amino acids for each protein. */
		unsigned nproteins;     /**< Number of proteins.                     */
		unsigned *labels;       /**< Protein labels.                         */
	};
	
	/* Forward definitions. */
	extern void dct(double *, double *, unsigned, unsigned);
	extern void database_read(const char **, unsigned, unsigned);
	extern void database_parse(const char **, unsigned, unsigned);
	extern void database_destroy(void);
	extern double svm(struct svm_problem *, double, double);
	extern void buildProblem(unsigned *, unsigned, double *, struct svm_problem *, unsigned);
	extern void destroy_problem(struct svm_problem *);
	
	/* Forward definitions. */
	extern unsigned nproteins;
	extern unsigned nfeatures;
	extern unsigned nselected;
	extern struct database database;

#endif /* PREDICT_H_ */
