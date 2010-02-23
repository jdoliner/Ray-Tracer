/*! \file sphere.c
 *
 * \brief Implementation of functions for a sphere 
 *
 * \author Joe Doliner
 */

#include "../geometry.h"
#include "sphere.h"

/*! \brief intersect a ray with a sphere, only returns the first intersection point
 */
Intersection_t *Intersect_Sphere(Rayf_t *ray, Geo_Sphere_t *sphere) {
    /* values for the quadric equation */
    float a = LengthSqV3f(ray->dir); 
    float b = 2 * DotV3f(ray->dir, ray->orig);
    float c = LengthSqV3f(ray->orig) - Sqrf(sphere->radius);
    float D = Sqrf(b) - (4 * a * c);

    if (D < 0)
	return NULL;
    else {
	float t1 = (-b - sqrtf(D)) / (2 * a), t2 = (-b + sqrtf(D)) / (2 * a); /* two candidate intersection parameters */
	float t; /* the smallest positive candidate intersection parameter */
	
	/* if only 1 is negative the ray starts inside the sphere
	 * if both are negative the sphere is behind the ray
	 * either way there's no intersection
	 */
	if (t1 <= 0 || t2 <= 0)
	    return NULL;
	else
	    t = Minf(t1, t2);

	Intersection_t *intersection = NEW(Intersection_t);
	intersection->t = t;
	RayToPointf(ray, t, intersection->point);

	/* for a sphere centered at the origin the normal of a point is the vector from the point to the origin */
	CopyV3f(intersection->point, intersection->norm);
	NormalizeV3f(intersection->norm);
    }
}
