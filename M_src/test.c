#include "../includes/miniRT.h"

t_obj create_tobj_sphre(double x, double y, double z, double cx, double cy, double cz, double px)
{
    t_obj sphere;
    t_vec coordonnee_sphere;
    coordonnee_sphere.x = x;
    coordonnee_sphere.y = y;
    coordonnee_sphere.z = z;

    t_vec color_sphere;
    color_sphere.x = cx;
    color_sphere.y = cy;
    color_sphere.z = cz;

    sphere.p.x = px;
    sphere.color = color_sphere;
    sphere.coord = coordonnee_sphere;
    return sphere;
}

t_scene create_scene()
{
    t_scene scene;

    // create cam
    t_cam camera;
    camera.coord.x = 0;
    camera.coord.y = 0;
    camera.coord.z = -80;
    camera.orient.x = 11;
    camera.orient.y = 11;
    camera.orient.z = 11;
    camera.FOV = 60 * 3.14159265359 / 100;
    scene.camera = camera;

    // create light
    t_light *light;
    light = malloc(sizeof(t_light));
    light->coord.x = 4;
    light->coord.y = 1;
    light->coord.z = -5;
    light->ratio = 100000000;
    scene.light = light;

    scene.obj = NULL;

    // create sol
    t_obj *new_obj = malloc(sizeof(t_obj));
    *new_obj = create_tobj_sphre(2, 3, -4, 255, 0, 0, 0.8);
    new_obj->next = NULL;
    scene.obj = new_obj;


    // create mur_gauche
  

    return scene;
}