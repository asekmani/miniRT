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

void color_adjust(t_vec *color_result)
{
	color_result->x = pow(color_result->x, 1 / 2.2);
	color_result->y = pow(color_result->y, 1 / 2.2);
	color_result->z = pow(color_result->z, 1 / 2.2);
	color_result->x = (color_result->x > 255) ? 255 : ((color_result->x < 0) ? 0 : color_result->x);
	color_result->y = (color_result->y > 255) ? 255 : ((color_result->y < 0) ? 0 : color_result->y);
	color_result->z = (color_result->z > 255) ? 255 : ((color_result->z < 0) ? 0 : color_result->z);
}
t_vec calcul_color(t_scene scene, t_ray ray)
{
	t_color_calculator color_calculator;
	color_calculator = init_color_calculator();
	color_calculator.inter = inter_scene(scene, ray, &color_calculator.p, &color_calculator.n, &color_calculator.inter_obj);
	if (color_calculator.inter)
	{
		color_calculator.coord_light = vec_subtract(scene.light->coord, color_calculator.p);
		color_calculator.norm_light = normalize(color_calculator.coord_light);
		// créer un rayon d'origin position p qui est la plus proche intersection et de direction vers la lumiere
		color_calculator.pos_light.coord = vec_add(color_calculator.p, vec_multiply(color_calculator.n, 0.01));
		color_calculator.pos_light.direc = color_calculator.norm_light;
		color_calculator.inter_light = inter_scene_ray(scene, color_calculator.pos_light, &color_calculator.dis);
		if (!color_calculator.inter_light || color_calculator.dis * color_calculator.dis >= norm(color_calculator.coord_light))
		{
			if (dot_product(color_calculator.norm_light, color_calculator.n) > 0)
				color_calculator.pixel = scene.light->ratio * dot_product(color_calculator.norm_light, color_calculator.n) / norm(color_calculator.coord_light);
			color_calculator.color_result = vec_multiply(normalize_color(color_calculator.inter_obj.color), color_calculator.pixel);
			color_adjust(&color_calculator.color_result);
		}
	}
	return color_calculator.color_result;
}

void tracing(t_minirt *rt)
{
	t_scene scene;
	t_ray ray;
	t_vec px_color;
	int color;
	int i;
	int j;

	scene = create_scene();
	i = 0;
	while (i < H)
	{
		j = 0;
		while (j < W)
		{
			// creation de rayon: l'origine de rayon est la position de camera, direction est le pixel courant
			ray.coord = scene.camera.coord;
			ray.direc.x = j - W / 2;
			ray.direc.y = i - H / 2;
			ray.direc.z = -W / (2 * tan(scene.camera.FOV / 2));
			ray.direc = normalize(ray.direc);
			px_color = calcul_color(scene, ray);
			color = create_rgb(px_color.x, px_color.y, px_color.z);
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
