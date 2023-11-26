/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:07:26 by asekmani          #+#    #+#             */
/*   Updated: 2023/11/21 16:07:29 by asekmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int create_rgb(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

void color_adjust(t_vec *col_res)
{
	if (col_res->x > 255)
		col_res->x = 255;
	else if (col_res->x < 0)
		col_res->x = 0;
	if (col_res->y > 255)
		col_res->y = 255;
	else if (col_res->y < 0)
		col_res->y = 0;
	if (col_res->z > 255)
		col_res->z = 255;
	else if (col_res->z < 0)
		col_res->z = 0;
}

t_vec diffuse(t_obj obj_int, t_light *light, double d)
{
	t_vec diff;

	diff = calcul_coef_color(obj_int.color, light->color, d * light->ratio);
	return (diff);
}

t_vec specular(t_scene *sc, t_inter inter, t_light *light)
{
	t_vec	l;
	t_vec	v;
	t_vec	r;
	double	spec;
	t_vec	hit_light;

	hit_light = vec_subtract(light->coord, inter.p);
	l = normalize(hit_light);
	v = normalize(vec_subtract(inter.p, sc->camera.coord));
	r = vec_subtract(vec_multiply(inter.n, 2 * dot_product(inter.n, l)), l);
	spec = pow(dot_product(r, v), 50) * light->ratio * 0.5;
	return (vec_multiply(light->color, spec));
}

t_vec calcul_light_color(t_scene *sc, t_inter inter, t_obj obj_int, t_vec amb)
{
	t_light *light;
	t_vec ret;
	t_vec hit_light;
	double d;

	ret = create_vectorv(0, 0, 0);
	
	if (!sc->light)
		return (amb);
	light = sc->light;
	
	while (light)
	{
		if (shade(sc, inter, light))
			ret = add_color(ret, amb);
		else
		{
			hit_light = vec_subtract(light->coord, inter.p);
			d = dot_product(normalize(hit_light), inter.n);
			ret = add_color(ret, amb);
			if (d > 0)
				ret = add_color(add_color(ret, diffuse(obj_int, light, d)), specular(sc, inter, light));
				
			
		}
		light = light->next;
	}
	return (ret);
}



t_vec calcul_color(t_scene sc, t_ray ray)
{
	t_inter local_inter;
	t_obj inter;
	t_vec base_color;
	t_vec px_col;

	local_inter = create_inter();
	if (inter_scene(sc, ray, &local_inter, &inter))
	{
		base_color = calcul_coef_color(inter.color, sc.ambient.color,
									   sc.ambient.ratio);
		if (dot_product(ray.direc, local_inter.n) > 0)
			local_inter.n = vec_multiply(local_inter.n, -1);
		px_col = calcul_light_color(&sc, local_inter, inter, base_color);
		return (px_col);
	}
	return (vec_multiply(sc.ambient.color, sc.ambient.ratio));
}
