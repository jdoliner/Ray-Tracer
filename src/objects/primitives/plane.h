/*! \file box.h
 *
 * \brief A representation of a rectangular prism
 *
 * \author Joe Doliner
 */

#ifndef _PLANE_H_
#define _PLANE_H_

#include "../intersection.h"

/*! structure to store a plane
 */
typedef struct {
    Vec3f_t	N;	/* <! the normal of the plane */
    Vec3f_t	P;	/* <! a point in the plane */
} Geo_Plane_t;

/*! \brief intersect a ray with a box, only returns the first intersection point
 */
Intersection_t *Intersect_Plane(Rayf_t *ray, Geo_Plane_t *plane);


#endif
