#include "../includes/miniRT.h"

int close_window()
{
    exit(0);
}

void draw_pixel(void *mlx_ptr, void *win_ptr, int x, int y, int color, int size) {
    // Créer une image de dimensions spécifiées avec la couleur spécifiée
    int *pixel_data = (int *)malloc(size * size * sizeof(int));
    for (int i = 0; i < size * size; i++) {
        pixel_data[i] = color;
    }

    void *image = mlx_new_image(mlx_ptr, size, size);
    mlx_put_image_to_window(mlx_ptr, win_ptr, image, x, y);

    // Copier les données de pixel dans l'image
    mlx_pixel_put(mlx_ptr, image, 0, 0, color);
    mlx_destroy_image(mlx_ptr, image);

    free(pixel_data);
}

int main(void)
{
    void *mlx_ptr;
    void *win_ptr;
    int W = 800;
    int H = 800;
    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, W, H, "MiniLibX Example");
    mlx_hook(win_ptr, 17, 1L << 17, close_window, NULL);

    unsigned char *image = (unsigned char *)malloc(W * H * 3);
    // creation sphere
    t_obj sphere;
    t_col colorsphere;
    colorsphere.r = 87;
    colorsphere.g = 155;
    colorsphere.b = 23;

    t_vec coordonnee_sphere;
    coordonnee_sphere.x = 0;
    coordonnee_sphere.y = 0;
    coordonnee_sphere.z = -55;

    sphere.color = colorsphere;
    sphere.coord = coordonnee_sphere;
    sphere.p.x = 20;

    // creation de camera
    t_vec coordonnee_cam;
    coordonnee_cam.x = 0;
    coordonnee_cam.y = 0;
    coordonnee_cam.z = 0;

    t_vec orientation_cam;
    orientation_cam.x = 11;
    orientation_cam.y = 11;
    orientation_cam.z = 11;

    t_cam camera;
    camera.coord = coordonnee_cam;
    camera.orient = orientation_cam;
    camera.FOV = 60 * 3.14159265 / 100;
    t_light light;
    t_vec lightcoord;
    lightcoord.x = 20;
    lightcoord.y = 40;
    lightcoord.z = -30;
    light.coord = lightcoord;
    light.ratio = 1000000;
   

    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            t_ray ray;
            ray.coord = camera.coord;
            t_vec raydirection;
            raydirection.x = j - W / 2;
            raydirection.y = i - H / 2;
            raydirection.z = -W / (2 * tan(camera.FOV / 2));
            ray.direction = raydirection;
            ray.direction = normalize(ray.direction);
            t_vec p;
            t_vec n;
            bool intersect = intersection_sphere(ray, sphere, &p, &n);
            double intensite_pixel = 0;
            if (intersect)
            {
                t_vec pos_light_p = vec_subtract(light.coord, p);
                t_vec n_pos_light_p = normalize(pos_light_p);
                double ps_n_pos_light_p_n = dot_product(n_pos_light_p, n);
                intensite_pixel = light.ratio * ps_n_pos_light_p_n / norm(pos_light_p);
                if (intensite_pixel > 255)
                    intensite_pixel = 255;
                if (intensite_pixel < 0)
                    intensite_pixel = 0;
            }

            image[((H - i - 1) * W + (W - j - 1)) * 3 + 0] = intensite_pixel;
            image[((H - i - 1) * W + (W - j - 1)) * 3 + 1] = intensite_pixel;
            image[((H - i - 1) * W + (W - j - 1)) * 3 + 2] = intensite_pixel;
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

     for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {  if(fabs(i - camera.coord.x) < 8 && fabs(j - camera.coord.y) < 8)
            mlx_pixel_put(mlx_ptr, win_ptr, i, j, 0xFF0000);
        }
    }

     for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {  if(fabs(i - light.coord.x) < 8 && fabs(j - light.coord.y) < 8)
            mlx_pixel_put(mlx_ptr, win_ptr, i, j, 0x00FF00);
        }
    }
    
    save_img("out.bmp", &image[0], W, H);
    printf("OK");
    mlx_loop(mlx_ptr);
}