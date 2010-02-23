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
#include "scene.h"
#include <float.h>

/* !Intersect_Scene
 * \brief intersect a ray with an entire.
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


