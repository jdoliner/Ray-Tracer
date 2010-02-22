/*! \file material.h
 *
 * \brief A representation of a material for objects
 *
 * \author Joe Doliner
 */

#include "../engine/vector.h"

/*! struct for a material */
typedef struct {
    Vec3f_t	diffuse_color;	/* !< diffuse color */
    Vec3f_t	spec_color;	/* !< specular color */
    float	spec;		/* !< how specular the object is */
    float	glossiness;	/* !< the exponent for the specular highlights */
    float	transperancy;	/* !< transparency in [0, 1] */
    float	reflection;	/* !< reflection in [0, 1] */
} Material_t;
