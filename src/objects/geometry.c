/*! \file geometry.h
 *
 * \brief A representation of a geometry object in a scene
 *
 * \author Joe Doliner
 */

#include "geometry.h"
#include "../engine/defs.h"

/* !Calculate_Bbox
 * \brief calculates and sets the bounding box of a geometry object in global coordinates
 */
void Calculate_Bbox(Geometry_t *geometry) {
    switch (geometry->prim_type) {
	case SPHERE:
	    geometry->bBox.corner[0][0] = geometry->bBox.corner[0][1] = geometry->bBox.corner[0][2] = -geometry->primitive.sphere.radius;
	    geometry->bBox.corner[1][0] = geometry->bBox.corner[1][1] = geometry->bBox.corner[1][2] = -geometry->primitive.sphere.radius;
	    break;
	case BOX:
	    break;
	case TORUS:
	    break;
    }
}

/* !Intersect
 * \brief 
 */
Intersection_t *Intersect(Rayf_t *ray, Geometry_t *geometry) {

}
