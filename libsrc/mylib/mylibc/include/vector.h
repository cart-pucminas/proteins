/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * <vector.h> - Vector library.
 */

#ifndef VECTOR_H_
#define VECTOR_H_

/*============================================================================*
 *                             Private Interface                              *
 *============================================================================*/
 
	/*
	 * Vector.
	 */
	struct vector
	{
		int size;         /* Size.     */
		double *elements; /* Elements. */
	};

/*============================================================================*
 *                             Public Interface                               *
 *============================================================================*/

	/*
	 * Opaque pointer to a vector.
	 */
	typedef struct vector * vector_t;
	
	/*
	 * Returns the size of a vector.
	 */
	#define vector_size(v) \
		(((vector_t) (v))->size)
	
	/*
	 * Creates a vector.
	 */
	extern struct vector *vector_create(int n);
	
	/*
	 * Destroys a vector.
	 */
	extern void vector_destroy(struct vector *v);
	
	/*
	 * Assigns a vector to another.
	 */
	extern vector_t vector_assign(vector_t v1, vector_t v2);
	
	/*
	 * Adds two vectors.
	 */
	extern vector_t vector_add(vector_t v1, vector_t v2);
	
	/*
	 * Subtracts two vectors.
	 */
	extern vector_t vector_sub(vector_t v1, vector_t v2);
	
	/*
	 * Multiplies a vector by a scalar.
	 */
	vector_t vector_mult(vector_t v, double scalar);
	
	/*
	 * Computes the euclidean distance between two vectors.
	 */
	extern double vector_distance(vector_t a, vector_t b);
	
	/*
	 * Tests if two vectors are equal.
	 */
	extern int vector_equal(vector_t a, vector_t b);

	/*
	 * Returns the element [i] in a vector.
	 */
	#define VECTOR(v, i) \
		(((vector_t)(v))->elements[(i)])

#endif /* VECTOR_H_ */
