/*! \file box.h
 *
 * \brief A representation of a rectangular prism
 *
 * \author Joe Doliner
 */

#ifndef _BOX_H_
#define _BOX_H_

/*! structure to store a box
 * box has faces lying in planes x = +- rx, y = +- ry, z = +- rz */
typedef struct {
    Vec3f_t	r; /*! {rx, ry, rz} this is the most positive corner of the box too */
} Geo_Box_t;

#endif
