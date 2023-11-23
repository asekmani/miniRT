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

bool inter_scene(t_scene scene,t_ray ray, t_inter *inter, t_obj *s)
{
    t_obj *obj;
    t_inter local_inter;
    bool has_inter;
    bool local_has_inter;
    double min_t;

    has_inter = false;
    min_t = DBL_MAX;
    obj = scene.obj;
    while (obj != NULL)
    {
        local_inter = create_inter();
        if (obj->id == SP)
            local_has_inter = inter_sphere(ray, *obj, &local_inter);
        if (obj->id == PL)
            local_has_inter = inter_plan(ray, *obj, &local_inter);
        if (obj->id == CY)
            local_has_inter = inter_cylindre(ray, *obj, &local_inter);
        // if (obj->id == CO)
        //     local_has_inter = inter_cone(ray, *obj, &local_inter);
        if (local_has_inter)
        {
            has_inter = true;
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
    return has_inter;
}

// bool inter_scene_ray(t_scene scene, t_ray ray, double *t)
// {
//     t_obj *sphere;
//     t_inter local_inter;
//     double min_t;
//     bool has_inter;
//     bool local_has_inter;

//     min_t = DBL_MAX;
//     has_inter = false;
//     sphere = scene.obj;
//     while (sphere != NULL)
//     {
//         local_inter = create_inter();
//         local_has_inter = inter_sphere(ray, *sphere, &local_inter);
//         if (local_has_inter)
//         {
//             has_inter = true;
//             if (local_inter.t < min_t)
//                 min_t = local_inter.t;
//         }
//         sphere = sphere->next;
//     }
//     *t = min_t;
//     return (has_inter);
// }
