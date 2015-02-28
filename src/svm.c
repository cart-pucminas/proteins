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
#include "svm.h"
#include <errno.h>
#define Malloc(type,n) (type *)malloc((n)*sizeof(type))

/*
       float* readDatabase(); // ler a base de dados e carrega para a memoria primaria
       float* normalize(float* dataBase)

        /* genetic algorithm 

       float* selectFeature(float* dataBaseNormalized, ); //seleciona da base de dados o conjunto de caracteristicas 
       float* discreteCossineTransform(float* selectedData);
       float supportVectorMachine(float* transformedBase, float C, float gamma)
       
       /* suppot vector machine
       
       void setParameters(float C, float gamma)
*/

struct svm_parameter param;		// set by setParameters
struct svm_problem prob;		// set by read_problem
struct svm_model *model;
struct svm_node *x_space;
int cross_validation;
int nr_fold;

int main()
{
        return 0;
}


float svm(unsigned *label, float *data, unsigned ncoeficients, unsigned nproteins, float c, float gamma)
{
	/* Parameters exchange */
	setParameters(c, gamma);
                
	/* Builds the structure*/
	buildProblem();
	            
                /* Cross validation. */
                 do_cross_validation
                                       
                                       
        svm_destroy_param(&param);
	free(prob.y);
	free(prob.x);
	free(x_space);

  //      return (accuracy);
}

void do_cross_validation()
{
	int i;
	int total_correct = 0;
	double total_error = 0;
	double sumv = 0, sumy = 0, sumvv = 0, sumyy = 0, sumvy = 0;
	double *target = Malloc(double,prob.l);

	svm_cross_validation(&prob,&param,nr_fold,target);
	if(param.svm_type == EPSILON_SVR ||
	   param.svm_type == NU_SVR)
	{
		for(i=0;i<prob.l;i++)
		{
			double y = prob.y[i];
			double v = target[i];
			total_error += (v-y)*(v-y);
			sumv += v;
			sumy += y;
			sumvv += v*v;
			sumyy += y*y;
			sumvy += v*y;
		}
		printf("Cross Validation Mean squared error = %g\n",total_error/prob.l);
		printf("Cross Validation Squared correlation coefficient = %g\n",
			((prob.l*sumvy-sumv*sumy)*(prob.l*sumvy-sumv*sumy))/
			((prob.l*sumvv-sumv*sumv)*(prob.l*sumyy-sumy*sumy))
			);
	}
	else
	{
		for(i=0;i<prob.l;i++)
			if(target[i] == prob.y[i])
				++total_correct;
		printf("Cross Validation Accuracy = %g%%\n",100.0*total_correct/prob.l);
	}
	free(target);
}

void buildProblem()
{     
        int max_index, inst_max_index, i, k,idx;
	size_t ncoeficients, j;
	char *endptr;
	
        prob.l = nproteins;
	prob.y = Malloc(double,nproteins);
	prob.x = Malloc(struct svm_node *,nproteins);
	x_space = Malloc(struct svm_node,(ncoeficients*nproteins)+nproteins);

	max_index = 0;

        j = 0;
	for(i=0;i<nproteins;i++)
	{	        
		inst_max_index = -1; // strtol gives 0 if wrong format, and precomputed kernel has <index> start from 0
		prob.x[i] = &x_space[j];
        	prob.y[i] = label[i];
	
                idx = 0;
                 for(k = i*ncoeficients; k < (i+1)*ncoeficients; k++)
		{
			x_space[j].index = idx;
			inst_max_index = x_space[j].index;
			x_space[j].value = data[k];
                        idx++;
			++j;
		}

		if(inst_max_index > max_index)
			max_index = inst_max_index;
		x_space[j++].index = -1;
	}
}


void setParameters(float C, float gamma)
{
        int i;
	void (*print_func)(const char*) = NULL;	// default printing to stdout

	// default values
	param.svm_type = C_SVC;
	param.kernel_type = RBF;
	param.degree = 3;
	param.gamma = gamma;	// 1/num_features
	param.coef0 = 0;
	param.nu = 0.5;
	param.cache_size = 100;
	param.C = C;
	param.eps = 1e-3;
	param.p = 0.1;
	param.shrinking = 1;
	param.probability = 0;
	param.nr_weight = 0;
	param.weight_label = NULL;
	param.weight = NULL;
	cross_validation = 1;
        nr_fold =10;
	
	svm_set_print_string_function(print_func);
	
}

