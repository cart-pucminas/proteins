/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmai.com>
 * 
 * <algorithm.h> - Algorithms library.
 */

#ifndef ALGORITHM_H_
#define ALGORITHM_H_

	#include "array.h"
	#include "matrix.h"
	
	/*
	 *  Clusters data.
	 */
	extern int *kmeans(array_t data, int nclusters, int mindistance);
 
	/*
	 * Solves the assignment problem.
	 */
	extern int *auction(matrix_t prices, double slack);

#endif /* ALGORITHM_H_ */
