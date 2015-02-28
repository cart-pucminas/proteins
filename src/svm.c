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
#include "svm.h"
#include "util.h"

#define NR_FOLD 10

float do_cross_validation(void)
{
	float accuracy;
	int total_correct;
	double *target = smalloc(double,prob.l);

	svm_cross_validation(&prob, &param, NR_FOLD, target);
	
	/* Compute accuracy. */
	total_correct = 0;
	for (int i = 0; i < prob.l; i++)
	{
		if (target[i] == prob.y[i])
			total_correct++;
	}
	accuracy = 100.0*total_correct/prob.l
	
	free(target);
	
	return (accuracy);
}

void buildProblem(struct svm_problem *prob, struct svm_node *x_space, unsigned ncoeficients)
{
	int j;
	int max_index;
	
	prob->l = nproteins;
	prob->y = smalloc(double,nproteins);
	prob->x = smalloc(struct svm_node *,nproteins);
	x_space = smalloc(struct svm_node,(ncoeficients*nproteins)+nproteins);

	j = 0;
	max_index = 0;
	for (int i = 0 ; i < nproteins; i++)
	{	   
		int idx;     
		int inst_max_index;
		
		prob->x[i] = &x_space[j];
		prob->y[i] = label[i];
		
		idx = 0;
		inst_max_index = -1;
		
		for (int k = i*ncoeficients; k < (i+1)*ncoeficients; k++)
		{
			x_space[j].index = idx;
			inst_max_index = x_space[j].index;
			x_space[j].value = data[k];
			idx++; j++;
		}

		if(inst_max_index > max_index)
			max_index = inst_max_index;
			
		x_space[j++].index = -1;
	}
}

float svm(unsigned *label, float *data, unsigned ncoeficients, unsigned nproteins, float c, float gamma)
{
	float accuracy;
	struct svm_node *x_space;
	struct svm_problem prob;
	struct svm_parameter param;
	
	/* Set parameters. */
	param.svm_type     = C_SVC;
	param.kernel_type  = RBF;
	param.degree       = 3;
	param.gamma        = gamma;
	param.coef0        = 0;
	param.nu           = 0.5;
	param.cache_size   = 100;
	param.C            = C;
	param.eps          = 1e-3;
	param.p            = 0.1;
	param.shrinking    = 1;
	param.probability  = 0;
	param.nr_weight    = 0;
	param.weight_label = NULL;
	param.weight       = NULL;
	
	/* Builds the structure*/
	buildProblem(&prob, x_space, ncoeficients);
	            
	/* Cross validation. */
	accuracy = do_cross_validation();

	/* House keeping. */
	svm_destroy_param(&param);
	free(prob.y);
	free(prob.x);
	free(x_space);
	
	return (accuracy);
}

