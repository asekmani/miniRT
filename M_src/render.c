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
void img_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int create_rgb(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

void tracing(t_minirt *rt)
{
	t_scene scene;
	scene = create_scene();
	int i;
	int j;
	i = 0;
	while (i < H)
	{
		j = 0;
		while (j < W)
		{
			// creation de rayon: l'origine de rayon est la position de camera, direction est le pixel courant
			t_ray ray;
			ray.coord = scene.camera.coord;
			ray.direc.x = j - W / 2;
			ray.direc.y = i - H / 2;
			ray.direc.z = -W / (2 * tan(scene.camera.FOV / 2));
			ray.direc = normalize(ray.direc);
			t_vec p;			 // point d'intersection de rayon avec l'objet
			t_vec n;			 // normal
			t_obj intersect_obj; // l'objet le plus proche qui intersecte avec le rayon

			bool intersect = inter_scene(scene, ray, &p, &n, &intersect_obj);

			t_vec int_px_color;
			int_px_color.x = 0;
			int_px_color.y = 0;
			int_px_color.z = 0;
			if (intersect)
			{
				t_vec pos_light_p = vec_subtract(scene.light->coord, p);
				t_vec n_pos_light_p = normalize(pos_light_p);
				// créer un rayon d'origin position p qui est la plus proche intersection et de direction vers la lumiere
				t_ray r_p_to_position_light;
				// video 2 10m:20
				r_p_to_position_light.coord = vec_add(p, vec_multiply(n, 0.01));
				r_p_to_position_light.direc = n_pos_light_p;
				bool has_intersect_light;
				double distance_vers_intersection;
				has_intersect_light = inter_scene_ray(scene, r_p_to_position_light, &distance_vers_intersection);
				if (has_intersect_light && distance_vers_intersection * distance_vers_intersection < norm(pos_light_p))
				{
					int_px_color.x = 0;
					int_px_color.y = 0;
					int_px_color.z = 0;
				}
				else
				{
					double ps_n_pos_light_p_n = dot_product(n_pos_light_p, n);
					if (ps_n_pos_light_p_n < 0)
					{
						ps_n_pos_light_p_n = 0;
					}
					double intensite_pixel;
					intensite_pixel = scene.light->ratio * ps_n_pos_light_p_n / norm(pos_light_p);

					int_px_color = vec_multiply(normalize_color(intersect_obj.color), intensite_pixel);
					int_px_color.x = pow(int_px_color.x, 1 / 2.2);
					int_px_color.y = pow(int_px_color.y, 1 / 2.2);
					int_px_color.z = pow(int_px_color.z, 1 / 2.2);
					int_px_color.x = (int_px_color.x > 255) ? 255 : ((int_px_color.x < 0) ? 0 : int_px_color.x);
					int_px_color.y = (int_px_color.y > 255) ? 255 : ((int_px_color.y < 0) ? 0 : int_px_color.y);
					int_px_color.z = (int_px_color.z > 255) ? 255 : ((int_px_color.z < 0) ? 0 : int_px_color.z);
				}
			}
			int color = create_rgb(int_px_color.x, int_px_color.y, int_px_color.z);
			img_pixel_put(&rt->img, j, H - i - 1, color);
			j++;
		}
		i++;
	}
}

void render_rt(t_minirt *rt)
{
    tracing(rt);
	mlx_put_image_to_window(rt->vars.mlx, rt->vars.win, rt->img.img, 0, 0);
	mlx_key_hook(rt->vars.win, exit_key, &rt->vars);
	mlx_hook(rt->vars.win, 17, 0, end_minirt, &rt->vars);
	mlx_loop(rt->vars.mlx);
}
