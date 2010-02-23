/*! \file intersection.h
 *
 * \brief A representation of an intersection between an object and a ray
 *
 * \author Joe Doliner
 */

#ifndef _INTERSECTION_H_
#define _INTERSECTION_H_

/*! struct for in intersection between a ray and a piece of geometry */
typedef struct {
    float 		t;		/*!< the parameter of the first intersection */
    Vec3f_t		point;		/*!< the point of intersection */
    Vec3f_t		norm;		/*!< the normal of the object at the point of intersection */
} Intersection_t;

#endif
