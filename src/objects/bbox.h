/*! \file geometry.h
 *
 * \brief A implemention of a geometry object in a scene
 *
 * \author Joe Doliner
 */

#ifndef _BBOX_H
#define _BBOX_H

#include "../engine/vector.h"

/* !struct to store a bounding box
 * bounding boxes are always specified in global coordinates
 */
typedef struct {
    Vec3f_t	corner[2]; /* !< opposing corners of the bounding box */
} BBox_t;

#endif
