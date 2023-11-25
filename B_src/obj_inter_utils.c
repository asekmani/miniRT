/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_inter_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:08:20 by asekmani          #+#    #+#             */
/*   Updated: 2023/11/23 17:08:22 by asekmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_sphere	create_sph(t_ray ray, t_obj sp)
{
	t_sphere	s;

	s.oc = vec_subtract(ray.coord, sp.coord);
	s.a = dot_product(ray.direc, ray.direc);
	s.b = 2.0 * dot_product(s.oc, ray.direc);
	s.c = dot_product(s.oc, s.oc) - (sp.p.x / 2.0) * (sp.p.x / 2.0);
	s.t = s.b * s.b - (4 * s.a * s.c);
	return (s);
}

t_cylinder	create_cyl(t_ray ray, t_obj obj)
{
	t_cylinder	cyl;

	cyl.normal = normalize(obj.orient);
	cyl.oc = vec_subtract(ray.coord, obj.coord);
	cyl.a = dot_product(ray.direc, ray.direc) - (dot_product(ray.direc,
				cyl.normal) * dot_product(ray.direc, cyl.normal));
	cyl.b = 2 * (dot_product(ray.direc, cyl.oc) - (dot_product(ray.direc,
					cyl.normal) * dot_product(cyl.oc, cyl.normal)));
	cyl.c = dot_product(cyl.oc, cyl.oc) - (dot_product(cyl.oc, cyl.normal)
			* dot_product(cyl.oc, cyl.normal)) - (obj.p.x / 2) * (obj.p.x
			/ 2);
	cyl.delta = cyl.b * cyl.b - 4 * cyl.a * cyl.c;
	return (cyl);
}

t_cone	create_cone(t_ray ray, t_obj obj)
{
	t_cone	co;

	co.k = tan((obj.p.z / 2) * PI / 180.0);
	co.v = normalize(obj.orient);
	co.x = vec_subtract(ray.coord, obj.coord);
	co.a = dot_product(ray.direc, ray.direc) - (1 + pow(co.k, 2.0))
		* dot_product(ray.direc, co.v) * dot_product(ray.direc, co.v);
	co.b = 2.0 * (dot_product(ray.direc, co.x) - (1 + pow(co.k, 2.0))
			* dot_product(ray.direc, co.v) * dot_product(co.x, co.v));
	co.c = dot_product(co.x, co.x) - (1 + pow(co.k, 2.0))
		* dot_product(co.x, co.v) * dot_product(co.x, co.v);
	co.delta = co.b * co.b - (4 * co.a * co.c);
	return (co);
}

bool	find_inter_cy(t_cylinder info, t_ray *ray, t_obj *cy, double *t)
{
	info.t1 = (-info.b + sqrt(info.delta)) / (2 * info.a);
	info.t2 = (-info.b - sqrt(info.delta)) / (2 * info.a);
	if (info.t1 < EPS)
		return (false);
	if (info.t1 > info.t2)
		info.t = info.t2;
	else
		info.t = info.t1;
	info.y0 = dot_product(ray->direc, info.normal) * info.t2
		+ dot_product(info.oc, info.normal);
	info.y1 = dot_product(ray->direc, info.normal) * info.t1
		+ dot_product(info.oc, info.normal);
	if (info.y0 >= EPS && info.y0 <= cy->p.y)
	{
		*t = (info.t2);
		return (true);
	}
	if (info.y1 >= EPS && info.y1 <= cy->p.y)
	{
		*t = (info.t1);
		return (true);
	}
	return (false);
}

bool	find_inter_co(t_cone info, t_obj *co, t_ray *ray, double *t)
{
	if (info.delta < 0)
		return (false);
	info.t1 = (-info.b + sqrt(info.delta)) / (2 * info.a);
	info.t2 = (-info.b - sqrt(info.delta)) / (2 * info.a);
	if (info.t1 < EPS)
		return (false);
	if (info.t1 > info.t2)
		info.t = info.t2;
	else if (info.t1 < info.t2)
		info.t = info.t1;
	info.y0 = dot_product(ray->direc, info.v) * info.t2
		+ dot_product(info.x, info.v);
	info.y1 = dot_product(ray->direc, info.v) * info.t1
		+ dot_product(info.x, info.v);
	if (info.y0 >= EPS && info.y0 <= co->p.y)
	{
		*t = (info.t2);
		return (true);
	}
	if (info.y1 >= EPS && info.y1 <= co->p.y)
	{
		*t = (info.t1);
		return (true);
	}
	return (false);
}
