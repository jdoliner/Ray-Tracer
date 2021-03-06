/*! \file material.h
 *
 * \brief A representation of a material for objects
 *
 * \author Joe Doliner
 */

#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "../engine/vector.h"

/*! struct for a material */
typedef struct {
    Color_t	diffuse_color;	/* !< diffuse color */
    Color_t	spec_color;	/* !< specular color */
    float	spec;		/* !< how specular the object is */
    float	glossiness;	/* !< the exponent for the specular highlights */
    float	transparency;	/* !< transparency in [0, 1] */
    float	reflection;	/* !< reflection in [0, 1] */
    float	refraction;	/* !< refraction index in [0, 1] */
} Material_t;

#endif
