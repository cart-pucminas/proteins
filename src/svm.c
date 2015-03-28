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
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <libsvm/svm.h>
#include <mylibc/util.h>
#include "predict.h"

#define NR_FOLD 10


static double do_cross_validation(const struct svm_problem *prob, struct svm_parameter *param)
{
	double accuracy;
	int total_correct;
	double *target = smalloc(prob->l*sizeof(double));

	svm_cross_validation(prob, param, NR_FOLD, target);
	
	/* Compute accuracy. */
	total_correct = 0;
	for (int i = 0; i < prob->l; i++)
	{
		if (target[i] == prob->y[i])
			total_correct++;
	}
	accuracy = 100.0*total_correct/prob->l;
	
	free(target);
	
	return (accuracy);
}

void buildProblem(unsigned *labels, unsigned nproteins, double *data, struct svm_problem *prob, unsigned ncoeficients)
{
	int j;
	int max_index;
	
	prob->l = nproteins;
	prob->y = smalloc(nproteins*sizeof(double));
	prob->x = smalloc(nproteins*sizeof(struct svm_node *));
	prob->x_space = smalloc(((ncoeficients*nproteins)+nproteins)*sizeof(struct svm_node));

	j = 0;
	max_index = 0;
	for (unsigned i = 0; i < nproteins; i++)
	{	   
		int idx;     
		int inst_max_index;
		
		prob->x[i] = &prob->x_space[j];
		prob->y[i] = labels[i];
		
		idx = 0;
		inst_max_index = -1;
		
		for (unsigned k = 0; k < ncoeficients; k++)
		{
			prob->x_space[j].index = idx;
			inst_max_index = prob->x_space[j].index;
			prob->x_space[j].value = data[i*ncoeficients + k];
			idx++; j++;
		}

		if(inst_max_index > max_index)
			max_index = inst_max_index;
			
		prob->x_space[j++].index = -1;
	}
}

void destroy_problem(struct svm_problem *prob)
{
	free(prob->x_space);
	free(prob->y);
	free(prob->x);
}

double svm(const struct svm_problem *prob, double c, double gamma)
{
	double accuracy;
	struct svm_parameter param;
	
	/* Set parameters. */
	param.svm_type     = C_SVC;
	param.kernel_type  = RBF;
	param.degree       = 3;
	param.gamma        = gamma;
	param.coef0        = 0;
	param.nu           = 0.5;
	param.cache_size   = 100;
	param.C            = c;
	param.eps          = 1e-3;
	param.p            = 0.1;
	param.shrinking    = 1;
	param.probability  = 0;
	param.nr_weight    = 0;
	param.weight_label = NULL;
	param.weight       = NULL;
	            
	/* Cross validation. */
	accuracy = do_cross_validation(prob, &param);

	/* House keeping. */
	svm_destroy_param(&param);
	
	return (accuracy);
}

