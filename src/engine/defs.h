/*! \file defs.h
 *
 * \brief This file contains miscellaneous definitions used in the program.
 *
 * \author John Reppy
 */

/* CMSC23700 Sample code
 *
 * COPYRIGHT (c) 2010 John Reppy (http://www.cs.uchicago.edu/~jhr)
 * All rights reserved.
 */

#ifndef _DEFS_H_
#define _DEFS_H_

/* incude standard headers */
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

/*! \brief return the current time.
 *  \returns the time in seconds since some start time.
 */
extern double GetTime ();

/*! \brief allocate heap memory checking for failure.
 *  \param nbytes the amount of memory to allocate in bytes.
 *  \returns the allocated object.
 */
extern void *CheckMalloc (size_t nbytes);

#define NEW(ty)		(ty *)CheckMalloc(sizeof(ty))
#define NEWVEC(ty, n)	(ty *)CheckMalloc(sizeof(ty)*(n))

#endif /* !_DEFS_H_ */
