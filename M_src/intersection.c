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

bool pick_cy_inter(t_cylinder inf, t_ray *ray, t_obj *cy, double *t)
{
    inf.t1 = (-inf.b + sqrt(inf.delta)) / (2 * inf.a);
    inf.t2 = (-inf.b - sqrt(inf.delta)) / (2 * inf.a);
    if (inf.t1 < EPS)
        return false;
    if (inf.t1 > inf.t2)
        inf.t = inf.t2;
    else
        inf.t = inf.t1;
    inf.y0 = dot_product(ray->direc, inf.normal) * inf.t2 + dot_product(inf.oc, inf.normal);
    inf.y1 = dot_product(ray->direc, inf.normal) * inf.t1 + dot_product(inf.oc, inf.normal);
    if (inf.y0 >= EPS && inf.y0 <= cy->p.y)
    {
        *t = (inf.t2);
        return true;
    }
    if (inf.y1 >= EPS && inf.y1 <= cy->p.y)
    {
        *t = (inf.t1);
        return true;
    }

    return false;
}

bool inter_cylindre(t_ray ray, t_obj obj, t_intersection *inter)
{
    t_cylinder inf;
    t_vec oc;
    double m;
    inf.normal = normalize(obj.orient);
    inf.oc = vec_subtract(ray.coord, obj.coord);
    inf.a = dot_product(ray.direc, ray.direc) - (dot_product(ray.direc, inf.normal) * dot_product(ray.direc, inf.normal));
    inf.b = 2 * (dot_product(ray.direc, inf.oc) - (dot_product(ray.direc, inf.normal) * dot_product(inf.oc, inf.normal)));
    inf.c = dot_product(inf.oc, inf.oc) - (dot_product(inf.oc, inf.normal) * dot_product(inf.oc, inf.normal)) - (obj.p.x / 2) * (obj.p.x / 2);
    inf.delta = inf.b * inf.b - 4 * inf.a * inf.c;
    if (inf.delta < EPS)
        return false;
    if (pick_cy_inter(inf, &ray, &obj, &inter->t))
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

bool inter_plan(t_ray ray, t_obj obj, t_intersection *inter)
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

double	take_min(double x, double y)
{
	if (x > y)
		return (y);
	return (x);
}
bool inter_sphere(t_ray ray, t_obj sp, t_intersection *inter)
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
    if(inter->t < EPS){
        return false;
    }
	inter->p = vec_add(ray.coord, vec_multiply(ray.direc, inter->t));
	inter->n = normalize(vec_subtract(inter->p, sp.coord));	
	return true;

   
}


bool inter_scene(t_scene scene,t_ray ray, t_intersection *inter, t_obj *s)
{
    t_obj *obj;
    obj = scene.obj;
    bool has_intersect;
    has_intersect = false;
    double min_t = DBL_MAX;
    while (obj != NULL)
    {
       t_intersection local_inter = create_int();
        bool local_has_intersect;
        if (obj->id == SP)
            local_has_intersect = inter_sphere(ray, *obj, &local_inter);
        if (obj->id == PL)
            local_has_intersect = inter_plan(ray, *obj, &local_inter);
        if (obj->id == CY)
            local_has_intersect = inter_cylindre(ray, *obj, &local_inter);
        if (local_has_intersect)
        {
            has_intersect = true;
            if (local_inter.t < min_t)
            {
                min_t = local_inter.t;
                inter->p = local_inter.p;
                inter->n = local_inter.n;
                *s = *obj;
            }
        }
        obj = obj->next;
    }
    return has_intersect;
}

bool inter_scene_ray(t_scene scene, t_ray ray, double *t)
{
    t_obj *sphere;
    sphere = scene.obj;
    bool has_intersect;
    has_intersect = false;
    double min_t = DBL_MAX;
    t_intersection local_inter;
    while (sphere != NULL)
    {
        local_inter = create_int();
        bool local_has_intersect;
        local_has_intersect = inter_sphere(ray, *sphere, &local_inter);
        if (local_has_intersect)
        {
            has_intersect = true;
            if (local_inter.t < min_t)
            {
                min_t = local_inter.t;
            }
        }
        sphere = sphere->next;
    }
    *t = min_t;
    return has_intersect;
}
