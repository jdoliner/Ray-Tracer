/*! \file util.c
 *
 * \brief This file contains various utility functions.
 *
 * \author John Reppy
 */

/* CMSC23700 Sample code
 *
 * COPYRIGHT (c) 2010 John Reppy (http://www.cs.uchicago.edu/~jhr)
 * All rights reserved.
 */

#include "defs.h"
#include <sys/time.h>
#include <stdio.h>

/* GetTime:
 */
double GetTime ()
{
    struct timeval	t;
    
    gettimeofday (&t, 0);
    return (double)t.tv_sec + 0.000001*(double)t.tv_usec;

}

/* CheckMalloc:
 */
void *CheckMalloc (size_t nbytes)
{
    void *obj = malloc(nbytes);
    if (obj == 0) {
	fprintf(stderr, "Fatel error: unable to allocate %d bytes\n", (int)nbytes);
	exit (1);
    }

    return obj;
}
