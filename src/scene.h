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
    Color_t		background;	/*!< the background color of the scene */
} Settings_t;

/*! \brief a scene */
typedef struct {
    int			nGeo;		/*!< the number of geometry objects in the scene */
    int			nLights;	/*!< the number of light objects in the scene */
    Geometry_t 		**geometry;	/*!< an array of geometry objects in scene */
    Light_t		**light;	/*!< an array of light objects in the scene */
    Camera_t		*camera;	/*!< the camera in the scene */
    Settings_t		*settings;	/*!< global properties in the scene */
} Scene_t;

/* !New_Scene
 * \brief Allocate all the space needed for a scene and set the relevant values
 */
Scene_t *New_Scene(int nGeo, int nLights);

/* !Intersect_Scene
 * \brief intersect a ray with an entire scene.
 */
Intersection_t *Intersect_Scene(Rayf_t *ray, Scene_t *scene);

/* !Trace_Ray
 * \brief shoots a ray into a scene and returns the color of the pixel
 */
void Trace_Ray(Rayf_t *ray, Scene_t *scene, Color_t *color);

/* !Render_Scene
 * \brief Shoots rays in to a scene to evaluate their color and returns them as an hres by vres array
 * \param scene the scene to be rendered
 * \param wres width resolution (should be a power of 2)
 * \param hres height resolution (should be a power of 2)
 */
Color_t *Render_Scene(Scene_t *scene, int wres, int hres);

#endif
