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
	// col_res->x = pow(col_res->x, 1 / 2.2);
	// col_res->y = pow(col_res->y, 1 / 2.2);
	// col_res->z = pow(col_res->z, 1 / 2.2);
	col_res->x = (col_res->x > 255) ? 255 : ((col_res->x < 0) ? 0 : col_res->x);
	col_res->y = (col_res->y > 255) ? 255 : ((col_res->y < 0) ? 0 : col_res->y);
	col_res->z = (col_res->z > 255) ? 255 : ((col_res->z < 0) ? 0 : col_res->z);
}
int	shade(t_scene *sc,  t_intersection inter, t_light *light)
{
	t_vec		hit_light;
	t_ray	sh_ray;
	t_intersection		shadow;
	t_vec		hit_sh;
	t_obj local_inter;

	hit_light = vec_subtract(light->coord, inter.p);
	sh_ray.coord = inter.p;
	sh_ray.direc = normalize(hit_light);
	shadow.t = -1;
	bool inters = inter_scene(*sc, sh_ray, &shadow, &local_inter);
	hit_sh = vec_subtract(shadow.p, sh_ray.coord);
	if (inters && (module_v(hit_light) > module_v(hit_sh)))
		return (1);
	return (0);
}

t_vec	diffuse(t_obj obj_int, t_light *light, double d)
{
	t_vec	diff;

	diff = calcul_coef_color(obj_int.color, light->color, d * light->ratio);
	return (diff);
}
t_vec	calcul_light_color(t_scene *sc, t_intersection inter,t_obj obj_int, t_vec amb)
{
	t_light		*light;
	t_vec		ret;
	t_vec		hit_light;
	double		d;

	ret = create_vectorv(0, 0, 0);
	light = sc->light;
	if (!light)
		return (amb);
	if (shade(sc, inter, light))
		ret = add_color(ret, amb);
	else
	{
		hit_light = vec_subtract(light->coord, inter.p);
		d = dot_product(normalize(hit_light), inter.n);
		ret = add_color(ret, amb);
		if (d > 0)
			ret = add_color(ret, diffuse(obj_int, light, d));
	}
	return (ret);
}

t_vec	calcul_color(t_scene sc, t_ray ray)
{
	t_intersection local_inter = create_int();
	t_obj inter;
	t_vec base_color;
	t_vec	px_col;
	if (inter_scene(sc, ray, &local_inter, &inter))
	{
		base_color = calcul_coef_color(inter.color, sc.ambient.color, sc.ambient.ratio);
		if(dot_product(ray.direc, local_inter.n) > 0)
			local_inter.n = vec_multiply(local_inter.n, -1);
		 px_col = calcul_light_color(&sc, local_inter, inter, base_color);
		return (px_col);
	}
	return (vec_multiply(sc.ambient.color, sc.ambient.ratio));
}

void tracing(t_minirt *rt)
{

	t_ray ray;
	t_vec px_color;
	int color;
	int i;
	int j;

	i = H - 1;

	while (i >= 0)
	{
		j = 0;
		while (j < W)
		{
			double x = (double)j * 2 / W - 1;
			double y = (double)i * 2 / H - 1;
			ray = create_ray_cam(rt, x, y);
			px_color = calcul_color(*rt->scene, ray);
			color = create_rgb(px_color.x, px_color.y, px_color.z);
			img_pixel_put(&rt->img, j, H - 1 - i, color);
			j++;
		}
		i--;
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
