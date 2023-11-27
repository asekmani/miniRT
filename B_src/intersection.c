/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:50:30 by asekmani          #+#    #+#             */
/*   Updated: 2023/11/13 18:50:33 by asekmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

bool	find_local_inter(t_ray ray, t_obj *obj, t_inter *local_inter)
{
	if (obj->id == SP)
		return (inter_sphere(ray, *obj, local_inter));
	else if (obj->id == PL)
		return (inter_plan(ray, *obj, local_inter));
	else if (obj->id == CY)
		return (inter_cylindre(ray, *obj, local_inter));
	else if (obj->id == CO)
		return (inter_cone(ray, *obj, local_inter));
	return (false);
}

bool	inter_scene(t_scene scene, t_ray ray, t_inter *inter, t_obj *s)
{
	t_inter	local_inter;
	bool	has_inter;
	bool	local_has_inter;
	double	min_t;

	has_inter = false;
	min_t = DBL_MAX;
	while (scene.obj != NULL)
	{
		local_inter = create_inter();
		local_has_inter = find_local_inter(ray, scene.obj, &local_inter);
		if (local_has_inter)
		{
			has_inter = true;
			if (local_inter.t < min_t)
			{
				min_t = local_inter.t;
				inter->p = local_inter.p;
				inter->n = local_inter.n;
				*s = *scene.obj;
			}
		}
		scene.obj = scene.obj->next;
	}
	return (has_inter);
}

t_vec	specular(t_scene *sc, t_inter inter, t_light *light)
{
	t_vec	l;
	t_vec	v;
	t_vec	r;
	t_vec	hit_light;
	double	spec;

	hit_light = vec_subtract(light->coord, inter.p);
	l = normalize(hit_light);
	v = normalize(vec_subtract(inter.p, sc->camera.coord));
	r = vec_subtract(vec_multiply(inter.n, 2 * dot_product(inter.n, l)), l);
	spec = pow(dot_product(r, v), 50) * light->ratio * 0.5;
	return (vec_multiply(light->color, spec));
}
