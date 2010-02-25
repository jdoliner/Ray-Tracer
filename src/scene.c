/*! \file scene.c
 *
 * \brief Implementation of functions for a scene
 *
 * \author Joe Doliner
 */

/*! \brief intersect a ray with an entire scene
 */

#include "objects/geometry.h"
#include "objects/light.h"
#include "objects/intersection.h"
#include "engine/vector.h"
#include "engine/EasyBMP/EasyBMP.h"
#include "scene.h"
#include <float.h>

/* !Intersect_Scene
 * \brief intersect a ray with an entire scene.
 */
Intersection_t *Intersect_Scene(Rayf_t *ray, Scene_t *scene) {
    int i;
    float t_to_beat = FLT_MAX;
    Intersection_t *candidate = NULL, *answer = NULL;
    for (i = 0; i < scene->nGeo; i++) {
	candidate = Intersect_Geo(ray, scene->geometry[i]);
	if (candidate != NULL) {
	    if (candidate->t < t_to_beat) {
		t_to_beat = candidate->t;
		if (answer != NULL)
		    free(answer);
		answer = candidate;
	    } else {
		free(candidate);
	    }
	}
    }

    return answer;
}

/* !Trace_Ray
 * \brief shoots a ray into a scene and returns the color of the pixel
 */
Color_t *Trace_Ray(Rayf_t *ray, Scene_t *scene) {
    Intersection_t *intersection = Intersect_Scene(ray, scene);
    Color_t *color = NEW(Vec3f_t);
    CopyColor(intersection->material->diffuse_color, *color);
    return color;
}

/* !Render_Scene
 * \brief Shoots rays in to a scene to evaluate their color and returns them as an hres by vres array
 */
Color_t *Render_Scene(Scene_t *scene, int wres, int hres) {
    int i, j;
    Color_t *render = NEWVEC(Color_t, wres * hres);
    
    /* first we need to figure out how far away the points the rays intersect the screen at are */
    float woffsetLength = scene->camera->width / (wres - 1), hoffsetLength = scene->camera->height / (hres - 1);

    Vec3f_t cam_dir;
    Vec3f_t woffset, hoffset;

    SubV3f(scene->camera->look_at, scene->camera->pos, cam_dir);

    /* notice that this doesn't get messed up of up is not perpendicular to cam_dir */
    CrossV3f(cam_dir, scene->camera->up, woffset);
    CrossV3f(cam_dir, woffset, hoffset);

    NormalizeV3f(woffset);
    NormalizeV3f(hoffset);

    ScaleV3f(woffsetLength, woffset, woffset);
    ScaleV3f(hoffsetLength, hoffset, hoffset);

    Rayf_t ray; /* the ray we'll shoot into the scene */
    CopyV3f(scene->camera->pos, ray->orig);

    for (i = 0; i < wres; i++) {
	for (j = 0;j < hres; j++) {
	    //XXX pick up here XXX
	    Vec3f_t wscreenpos, hscreenpos;
	}
    }
}
