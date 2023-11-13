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
        local_has_intersect = inter_sphere(ray, *sphere, &local_p, &local_n, &local_t);
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
