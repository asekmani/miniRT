/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_inter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:05:12 by asekmani          #+#    #+#             */
/*   Updated: 2023/11/23 17:05:14 by asekmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

bool inter_plan(t_ray ray, t_obj obj, t_inter *inter)
{
    double b;
    double a;

    t_vec normal = normalize(obj.orient);
    t_vec r_to_obj = vec_subtract(ray.coord, obj.coord);
    b = dot_product(ray.direc, normal);
    if (b != 0)
    {
        a = dot_product(r_to_obj, normal);
        inter->t = -a / b;
        if (inter->t < EPS)
            return false;
        inter->p = vec_add(ray.coord, vec_multiply(ray.direc, inter->t));
        inter->n = normalize(obj.orient);
        if (dot_product(ray.direc, inter->n) > __DBL_EPSILON__)
            inter->n = normalize(vec_multiply(obj.orient, -1));
        return true;
    }
    return false;
}

bool inter_sphere(t_ray ray, t_obj sp, t_inter *inter)
{
   t_sphere	sph;

	sph.oc = vec_subtract(ray.coord, sp.coord);
	sph.a = dot_product(ray.direc, ray.direc);
	sph.b = 2.0 * dot_product(sph.oc, ray.direc);
	sph.c = dot_product(sph.oc, sph.oc) - (sp.p.x / 2.0) * (sp.p.x / 2.0);
	sph.t = sph.b * sph.b - (4 * sph.a * sph.c);
	if (sph.t < EPS)
		return false;
	sph.t1 = (sph.b * (-1.0) - sqrt(sph.t)) / (2.0 * sph.a);
	sph.t2 = (sph.b * (-1.0) + sqrt(sph.t)) / (2.0 * sph.a);
	if (sph.t1 * sph.t2 > EPS)
	{
		if (sph.t1 < EPS)
         return false;
        inter->t = take_min(sph.t1, sph.t2);
	}
	if (sph.t1 > EPS)
        inter->t = sph.t1;
    else
        inter->t = sph.t2;
    if (inter->t < EPS)
        return false;
    inter->p = vec_add(ray.coord, vec_multiply(ray.direc, inter->t));
	inter->n = normalize(vec_subtract(inter->p, sp.coord));	
	return true; 
}

bool inter_cylindre(t_ray ray, t_obj obj, t_inter *inter)
{
    t_cylinder info;
    t_vec oc;
    double m;
    info.normal = normalize(obj.orient);
    info.oc = vec_subtract(ray.coord, obj.coord);
    info.a = dot_product(ray.direc, ray.direc) - (dot_product(ray.direc, info.normal) * dot_product(ray.direc, info.normal));
    info.b = 2 * (dot_product(ray.direc, info.oc) - (dot_product(ray.direc, info.normal) * dot_product(info.oc, info.normal)));
    info.c = dot_product(info.oc, info.oc) - (dot_product(info.oc, info.normal) * dot_product(info.oc, info.normal)) - (obj.p.x / 2) * (obj.p.x / 2);
    info.delta = info.b * info.b - 4 * info.a * info.c;
    if (info.delta < EPS)
        return false;
    if (find_inter_cy(info, &ray, &obj, &inter->t))
    {
        inter->p = vec_add(ray.coord, vec_multiply(ray.direc, inter->t));
        oc = normalize(obj.orient);
        m = dot_product(ray.direc, vec_multiply(oc, inter->t)) + dot_product(vec_subtract(ray.coord, obj.coord), oc);
        inter->n = normalize(vec_subtract(vec_subtract(inter->p, obj.coord),
                                    vec_multiply(oc, m)));
        return true;
    }
    return false;
}

// double	inter_cone(t_ray *ray, t_obj *co)
// {
// 	t_cone	info;
// 	double		t;

// 	info.k = tan((co->p.z / 2) * PI / 180.0);
// 	info.v = normalize(co->orient);
// 	info.x = vec_subtract(ray->coord, co->coord);
// 	info.a = dot_product(ray->direc, ray->direc) - (1 + pow(info.k, 2.0))
// 		* dot_product(ray->direc, info.v) * dot_product(ray->direc, info.v);
// 	info.b = 2.0 * (dot_product(ray->direc, info.x) - (1 + pow(info.k, 2.0))
// 			* dot_product(ray->direc, info.v) * dot_product(info.x, info.v));
// 	info.c = dot_product(info.x, info.x) - (1 + pow(info.k, 2.0))
// 		* dot_product(info.x, info.v) * dot_product(info.x, info.v);
// 	info.delta = info.b * info.b - (4 * info.a * info.c);
// 	t = find_inter_co(co, ray, info);
// 	return (t);
// }
