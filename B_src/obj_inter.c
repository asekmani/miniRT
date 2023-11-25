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

bool	inter_plan(t_ray ray, t_obj obj, t_inter *inter)
{
	double	b;
	double	a;
	t_vec	normal;
	t_vec	r_to_obj;

	normal = normalize(obj.orient);
	r_to_obj = vec_subtract(ray.coord, obj.coord);
	b = dot_product(ray.direc, normal);
	if (b != 0)
	{
		a = dot_product(r_to_obj, normal);
		inter->t = -a / b;
		if (inter->t < EPS)
			return (false);
		inter->p = vec_add(ray.coord, vec_multiply(ray.direc, inter->t));
		inter->n = normalize(obj.orient);
		if (dot_product(ray.direc, inter->n) > __DBL_EPSILON__)
			inter->n = normalize(vec_multiply(obj.orient, -1));
		return (true);
	}
	return (false);
}

bool	inter_sphere(t_ray ray, t_obj sp, t_inter *inter)
{
	t_sphere	sph;

	sph = create_sph(ray, sp);
	if (sph.t < EPS)
		return (false);
	sph.t1 = (sph.b * (-1.0) - sqrt(sph.t)) / (2.0 * sph.a);
	sph.t2 = (sph.b * (-1.0) + sqrt(sph.t)) / (2.0 * sph.a);
	if (sph.t1 * sph.t2 > EPS)
	{
		if (sph.t1 < EPS)
			return (false);
		inter->t = take_min(sph.t1, sph.t2);
	}
	if (sph.t1 > EPS)
		inter->t = sph.t1;
	else
		inter->t = sph.t2;
	if (inter->t < EPS)
		return (false);
	inter->p = vec_add(ray.coord, vec_multiply(ray.direc, inter->t));
	inter->n = normalize(vec_subtract(inter->p, sp.coord));
	return (true);
}

bool	inter_cylindre(t_ray ray, t_obj obj, t_inter *inter)
{
	t_cylinder	cy;
	t_vec		oc;
	double		m;

	cy = create_cyl(ray, obj);
	if (cy.delta < EPS)
		return (false);
	if (find_inter_cy(cy, &ray, &obj, &inter->t))
	{
		inter->p = vec_add(ray.coord, vec_multiply(ray.direc, inter->t));
		oc = normalize(obj.orient);
		m = dot_product(ray.direc, vec_multiply(oc, inter->t))
			+ dot_product(vec_subtract(ray.coord, obj.coord), oc);
		inter->n = normalize(vec_subtract(vec_subtract(inter->p, obj.coord),
					vec_multiply(oc, m)));
		return (true);
	}
	return (false);
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

bool	inter_cone(t_ray ray, t_obj obj, t_inter *inter)
{
	t_cone	cone;
	t_vec	n;
	t_vec	vi;
	double	k;
	double	m;

	cone = create_cone(ray, obj);
	k = tan((obj.p.z / 2) * PI / 180.0);
	vi = normalize(obj.orient);
	m = dot_product(ray.direc, vec_multiply(vi, inter->t))
		+ dot_product(vec_subtract(ray.coord, obj.coord), vi);
	if (cone.delta < EPS)
		return (false);
	if (find_inter_co(cone, &obj, &ray, &inter->t))
	{
		inter->p = vec_add(ray.coord, vec_multiply(ray.direc, inter->t));
		n = vec_subtract(vec_subtract(inter->p, obj.coord),
				vec_multiply(vi, ((1 + pow(k, 2.0))) * m));
		inter->n = normalize(n);
		return (true);
	}
	return (false);
}
