/*! \file scene.h
 *
 * \brief A representation of a scene to be rendered
 *
 * \author Joe Doliner
 */

#ifndef _SCENE_H_
#define _SCENE_H_

#include "objects/geometry.h"
#include "objects/light.h"
#include "objects/camera.h"

/*! \brief settings for a scene */
typedef struct {
    int pass;
} Settings_t;

/*! \brief a scene */
typedef struct {
    int			nGeo;		/*!< the number of geometry objects in the scene */
    int			nLights;	/*!< the number of light objects in the scene */
    Geometry_t 		**geometry;	/*!< an array of geometry objects in scene */
    Light_t		**light;	/*!< an array of light objects in the scene */
    Camera_t		*camera;	/*!< the camera in the scene */
    Settings_t		settings;	/*!< global properties in the scene */
} Scene_t;

#endif
