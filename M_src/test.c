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
    camera.coord.z = 0;
    camera.orient.x = 11;
    camera.orient.y = 11;
    camera.orient.z = 11;
    camera.FOV = 60 * 3.14159265359 / 100;
    scene.camera = camera;

    // create light
    t_light *light;
    light = malloc(sizeof(t_light));
    light->coord.x = 30;
    light->coord.y = 50;
    light->coord.z = -20;
    light->ratio = 100000000;
    scene.light = light;

    scene.obj = NULL;

    // create sol
    t_obj *new_obj = malloc(sizeof(t_obj));
    *new_obj = create_tobj_sphre(0, -2050, 0, 195, 153, 237, 2000);
    new_obj->next = NULL;
    scene.obj = new_obj;

    // create plafond
    new_obj->next = malloc(sizeof(t_obj));
    new_obj = new_obj->next;
    *new_obj = create_tobj_sphre(0, 2100, 0, 192, 192, 192, 2000);
    new_obj->next = NULL;

    // create mur_gauche
    new_obj->next = malloc(sizeof(t_obj));
    new_obj = new_obj->next;
    *new_obj = create_tobj_sphre(-2050, 0, 0, 0, 0, 128, 2000);
    new_obj->next = NULL;

    // create mur_droit
    new_obj->next = malloc(sizeof(t_obj));
    new_obj = new_obj->next;
    *new_obj = create_tobj_sphre(2050, 0, 0, 0, 128, 128, 2000);
    new_obj->next = NULL;

    // create mur_fond
    new_obj->next = malloc(sizeof(t_obj));
    new_obj = new_obj->next;
    *new_obj = create_tobj_sphre(0, 0, -2100, 128, 0, 128, 2000);
    new_obj->next = NULL;

    new_obj->next = malloc(sizeof(t_obj));
    new_obj = new_obj->next;
    *new_obj = create_tobj_sphre(0, 0, -55, 246, 145, 9, 20);
    new_obj->next = NULL;

    return scene;
}