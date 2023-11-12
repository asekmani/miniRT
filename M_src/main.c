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

void draw_vector(void *mlx_ptr, void *win_ptr, t_vec vector, int x, int y, int size) {
    // Utiliser les composantes du vecteur pour définir la couleur
    int red = (int)(vector.x * 255);
    int green = (int)(vector.y * 255);
    int blue = (int)(vector.z * 255);

    // La couleur sera basée sur les composantes du vecteur
    unsigned int color = (red << 16) | (green << 8) | blue;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            mlx_pixel_put(mlx_ptr, win_ptr, x + i, y + j, color);
        }
    }
}

int main(void) {
    void *mlx_ptr;
    void *win_ptr;
    int W = 1024;
    int H = 1024;
    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, W, H, "MiniLibX Example");

    mlx_hook(win_ptr, 17, 1L << 17, close_window, NULL);

    unsigned char *image = (unsigned char *)malloc(W * H * 3);

    t_obj sphere;
    sphere.color.x = 76;
    sphere.color.y = 88;
    sphere.color.z = 12;
    sphere.coord.x = 0;
    sphere.coord.y = 0;
    sphere.coord.z = -55;
    sphere.p.x = 20;

    t_cam camera;
    camera.coord.x = 0;
    camera.coord.y = 0;
    camera.coord.z = 0;
    camera.orient.x = 11;
    camera.orient.y = 11;
    camera.orient.z = 11;
    camera.FOV = 60 * 3.14159265 / 100;

    t_light light;
    light.coord.x = 40;
    light.coord.y = 30;
    light.coord.z = -30;
    light.ratio = 1000000;

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            t_ray ray;
            ray.coord = camera.coord;
            ray.direction.x = j - W / 2;
            ray.direction.y = i - H / 2;
            ray.direction.z = -W / (2 * tan(camera.FOV / 2));
            ray.direction = normalize(ray.direction);

            t_vec p, n;
            double t;
            bool intersect = intersection_sphere(ray, sphere, &p, &n, &t);

            t_vec intensite_pixel_color;
            intensite_pixel_color.x = 0;
            intensite_pixel_color.y = 0;
            intensite_pixel_color.z = 0;
            if (intersect) {
                t_vec pos_light_p = vec_subtract(light.coord, p);
                t_vec n_pos_light_p = normalize(pos_light_p);
                double ps_n_pos_light_p_n = dot_product(n_pos_light_p, n);
                if(ps_n_pos_light_p_n < 0){
                    ps_n_pos_light_p_n = 0;
                }
                double intensite_pixel;
                intensite_pixel =  light.ratio * ps_n_pos_light_p_n / norm(pos_light_p);
                
                intensite_pixel_color = vec_multiply(normalize_color(sphere.color), intensite_pixel);
                 intensite_pixel_color.x = (intensite_pixel_color.x > 255) ? 255 : ((intensite_pixel_color.x < 0) ? 0 : intensite_pixel_color.x);
                 intensite_pixel_color.y = (intensite_pixel_color.y > 255) ? 255 : ((intensite_pixel_color.y < 0) ? 0 : intensite_pixel_color.y);
                 intensite_pixel_color.z = (intensite_pixel_color.z > 255) ? 255 : ((intensite_pixel_color.z < 0) ? 0 : intensite_pixel_color.z);
            }

            image[((H - i - 1 ) * W + j) * 3 + 0] = (unsigned char)intensite_pixel_color.x;
            image[((H - i - 1 ) * W + j) * 3 + 1] = (unsigned char)intensite_pixel_color.y;
            image[((H - i - 1 ) * W + j) * 3 + 2] = (unsigned char)intensite_pixel_color.z;
        }
    }

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            unsigned int result = (image[(i * W + j) * 3 + 0] << 16) | (image[(i * W + j) * 3 + 1] << 8) | image[(i * W + j) * 3 + 2];
            mlx_pixel_put(mlx_ptr, win_ptr, i, j, result);
        }
    }
    
    

    save_img("out.bmp", &image[0], W, H);
    printf("OK");
    mlx_loop(mlx_ptr);

    return 0;
}