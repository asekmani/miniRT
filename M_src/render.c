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

int	shade(t_scene *sc,  t_inter inter, t_light *light)
{
	t_vec		hit_light;
	t_ray	sh_ray;
	t_inter		shadow;
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

void tracing(t_minirt *rt)
{
	double x;
	double y;
	int color;
	int i;
	int j;

	i = H - 1;
	while (i >= 0)
	{
		j = 0;
		while (j < W)
		{
			x = (double)j * 2 / W - 1;
			y = (double)i * 2 / H - 1;
			rt->ray = create_ray_cam(rt, x, y);
			rt->vec = calcul_color(*rt->scene, rt->ray);
			color = create_rgb(rt->vec.x, rt->vec.y, rt->vec.z);
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
