/*! \file intersection.h
 *
 * \brief A representation of an intersection between an object and a ray
 *
 * \author Joe Doliner
 */

#ifndef _INTERSECTION_H_
#define _INTERSECTION_H_

#include "material.h"

/*! struct for in intersection between a ray and a piece of geometry */
typedef struct {
    float 		t;		/*!< the parameter of the first intersection */
    Vec3f_t		point;		/*!< the point of intersection */
    Vec3f_t		norm;		/*!< the normal of the object at the point of intersection */
    Material_t		*material;	/*!< the geometry object we hit */
    float		u;		/*!< the u parameter */
    float		v;		/*!< the v parameter */
    void		*geo;		/*!< the geometry we hit */
} Intersection_t;

#endif
