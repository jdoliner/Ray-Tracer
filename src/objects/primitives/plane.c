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

	/* compute texture coordinates */
	/* first we need a coordinate system */
	Vec3f_t v1 = {1, 0, 0}, v2;
	if (ParallelV3f(v1, plane->N)) {
	    v1[0] = 0;
	    v1[1] = 1;
	    v1[2] = 0;
	}

	Vec3f_t v1projN;
	ProjectV3f(v1, plane->N, v1projN);
	SubV3f(v1, v1projN, v1);
	CrossV3f(v1, plane->N, v2);

	NormalizeV3f(v1);
	NormalizeV3f(v2);

	/* compute u and v coordinates */
	Vec3f_t pvec;
	SubV3f(intersection->point, plane->P, pvec);
	float u = DotV3f(pvec, v1), v = DotV3f(pvec, v2);

	/* map u from [-infty, infty] to [0, 1] */
	if (u < 0)
	    u--;
	else
	    u++;

	u = ((1 / u) + 1) / 2;

	/* map v from [-infty, infty] to [0, 1] */
	if (v < 0)
	    v--;
	else
	    v++;

	v = ((1 / v) + 1) / 2;

	intersection->u = u;
	intersection->v = v;

	return intersection;
    }

    return NULL;
}
