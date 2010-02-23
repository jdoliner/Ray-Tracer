/*! \file geometry.h
 *
 * \brief A representation of a geometry object in a scene
 *
 * \author Joe Doliner
 */

#include "geometry.h"
#include "primtives/sphere.h"
#include "primitives/box.h"
#include "primitives/torus.h"
#include "../engine/defs.h"

/* !Calculate_Bbox
 * \brief calculates and sets the bounding box of a geometry object in global coordinates
 */
void Calculate_Bbox(Geometry_t *geometry) {
    switch (geometry->prim_type) {
	case SPHERE:
	    break;
	case BOX:
	    break;
	case TORUS:
	    break;
	default:
	    return ;
    }
}

/* !Intersect
 * \brief intersect a ray with a geometry object
 */
Intersection_t *Intersect(Rayf_t *ray, Geometry_t *geometry) {
    /* set up the ray in geometry space */
    Rayf_t geospaceRay;
    CopyV3f(ray->dir, geospaceRay.dir);
    CopyV3f(ray->orig, geospaceRay.orig);

    RotateVecByQuatf(geometry->rot, ray->orig, ray->orig);
    RotateVecByQuatf(geometry->rot, ray->dir, ray->dir);

    AddV3f(ray->orig, geometry->trans, ray->orig);

    /*now the ray is ready */
    Intersection_t *intersection;
    
    switch(geometry->prim_type) {
	case SPHERE:
	    intersection = Intersect_Sphere(geospaceRay, geometry->primitive.sphere);
	    break;
	case BOX:
	    intersection = Intersect_Box(geospaceRay, geometry->primitive.box);
	    break;
	case TORUS:
	    intersection = Intersect_Torus(geospaceRay, geometry->primitive.torus);
	    break;
	default:
	    assert(0);
    }

    /* stubs out here */
}
