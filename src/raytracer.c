#include <stdio.h>
#include "scene.h"
#include "engine/defs.h"
#include "engine/image.h"

int main () {
    Scene_t scene;
    Init_Scene(&scene, 1, 0);
    Color_t bg_color = {0, 0, 0, 255};
    CopyColor(bg_color, scene.settings->background);

    Geo_Sphere_t sphere_data;
    sphere_data.radius = 1.0f;

    Material_t sphere_mat;
    Color_t sphere_col = {255, 0, 0, 255};
    CopyColor(sphere_col, sphere_mat.diffuse_color);

    Geometry_t sphere;
    Vec3f_t trans = {0.0, 0.0, 0.0};
    CopyV3f(trans, sphere.trans);
    sphere.primitive = (Primitive_t *) &sphere_data;
    sphere.prim_type = SPHERE;
    sphere.material = &sphere_mat;

    scene.geometry[0] = &sphere;

    Camera_t camera;
    Vec3f_t cam_pos = {10.0, 0.0, 0.0};
    Vec3f_t cam_look_at = {0.0, 0.0, 0.0};
    Vec3f_t cam_up = {0.0, 1.0, 0.0};
    
    CopyV3f(cam_pos, camera.pos);
    CopyV3f(cam_look_at, camera.look_at);
    CopyV3f(cam_up, camera.up);

    camera.focal_length = 5.0;
    camera.width = 10.0;
    camera.height = 10.0;

    scene.camera = &camera;

    int width = 512, height = 512;

    Color_t *render = Render_Scene(&scene, width, height);

    Image_t *output = New_Image(width, height, render);

    Write_Image(output, "output.ppm");

    Delete_Image(output);

    return 0;
}
