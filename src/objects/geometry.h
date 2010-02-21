/*! \file geometry.h
 *
 * \brief A implemention of a geometry object in a scene
 *
 * \author Joe Doliner
 */

#ifndef _GEOMETRY_H
#define _GEOMETRY_H

#include "material.h"
#include "boundingbox.h"
#include "../engine/vector.h"
#include "Primitives/sphere.h"
#include "Primitives/cube.h"
#include "Primitives/torus.h"

/*! the struct of a geometry object */
typedef struct {
    Vec3f_t		loc;		/*!< the location of the object */
    Vec3f_t		scale;		/*!< scaling along the objects x,y,z coordinates */
    Quatf_t		rot;		/*!< the rotation of the object */
    BoundingBox_t	*bBox;		/*!< a bounding box around the object */
    Material_t		*material; 	/*!< information about how to render the object */
    Prim_Type_t		*prim_type;	/*!< what type of primitive we have */ 
    Primitive_t		*primitive;	/*!< what point to the object primitive */
} Geometry_t;

/*! the different possible types of primitives */
typedef enum {
    SPHERE = 0;
    CUBE;
    TORUS;
    NUM_PRIMS;
} Prim_Type_t;

/*! abstraction of a pointer to a primitive */
typedef union {
    Geo_Sphere_t 	*sphere; 	/*!< a pointer a sphere */
    Geo_Cube_t 		*cube;		/*!< a pointer a cube*/
    Geo_Torus_t		*torus;		/*!< a pointer a torus*/
} Primitive_t;

#endif
