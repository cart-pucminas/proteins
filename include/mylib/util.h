/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 *
 * This file is part of MyLib.
 *
 * MyLib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * MyLib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with MyLib. If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file
 * 
 * @brief Utility Library
 */

#ifndef UTIL_H_
#define UTIL_H_

	#include <stdio.h>
	#include <stdlib.h>
	
	/**
	 * @defgroup Utility Utility
	 */
	/**@{*/

	/**
	 * @name Error Reporting
	 */
	/**@{*/
	extern void error(const char *);
	extern void warning(const char *);
	/**@}*/
	
	/**
	 * @name Memory Allocation
	 */
	/**@{*/
	extern void *smalloc(size_t);
	extern void *scalloc(size_t, size_t);
	extern void *srealloc(void *, size_t);
	/**@}*/
	
	/**
	 * @brief Maximum pseudo-random number.
	 */
	#define RANDNUM_MAX 4294967295u
	
	/**
	 * @name Number Generator
	 */
	/**@{*/
	extern void srandnum(unsigned);
	extern unsigned randnum(void);
	/**@}*/
	
	/**
	 * @brief Make something to be unused.
	 * 
	 * @param x Thing.
	 */
	#define UNUSED(x) \
		((void)(x))
	
	/**@}*/
	
	extern char *readline(FILE *);
	extern char seteol(char);

#endif /* UTIL_H_ */
