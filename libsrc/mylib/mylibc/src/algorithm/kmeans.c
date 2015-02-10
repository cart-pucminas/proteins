/*
 * kmeans.c - kmeans() implementation.
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

#include <assert.h>
#include <algorithm.h>
#include <array.h>
#include <list.h>
#include <math.h>
#include <stdlib.h>
#include <util.h>
#include <vector.h>

#define KMEANS_RANDOM

/*
 * K-means data.
 */
struct kmeans_data
{
	array_t data;        /* Data being clustered.     */
	int *map;            /* Data map.                 */
	int size;            /* Data size.                */
	int migration;       /* Migration statistics.     */
	vector_t *centroids; /* Data centroids.           */
	vector_t tmp;        /* Temporary centroid.       */
	int nclusters;       /* Number of clusters.       */
	int mindistance;     /* Minimum distance.         */
	int dimension;       /* Data dimension.           */
	int too_far;         /* Too far?                  */
	int has_changed;     /* Has any centroid changed? */
};

/*
 * Computes the means of the clusters.
 */
static void compute_centroids(struct kmeans_data *k)
{
	int i, j; /* Loop indexes. */
	int size; /* Cluster size. */
	
	k->has_changed = 0;
	
	/* Compute means. */
	for (i = 0; i < k->nclusters; i++)
	{		
		/* Initialize temporary vector.*/
		vector_assign(k->tmp, k->centroids[i]);
		vector_sub(k->centroids[i], k->centroids[i]);
		
		size = 0;
		
		/* Compute cluster's mean. */
		for (j = 0; j < k->size; j++)
		{
			/* Not a member of this cluster. */
			if (k->map[j] != i)
				continue;			
			
			vector_add(k->centroids[i], ARRAY(k->data, j));
				
			size++;
		}		
		if (size > 1)
			vector_mult(k->centroids[i], 1.0/size);
			
		/* Cluster mean has changed. */
		if (!vector_equal(k->tmp, k->centroids[i]))
			k->has_changed = 1;
	}
}

#if defined KMEANS_RANDOM

/*
 * Populates clusters using the random parition method.
 */
static int random_populate(struct kmeans_data *k)
{
	int i; /* Loop index. */
	
	/* Distribute processes randomly among clusters. */
	for (i = 0; i < k->size; i++)
		k->map[i] = rand()%k->nclusters;
	
	compute_centroids(k);

	return (0);
}

#else

/*
 * Populates cluster using the Forgy method.
 */
static int forgy_populate(struct kmeans_data *k)
{
	int i, j;        /* Loop indexes.       */
	double tmp;      /* Auxiliary variable. */
	double distance; /* Current distance.   */
	
	/* Choose randomly k points from the database to be the centroids. */
	for (i = 0; i < k->nclusters; i++)
	{
		j = rand()%k->size;
		
		vector_assign(k->centroids[i], ARRAY(k->data, j));
	} 
	
	/* Distribute processes among clusters. */
	for (i = 0; i < k->size; i++)
	{
		distance = vector_distance(k->centroids[k->map[0]], ARRAY(k->data, i));
		k->map[i] = 0;
		
		/* Look for closest cluster. */
		for (j = 1; j < k->nclusters; j++)
		{	
			tmp = vector_distance(k->centroids[j], ARRAY(k->data, i));
			
			/* Found. */
			if (tmp < distance)
			{
				k->map[i] = j;
				distance = tmp;
			}
		}
	}
	
	return (0);
}

#endif
	
/*
* Populates clusters.
*/
static void kmeans_populate(struct kmeans_data *k)
{
	int i, j;        /* Loop index.         */
	double tmp;      /* Auxiliary variable. */
	double distance; /* Current distance.   */
	
	k->too_far = 0;
	
	/* Iterate over processes. */
	for (i = 0; i < k->size; i++)
	{		
		distance = vector_distance(k->centroids[k->map[i]], ARRAY(k->data, i));		
		
		/* Look for closest cluster. */
		for (j = 0; j < k->nclusters; j++)
		{	
			tmp = vector_distance(k->centroids[j], ARRAY(k->data, i));
			
			/* Found. */
			if (tmp < distance)
			{
				k->map[i] = j;
				distance = tmp;
				k->migration++;
			}
		}
		
		/* Cluster is too far away. */
		if (distance > k->mindistance)
			k->too_far = 1;
	}
}

/*
 * Initializes k-means.
 */
struct kmeans_data *kmeans_init(array_t data, int nclusters, int mindistance)
{
	int i;                 /* Loop index.           */
	int size;              /* Data size.            */
	int *map;              /* Data map.             */
	vector_t tmp;          /* temporary mean.       */
	int dimension;         /* Data dimension.       */
	vector_t *centroids;   /* Data centroids.       */
	struct kmeans_data *k; /* K-means data.         */
	
	size = array_size(data);
	
	/* Allocate data structures. */
	dimension = vector_size(ARRAY(data, 0));
	k = smalloc(sizeof(struct kmeans_data));
	map = scalloc(size, sizeof(int));
	tmp = vector_create(dimension);
	centroids = smalloc(nclusters*sizeof(vector_t));
	
	/* Create centroids. */
	for (i = 0; i < nclusters; i++)
		centroids[i] = vector_create(dimension);
	
	/* Initialize k-means data. */
	k->data = data;
	k->map = map;
	k->size = size;
	k->migration = 0;
	k->centroids = centroids;
	k->tmp = tmp;
	k->nclusters = nclusters;
	k->mindistance = mindistance;
	k->dimension = dimension;
	k->too_far = 0;
	k->has_changed = 0;
	
	return (k);
}

/*
 * Ends k-means.
 */
int *kmeans_end(struct kmeans_data *k)
{
	int *map;
		
	map = k->map;
	
	vector_destroy(k->tmp);
	free(k->centroids);
	free(k);

	return (map);
}

/*
 *  Clusters data.
 */
int *kmeans(array_t data, int nclusters, int mindistance)
{
	struct kmeans_data *k;

	k = kmeans_init(data, nclusters, mindistance);

#if defined KMEANS_RANDOM
	random_populate(k);
#else
	forgy_populate(k);
#endif

	/* Apply custerization algorithm. */
	do
	{
		kmeans_populate(k);		
		compute_centroids(k);
		
	} while (k->too_far && k->has_changed);
	
	return (kmeans_end(k));
}
