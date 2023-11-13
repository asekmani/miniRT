/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:19:51 by asekmani          #+#    #+#             */
/*   Updated: 2023/10/26 16:19:54 by asekmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	img_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	create_rgb(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

void	init_elements(t_light *light, t_obj *sphere, t_cam *camera)
{
	sphere->color.x = 76;
    sphere->color.y = 88;
    sphere->color.z = 12;
    sphere->coord.x = 0;
    sphere->coord.y = 0;
    sphere->coord.z = -55;
    sphere->p.x = 20;

	camera->coord.x = 0;
    camera->coord.y = 0;
    camera->coord.z = 0;
    camera->orient.x = 11;
    camera->orient.y = 11;
    camera->orient.z = 11;
    camera->FOV = 60 * 3.14159265 / 100;

	light->coord.x = 40;
    light->coord.y = 30;
    light->coord.z = -30;
    light->ratio = 1000000;
}


void	tracing(t_ray *ray, t_light *light, t_obj *sphere, t_cam *camera)
{
	int i;
	int j;
	
	init_elements(light, sphere, camera);
	i = 0;
	while (i < H)
	{
		j = 0;
		while (j < W)
		{
			ray->coord = camera->coord;
			ray->direc.x = j - W / 2;
			ray->direc.y = i - H / 2;
			ray->direc.z = -W / (2 * tan(camera->FOV / 2));
			ray->direc = normalize(ray->direc);

			t_vec p, n;
			double t;
			bool intersect = intersection_sphere(ray, sphere, &p, &n, &t);

			t_vec intensite_pixel_color;
			intensite_pixel_color.x = 0;
			intensite_pixel_color.y = 0;
			intensite_pixel_color.z = 0;
			if (intersect) {
				t_vec pos_light_p = vec_subtract(light->coord, p);
				t_vec n_pos_light_p = normalize(pos_light_p);
				double ps_n_pos_light_p_n = dot_product(n_pos_light_p, n);
				if (ps_n_pos_light_p_n < 0) {
					ps_n_pos_light_p_n = 0;
				}
				double intensite_pixel;
				intensite_pixel = light->ratio * ps_n_pos_light_p_n / norm(pos_light_p);

				intensite_pixel_color = vec_multiply(normalize_color(sphere->color), intensite_pixel);
				intensite_pixel_color.x = (intensite_pixel_color.x > 255) ? 255 : ((intensite_pixel_color.x < 0) ? 0 : intensite_pixel_color.x);
				intensite_pixel_color.y = (intensite_pixel_color.y > 255) ? 255 : ((intensite_pixel_color.y < 0) ? 0 : intensite_pixel_color.y);
				intensite_pixel_color.z = (intensite_pixel_color.z > 255) ? 255 : ((intensite_pixel_color.z < 0) ? 0 : intensite_pixel_color.z);
			}
			image[((H - i - 1) * W + j) * 3 + 0] = (unsigned char)intensite_pixel_color.x;
			image[((H - i - 1) * W + j) * 3 + 1] = (unsigned char)intensite_pixel_color.y;
			image[((H - i - 1) * W + j) * 3 + 2] = (unsigned char)intensite_pixel_color.z;

			j++;
		}
		i++;
	}
	// Affichage de l'image
	i = 0;
	while (i < H) 
	{
		int j = 0;
		while (j < W)
		{
			unsigned int result = (image[(i * W + j) * 3 + 0] << 16) | (image[(i * W + j) * 3 + 1] << 8) | image[(i * W + j) * 3 + 2];
			mlx_pixel_put(mlx_ptr, win_ptr, i, j, result);
			j++;
		}
		i++;
	}
}

void	render_rt(t_minirt *rt)
{
	mlx_put_image_to_window(rt->vars.mlx, rt->vars.win, rt->img.img, 0, 0);
	mlx_key_hook(rt->vars.win, exit_key, &rt->vars);
	mlx_hook(rt->vars.win, 17, 0, end_minirt, &rt->vars);
	mlx_loop(rt->vars.mlx);
}
