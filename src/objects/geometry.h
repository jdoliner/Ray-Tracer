/*! \file geometry.h
 *
 * \brief A implemention of a geometry object in a scene
 *
 * \author Joe Doliner
 */

#ifndef _GEOMETRY_H
#define _GEOMETRY_H

#include "material.h"
#include "bbox.h"
#include "../engine/vector.h"
#include "../engine/quat.h"
#include "primitives/sphere.h"
#include "primitives/box.h"
#include "primitives/torus.h"

/*! the different supported primitives */
typedef enum {
    SPHERE = 0,
    BOX,
    TORUS,
    NUM_PRIMS,
} Prim_Type_t;

/*! abstraction of a primitive */
typedef union {
    Geo_Sphere_t 	sphere; 	/*!< a pointer a sphere */
    Geo_Box_t 		box;		/*!< a pointer a cube*/
    Geo_Torus_t		torus;		/*!< a pointer a torus*/
} Primitive_t;

/*! the struct of a geometry object */
typedef struct {
    Vec3f_t		loc;		/*!< the location of the object */
    Vec3f_t		scale;		/*!< scaling along the objects x,y,z coordinates */
    Quatf_t		rot;		/*!< the rotation of the object */
    BBox_t		bBox;		/*!< a bounding box around the object */
    Material_t		*material; 	/*!< information about how to render the object */
    Prim_Type_t		prim_type;	/*!< what type of primitive we have */ 
    Primitive_t		primitive;	/*!< what point to the object primitive */
} Geometry_t;

/*! struct for in intersection between a ray and a piece of geometry */
typedef struct {
    float 		t;		/*!< the parameter of the first intersection */
    Vec3f_t		point;		/*!< the point of intersection */
    Vec3f_t		norm;		/*!< the normal of the object at the point of intersection */
} Intersection_t;

#endif
