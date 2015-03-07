/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * util/randnum.c - randnum() and srandum() implementations.
 */

#include <util.h>

/* Default generator values.*/
#define DEFAULT_W 521288629
#define DEFAULT_Z 362436069

/*
 * Current random number generator state.
 */
static struct
{
	unsigned int w;
	unsigned int z;
} curr = {
	DEFAULT_W,
	DEFAULT_Z
};

/*
 * Sets a seed value for the random number generator.
 */
void srandnum(int seed) 
{
	unsigned n1, n2;
	
	n1 = (seed * 104623) % (RANDNUM_MAX);
	curr.w = (n1) ? n1 : DEFAULT_W;
	n2 = (seed * 48947) % (RANDNUM_MAX);
	curr.z = (n2) ? n2 : DEFAULT_Z;
}

/*
 * Generates a random number between 0 and 1.
 */
unsigned randnum(void)
{
	unsigned num;
  
	curr.z = 36969 * (curr.z & 65535) + (curr.z >> 16);
	curr.w = 18000 * (curr.w & 65535) + (curr.w >> 16);
	num = (curr.z << 16) + curr.w;
	
	return (num);
}
