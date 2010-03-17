/*! \file geometry.c
 *
 * \brief A representation of a geometry object in a scene
 *
 * \author Joe Doliner
 */

#include "geometry.h"
#include "primitives/sphere.h"
#include "primitives/box.h"
#include "primitives/torus.h"
#include "primitives/plane.h"
#include "../engine/defs.h"
#include "intersection.h"
#include "../engine/image.h"

#define VARIANCE_CUTOFF 0.3f

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
	case PLANE:
	    intersection = Intersect_Plane(&geospaceRay, &(geometry->primitive->plane));
	    break;
	default:
	    assert(0);
    }

    if(intersection != NULL) {
	AddV3f(intersection->point, geometry->trans, intersection->point);
	intersection->material = geometry->material;
	intersection->geo = geometry;
    }

    return intersection;
}

/* !Init_Rex
 * \brief rex pointer to the rex to initiate
 * \brief resolution the resolution of the rex
 */
void Init_Rex(Rex_t *rex, int resolution) {
    int i, j;

    rex->value = NEWVEC(Color_t *, resolution);
    rex->vec = NEWVEC(Vec3f_t *, resolution);
    rex->nSamples = NEWVEC(int *, resolution);

    for (i = 0; i < resolution; i++) {
	rex->value[i] = NEWVEC(Color_t, resolution);
	rex->vec[i] = NEWVEC(Vec3f_t, resolution);
	rex->nSamples[i] = NEWVEC(int, resolution);
    }

    Color_t init_color = {0, 0, 0, 255};
    Vec3f_t init_vec = {0.0f, 0.0f, 0.0f};

    for (i = 0; i < resolution; i++) {
	for (j = 0; j < resolution; j++) {
	    CopyColor(init_color, rex->value[i][j]);
	    CopyV3f(init_vec, rex->vec[i][j]);
	    rex->nSamples[i][j] = 0;
	}
    }
    rex->resolution = resolution;
}

/* !CatchSpec_Rex
 * \brief evaluate a rex for spec at parameter
 * \param Rex_t *rex the rex to evaluate
 * \param u the u parameter
 * \param v the v parameter
 * \param the vector we're viewing along
 * \param dst output color
 */
void CatchSpec_Rex(Rex_t *rex, float u, float v, Vec3f_t vec, Color_t dst) {
    int i = GetIndex_Rex(rex, u), j = GetIndex_Rex(rex, v);
    
    ScaleColor(rex->value[i][j], Clampf(DotV3f(vec, rex->vec[i][j])), dst);
}

/* !CatchDiffuse_Rex
 * \brief evaluate a rex for diffuse at a parameter
 * \param Rex_t *rex the rex to evaluate
 * \param u the u parameter
 * \param v the v parameter
 */
void CatchDiffuse_Rex(Rex_t *rex, float u, float v, Color_t dst) {
    int i = GetIndex_Rex(rex, u), j = GetIndex_Rex(rex, v);

    CopyColor(rex->value[i][j], dst);
}

/* !ThrowSpec_Rex
 * \brief Throw a ray onto a rex
 * \param Rex_t *rex the rex to use
 * \param float u the u parameter
 * \param float v the v parameter
 * \param Vec3f_t vec the vector along which the spec intensity is maximal
 * \param Color_t color the color of the spec ray
 */
void ThrowSpec_Rex(Rex_t *rex, float u, float v, Vec3f_t vec, Color_t color) {
    int i = GetIndex_Rex(rex, u), j = GetIndex_Rex(rex, v);

    rex->nSamples[i][j]++;

    LerpV3f(rex->vec[i][j], 1.0f / rex->nSamples[i][j], vec, rex->vec[i][j]);
    BlendColor(color, rex->value[i][j], 1.0f / rex->nSamples[i][j], rex->value[i][j]);
}

/* !ThrowDiffuse_Rex
 * \brief Throw a ray onto a rex
 * \param Rex_t *rex the rex to use
 * \param float u the u parameter
 * \param float v the v parameter
 * \param Color_t color the diffuse color at this parameter
 */
void ThrowDiffuse_Rex(Rex_t *rex, float u, float v, Color_t color) {
    /* printf("Throwing ray with u = %f, v = %f\n", u, v); */
    int i = GetIndex_Rex(rex, u), j = GetIndex_Rex(rex, v);

    rex->nSamples[i][j]++;

    BlendColor(color, rex->value[i][j], 1.0f / rex->nSamples[i][j], rex->value[i][j]);
}

/* !Output_Rex
 * \brief drop a rex into an image
 * \param Rex_t *rex the rex to use
 * \param const char * fname the file name to output to
 */
void Output_Rex(Rex_t *rex, const char * fname) {
    int i, j;
    Color_t *data = NEWVEC(Color_t, rex->resolution * rex->resolution);
    for (i = 0; i < rex->resolution; i++)
	for (j = 0; j < rex->resolution; j++)
	    CopyColor(rex->value[i][j], data[i + rex->resolution * j]); 

    Image_t *rex_image = New_Image(rex->resolution, rex->resolution, data);
    Write_Image(rex_image, fname);
}
