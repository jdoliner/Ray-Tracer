#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "scene.h"
#include "objects/geometry.h"
#include "engine/defs.h"
#include "engine/image.h"
#include "engine/parse.h"

int main (int argc, char *argv[]) {
    srand(time(NULL));
    int i;

    if (argc < 2)
	assert(0);

    Scene_t *scene;

    scene = Parse_File(argv[1]);
    /* scene = Parse_File("../examples/5spheres.xml"); */

    if (scene->settings->radiosity) {
	Calculate_Rex(scene, 1024, scene->settings->rad_accuracy);
	for (i = 0; i < scene->nGeo; i++) {
	    Output_Rex(scene->geometry[i]->diffuse_rex, "rex.ppm");
	}
    }

    /* int width = 1024, height = 1024;
    Color_t *render = Render_Scene(scene, width, height);
    Image_t *output = New_Image(width, height, render);

    Write_Image(output, "output.ppm");

    Delete_Image(output); */

    return 0;
}
