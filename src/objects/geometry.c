/*! \file geometry.h
 *
 * \brief A representation of a geometry object in a scene
 *
 * \author Joe Doliner
 */

#include "geometry.h"
#include "primitives/sphere.h"
#include "primitives/box.h"
#include "primitives/torus.h"
#include "../engine/defs.h"
#include "intersection.h"

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
Intersection_t *Intersect_Geo(Rayf_t ray, Geometry_t *geometry) {
    /* set up the ray in geometry space */
    Rayf_t geospaceRay;
    CopyV3f(ray.dir, geospaceRay.dir);
    CopyV3f(ray.orig, geospaceRay.orig);
    /* Quatf_t inverseRot;
    InverseQuatf(geometry->rot, inverseRot); */

    /* RotateVecByQuatf(inverseRot, ray->orig, ray->orig);
    RotateVecByQuatf(inverseRot, ray->dir, ray->dir); */

    SubV3f(geospaceRay.orig, geometry->trans, geospaceRay.orig);

    /*now the ray is ready */
    Intersection_t *intersection;
    
    switch(geometry->prim_type) {
	case SPHERE:
	    intersection = Intersect_Sphere(&geospaceRay, &(geometry->primitive->sphere));
	    break;
	case BOX:
	    intersection = Intersect_Box(&geospaceRay, &(geometry->primitive->box));
	    break;
	case TORUS:
	    intersection = Intersect_Torus(&geospaceRay, &(geometry->primitive->torus));
	    break;
	default:
	    assert(0);
    }

    if(intersection != NULL) {
	AddV3f(intersection->point, geometry->trans, intersection->point);
	intersection->material = geometry->material;
    }

    return intersection;
}
