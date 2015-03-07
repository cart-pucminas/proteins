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

	/**
	 * @brief Database.
	 */
	extern struct 
	{
		float **data;           /**< Data.                                   */
		unsigned maxaminoacids; /**< Number of amino acids.                  */
		unsigned *naminoacids;  /**< Number of amino acids for each protein. */
		unsigned *nproteins;    /**< Number of proteins.                     */
		unsigned *labels;       /**< Protein labels.                         */
	} database;
	
	/* Forward definitions. */
	extern float svm(unsigned *, float *, unsigned, unsigned, float, float);
	extern void dct(float *, unsigned);
	
	/* Forward definitions. */
	extern unsigned nproteins;
	extern unsigned nfeatures;
	extern unsigned nselected;

#endif /* PREDICT_H_ */
