#include "../includes/miniRT.h"

int close_window()
{
    exit(0);
}

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
    scene.obj = NULL; 

    // create sol
    t_obj *new_obj = malloc(sizeof(t_obj));
    *new_obj = create_tobj_sphre(0, -2050, 0, 255, 255, 255, 2000);
    new_obj->next = NULL;
    scene.obj = new_obj;

    // create plafond
    new_obj->next = malloc(sizeof(t_obj));
    new_obj = new_obj->next;
    *new_obj = create_tobj_sphre(0, 2100, 0, 255, 255, 255, 2000);
    new_obj->next = NULL;

    // create mur_gauche
    new_obj->next = malloc(sizeof(t_obj));
    new_obj = new_obj->next;
    *new_obj = create_tobj_sphre(-2050, 0, 0, 0, 255, 0, 2000);
    new_obj->next = NULL;

     // create mur_droit
    new_obj->next = malloc(sizeof(t_obj));
    new_obj = new_obj->next;
    *new_obj = create_tobj_sphre(2050, 0, 0, 0, 0, 255, 2000);
    new_obj->next = NULL;

    // create mur_fond
    new_obj->next = malloc(sizeof(t_obj));
    new_obj = new_obj->next;
    *new_obj = create_tobj_sphre(0, 0, -2100, 0, 255, 255, 2000);
    new_obj->next = NULL;
    
    new_obj->next = malloc(sizeof(t_obj));
    new_obj = new_obj->next;
    *new_obj = create_tobj_sphre(0, 0, -55, 255, 0, 0, 20);
    new_obj->next = NULL;

    

    return scene;
}

int main(void)
{
    void *mlx_ptr;
    void *win_ptr;
    int W = 1024;
    int H = 1024;
    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, W, H, "MiniLibX Example");

    mlx_hook(win_ptr, 17, 1L << 17, close_window, NULL);

    unsigned char *image = (unsigned char *)malloc(W * H * 3);

    t_scene scene;
    scene = create_scene();

    t_cam camera;
    camera.coord.x = 0;
    camera.coord.y = 0;
    camera.coord.z = 0;
    camera.orient.x = 11;
    camera.orient.y = 11;
    camera.orient.z = 11;
    camera.FOV = 60 * 3.14159265359 / 100;

    t_light light;
    light.coord.x = 15;
    light.coord.y = 70;
    light.coord.z = -30;
    light.ratio = 1000000;

    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            t_ray ray;
            ray.coord = camera.coord;
            ray.direction.x = j - W / 2;
            ray.direction.y = i - H / 2;
            ray.direction.z = -W / (2 * tan(camera.FOV / 2));
            ray.direction = normalize(ray.direction);

            t_vec p, n;
            t_obj intersect_obj;
            bool intersect = intersection_scene(scene ,ray, &p, &n, &intersect_obj);

            t_vec intensite_pixel_color;
            intensite_pixel_color.x = 0;
            intensite_pixel_color.y = 0;
            intensite_pixel_color.z = 0;
            if (intersect)
            {
                t_vec pos_light_p = vec_subtract(light.coord, p);
                t_vec n_pos_light_p = normalize(pos_light_p);
                double ps_n_pos_light_p_n = dot_product(n_pos_light_p, n);
                if (ps_n_pos_light_p_n < 0)
                {
                    ps_n_pos_light_p_n = 0;
                }
                double intensite_pixel;
                intensite_pixel = light.ratio * ps_n_pos_light_p_n / norm(pos_light_p);

                intensite_pixel_color = vec_multiply(normalize_color(intersect_obj.color), intensite_pixel);
                intensite_pixel_color.x = (intensite_pixel_color.x > 255) ? 255 : ((intensite_pixel_color.x < 0) ? 0 : intensite_pixel_color.x);
                intensite_pixel_color.y = (intensite_pixel_color.y > 255) ? 255 : ((intensite_pixel_color.y < 0) ? 0 : intensite_pixel_color.y);
                intensite_pixel_color.z = (intensite_pixel_color.z > 255) ? 255 : ((intensite_pixel_color.z < 0) ? 0 : intensite_pixel_color.z);
            }

            image[((H - i - 1) * W + j) * 3 + 0] = (unsigned char)intensite_pixel_color.x;
            image[((H - i - 1) * W + j) * 3 + 1] = (unsigned char)intensite_pixel_color.y;
            image[((H - i - 1) * W + j) * 3 + 2] = (unsigned char)intensite_pixel_color.z;
        }
    }

    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            unsigned int result = (image[(i * W + j) * 3 + 0] << 16) | (image[(i * W + j) * 3 + 1] << 8) | image[(i * W + j) * 3 + 2];
            mlx_pixel_put(mlx_ptr, win_ptr, i, j, result);
        }
    }

    save_img("out.bmp", &image[0], W, H);
    printf("OK");
    mlx_loop(mlx_ptr);

    return 0;
}
