/*! \file light.h
 *
 * \brief A representation of a light object
 *
 * \author Joe Doliner
 */

/*! the struct of a geometry object */

#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "../engine/vector.h"

typedef struct {
    Color_t	color;		/*!< the diffuse color of the light */
    float	intensity;	/*!< the internsity of the light */
    Vec3f_t	pos;		/*!< position in global coordinates of the light */
    Vec3f_t	look_at;	/*!< the position the light is looking at */
} Light_t;

#endif
