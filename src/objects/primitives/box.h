/*! \file box.h
 *
 * \brief A representation of a rectangular prism
 *
 * \author Joe Doliner
 */

#ifndef _BOX_H_
#define _BOX_H_

/*! structure to store a box */
typedef struct {
    float	x; /* !<the length of the x dimension */
    float	y; /* !<the length of the y dimension */
    float	z; /* !<the length of the z dimension */
} Geo_Box_t;

#endif
