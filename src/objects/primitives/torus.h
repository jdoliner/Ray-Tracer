/*! \file torus.h
 *
 * \brief A representation of a torus
 *
 * \author Joe Doliner
 */

#ifndef _TORUS_H_
#define _TORUS_H_

#include "geometry.h"

typedef struct {
    float	revRadius;	/* !< the radius of revolution */
    float	circRadius;	/* !< the radiues of the revolved circle */
} Geo_Torus_t;

/*! \brief intersect a ray with a torus, only returns the first intersection point
 */
Intersection_t *Intersect_Torus(Rayf_t *ray, Geo_Box_t *torus);

#endif
