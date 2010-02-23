/*! \file cube.c
 *
 * \brief Implementation of functions for a cube
 *
 * \author Joe Doliner
 */

#include "../geometry.h"
#include <float.h>

/*! \brief intersect a ray with a box, only returns the first intersection point
 */
Intersection_t *Intersect_Box(Rayf_t *ray, Geo_Box_t *box) {
    bool hit; /* did we get a hit */
    int i;

    Vec3f_t normal; /* the normal at the intersection with the best t */
    Vec3f_t xpoint; /* the intersection point at the intersection with the best t */
    float t_to_beat = FLT_MAX;

    for (i = 0; i < 3; i++) {
	float r; /* the radius of side that's facing us */
	float t; /* the parameter of the intersection */

	/* which side is facing the ray */
	if(ray->dir[i] < 0)
	    r = box->r[i];
	else
	    r = -box->r[i];

	t = (r - ray->orig[i]) / ray->dir[i];
	RayToPointf(ray, t, xpoint);

	/* checks to make sure the t is valid and that the point of intersection occurs inside the bounds of the box */
	if (0 < t && t < t_to_beat && Absf(xpoint[(i + 1) % 3]) <= box->r[(i + 1) % 3] && Absf(xpoint[(i + 2) % 3]) <= box->r[(i + 2) % 3]) {
	    t_to_beat = t;
	    normal[0] = normal[1] = normal[2] = 0.0;
	    normal[i] = 1.0;
	    hit = true;
	}
    }

    if (hit) {
	Intersection_t *intersection = NEW(Intersection_t);
	intersection->t = t_to_beat;
	RayToPointf(ray, t_to_beat, intersection->point);
	CopyV3f(normal, intersection->norm);
	return intersection;
    }

    return NULL;
}
