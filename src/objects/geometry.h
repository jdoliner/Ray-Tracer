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
#include "primitives/plane.h"

/*! the different supported primitives */
typedef enum {
    SPHERE = 0,
    BOX,
    TORUS,
    PLANE,
    NUM_PRIMS
} Prim_Type_t;

/*! abstraction of a primitive */
typedef union {
    Geo_Sphere_t 	sphere; 	/*!< a sphere */
    Geo_Box_t 		box;		/*!< a cube*/
    Geo_Torus_t		torus;		/*!< a torus*/
    Geo_Plane_t		plane;		/*!< a plane */
} Primitive_t;

/*! radiosity texture */
typedef struct {
    Color_t	**value;		/*!< array of lighting values */
    Vec3f_t	**vec;			/*!< array of vectors (only used for spec maps) */
    int		**nSamples;		/*!< number of samples at each point */
    int 	resolution;		/*!< the resolution of the rex */
} Rex_t;

/*! the struct of a geometry object */
typedef struct {
    Vec3f_t		scale;		/*!< scaling along the objects x,y,z coordinates */
    Quatf_t		rot;		/*!< the rotation of the object */
    Vec3f_t		trans;		/*!< the translation of the object */
    BBox_t		bBox;		/*!< a bounding box around the object */
    Material_t		*material; 	/*!< information about how to render the object */
    Prim_Type_t		prim_type;	/*!< what type of primitive we have */ 
    Primitive_t		*primitive;	/*!< what point to the object primitive */
    Rex_t		*diffuse_rex;	/*!< the diffuse rex */
} Geometry_t;

/* !Intersect
 * \brief intersect a ray with a geometry object
 */
Intersection_t *Intersect_Geo(Rayf_t ray, Geometry_t *geometry);

/* !GetIndex_Rex
 * \brief convert a paramter into an index
 * \param rex the rex in question
 * \param p the parameter we're using
 */
static inline int GetIndex_Rex(Rex_t *rex, float p) {
    int i = lrint(rex->resolution * p);
    if (i == rex->resolution)
	i--;

    return i;
}

/* !Init_Rex
 * \brief rex pointer to the rex to initiate
 * \brief resolution the resolution of the rex
 */
void Init_Rex(Rex_t *rex, int resolution);

/* !CatchSpec_Rex
 * \brief evaluate a rex for spec at parameter
 * \param Rex_t *rex the rex to evaluate
 * \param u the u parameter
 * \param v the v parameter
 * \param the vector we're viewing along
 * \param dst output color
 */
void CatchSpec_Rex(Rex_t *rex, float u, float v, Vec3f_t vec, Color_t dst);

/* !CatchDiffuse_Rex
 * \brief evaluate a rex for diffuse at a parameter
 * \param Rex_t *rex the rex to evaluate
 * \param u the u parameter
 * \param v the v parameter
 * \param dst output color
 */
void CatchDiffuse_Rex(Rex_t *rex, float u, float v, Color_t dst);

/* !ThrowSpec_Rex
 * \brief Throw a ray onto a rex
 * \param Rex_t *rex the rex to use
 * \param float u the u parameter
 * \param float v the v parameter
 * \param Vec3f_t vec the vector along which the spec intensity is maximal
 * \param Color_t color the color of the spec ray
 */
void ThrowSpec_Rex(Rex_t *rex, float u, float v, Vec3f_t vec, Color_t color);

/* !ThrowDiffuse_Rex
 * \brief Throw a ray onto a rex
 * \param Rex_t *rex the rex to use
 * \param float u the u parameter
 * \param float v the v parameter
 * \param Color_t color the diffuse color at this parameter
 */
void ThrowDiffuse_Rex(Rex_t *rex, float u, float v, Color_t color);

/* !Output_Rex
 * \brief drop a rex into an image
 * \param Rex_t *rex the rex to use
 * \param const char * fname the file name to output to
 */
void Output_Rex(Rex_t *rex, const char * fname);

#endif
