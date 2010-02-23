/*! \file camera.h
 *
 * \brief A representation of a camera object
 *
 * \author Joe Doliner
 */

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "../engine/vector.h"

typedef struct {
    Vec3f_t	pos;		/*!< position in global coordinates of the light */
    Vec3f_t	look_at;	/*!< the position the light is looking at */
    Vec3f_t	up;		/*!< which way is up for the camera */
} Camera_t;

#endif
