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

bool inter_cylindre(t_ray ray, t_obj obj, t_vec *p, t_vec *n, double *t)
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
    if (pick_cy_inter(inf, &ray, &obj, t))
    {
        *p = vec_add(ray.coord, vec_multiply(ray.direc, *t));
        oc = normalize(obj.orient);
        m = dot_product(ray.direc, vec_multiply(oc, *t)) + dot_product(vec_subtract(ray.coord, obj.coord), oc);
        *n = normalize(vec_subtract(vec_subtract(*p, obj.coord),
                                    vec_multiply(oc, m)));
        return true;
    }
    return false;
}

bool inter_plan(t_ray ray, t_obj obj, t_vec *p, t_vec *n, double *t)
{

    double b;
    double a;

    t_vec normal = normalize(obj.orient);
    t_vec r_to_obj = vec_subtract(ray.coord, obj.coord);
    b = dot_product(ray.direc, normal);
    if (b != 0)
    {
        a = dot_product(r_to_obj, normal);
        *t = -a / b;
        if (*t < EPS)
            return false;
        *p = vec_add(ray.coord, vec_multiply(ray.direc, *t));
        *n = normalize(obj.orient);
        if (dot_product(ray.direc, obj.orient) < EPS)
            *n = normalize(vec_multiply(obj.orient, -1));
        return true;
    }
    return false;
}
bool inter_sphere(t_ray ray, t_obj sp, t_vec *p, t_vec *n, double *t)
{

    double a = 1;
    double b = 2 * dot_product(ray.direc, vec_subtract(ray.coord, sp.coord));
    double c = norm(vec_subtract(ray.coord, sp.coord)) - sp.p.x * sp.p.x;
    double delta = b * b - 4 * a * c;
    if (delta < 0)
        return false;
    double t1 = (-b - sqrt(delta)) / (2 * a);
    double t2 = (-b + sqrt(delta)) / (2 * a);
    if (t2 < 0)
        return false;
    if (t1 > 0)
        *t = t1;
    else
        *t = t2;
    *p = vec_add(ray.coord, vec_multiply(ray.direc, *t));
    *n = normalize(vec_subtract(*p, sp.coord));

    return true;
}

bool inter_scene(t_scene scene, t_ray ray, t_vec *p, t_vec *n, t_obj *s)
{
    t_obj *sphere;
    sphere = scene.obj;
    bool has_intersect;
    has_intersect = false;
    double min_t = DBL_MAX;
    while (sphere != NULL)
    {
        t_vec local_p;
        t_vec local_n;
        bool local_has_intersect;
        double local_t;
        if (sphere->id == SP)
            local_has_intersect = inter_sphere(ray, *sphere, &local_p, &local_n, &local_t);
        if (sphere->id == PL)
            local_has_intersect = inter_plan(ray, *sphere, &local_p, &local_n, &local_t);
        if (sphere->id == CY)
            local_has_intersect = inter_cylindre(ray, *sphere, &local_p, &local_n, &local_t);
        if (local_has_intersect)
        {
            has_intersect = true;
            if (local_t < min_t)
            {
                min_t = local_t;
                *p = local_p;
                *n = local_n;
                *s = *sphere;
            }
        }
        sphere = sphere->next;
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
    while (sphere != NULL)
    {
        t_vec local_p;
        t_vec local_n;
        bool local_has_intersect;
        double local_t;
        local_has_intersect = inter_sphere(ray, *sphere, &local_p, &local_n, &local_t);
        if (local_has_intersect)
        {
            has_intersect = true;
            if (local_t < min_t)
            {
                min_t = local_t;
            }
        }
        sphere = sphere->next;
    }
    *t = min_t;
    return has_intersect;
}
