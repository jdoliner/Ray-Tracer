/*! \file sphere.h
 *
 * \brief A representation of a sphere
 *
 * \author Joe Doliner
 */

#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "geometry.h"

/*! structure to represent a sphere */
typedef struct {
    float	radius;		/*!< the radius of the sphere */
} Geo_Sphere_t;

/*! \brief intersect a ray with a sphere, only returns the first intersection point
 */
Intersection_t *Intersect_Sphere(Rayf_t *ray, Geo_Sphere_t *sphere);
#endif
