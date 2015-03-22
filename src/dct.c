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

#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
/**
 * @brief Discrete cosine transform.
 * 
 * @details Applies the discrete cosine transform in the vector pointed to by
 *          @p x.
 * 
 * @param x Vector where the discrete cosine transform should be applied.
 * @param n Dimension of the vector.
 */
void dct(double *b, double *x, unsigned n, unsigned m)
{	
	for (unsigned i = 0; i < m; i++)
	{
		for (unsigned j = 0; j < n; j++)
		{
			if (i == 0)
			{
				b[i] += 1/sqrt(n)*x[j];
				continue;
			}
			
			b[i] += sqrt(2.0/n)*cos(i*M_PI/(2.0*n)*(2.0*j + 1))*x[j];
		}
	}
}
