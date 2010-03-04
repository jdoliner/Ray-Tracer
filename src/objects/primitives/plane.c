/*! \file plane.c
 *
 * \brief Implementation of functions for a plane 
 *
 * \author Joe Doliner
 */

#include "../geometry.h"
#include <float.h>

/*! \brief intersect a ray with a box, only returns the first intersection point
 */
Intersection_t *Intersect_Plane(Rayf_t *ray, Geo_Plane_t *plane) {
    float t; /* parameter of intersection */

    t = - (DotV3f(plane->N, ray->orig) - DotV3f(plane->N, plane->P)) / DotV3f(plane->N, ray->dir);

    if (t > EPSILON) {
	Intersection_t *intersection = NEW(Intersection_t);
	intersection->t = t;
	RayToPointf(ray, t, intersection->point);
	CopyV3f(plane->N, intersection->norm);
	return intersection;
    }

    return NULL;
}
