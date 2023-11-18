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

void color_adjust(t_vec *col_res)
{
	col_res->x = pow(col_res->x, 1 / 2.2);
	col_res->y = pow(col_res->y, 1 / 2.2);
	col_res->z = pow(col_res->z, 1 / 2.2);
	col_res->x = (col_res->x > 255) ? 255 : ((col_res->x < 0) ? 0 : col_res->x);
	col_res->y = (col_res->y > 255) ? 255 : ((col_res->y < 0) ? 0 : col_res->y);
	col_res->z = (col_res->z > 255) ? 255 : ((col_res->z < 0) ? 0 : col_res->z);
}
t_vec calcul_color(t_scene sc, t_ray ray)
{
	t_color_calculator cc;
	t_vec nc;
	
	cc = init_color_calculator();
	cc.inter = inter_scene(sc, ray, &cc.p, &cc.n, &cc.inter_obj);
	if (cc.inter)
	{
		cc.coord_light = vec_subtract(sc.light->coord, cc.p);
		cc.norm_light = normalize(cc.coord_light);
		cc.pos_light.coord = vec_add(cc.p, vec_multiply(cc.n, 0.01));
		cc.pos_light.direc = cc.norm_light;
		cc.inter_light = inter_scene_ray(sc, cc.pos_light, &cc.dis);
		if (!cc.inter_light || cc.dis * cc.dis >= norm(cc.coord_light))
		{
			if (dot_product(cc.norm_light, cc.n) > 0)
				cc.pixel = sc.light->ratio * dot_product(cc.norm_light, cc.n);
				cc.pixel /= norm(cc.coord_light);
				nc = norm_color(cc.inter_obj.color);
			cc.color_result = vec_multiply(nc, cc.pixel);
			color_adjust(&cc.color_result);
		}
	}
	return cc.color_result;
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
