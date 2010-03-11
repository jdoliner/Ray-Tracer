#include <stdio.h>
#include "scene.h"
#include "engine/defs.h"
#include "engine/image.h"
#include "engine/parse.h"

int main (int argc, char *argv[]) {
    if (argc < 2)
	assert(0);

    Scene_t *scene;

    scene = Parse_File(argv[1]);

    int width = 1024, height = 1024;
    Color_t *render = Render_Scene(scene, width, height);
    Image_t *output = New_Image(width, height, render);

    Write_Image(output, "output.ppm");

    Delete_Image(output);

    return 0;
}
