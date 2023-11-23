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

double	take_min(double x, double y)
{
	if (x > y)
		return (y);
	return (x);
}

bool find_inter_cy(t_cylinder info, t_ray *ray, t_obj *cy, double *t)
{
    info.t1 = (-info.b + sqrt(info.delta)) / (2 * info.a);
    info.t2 = (-info.b - sqrt(info.delta)) / (2 * info.a);
    if (info.t1 < EPS)
        return false;
    if (info.t1 > info.t2)
        info.t = info.t2;
    else
        info.t = info.t1;
    info.y0 = dot_product(ray->direc, info.normal) * info.t2 + dot_product(info.oc, info.normal);
    info.y1 = dot_product(ray->direc, info.normal) * info.t1 + dot_product(info.oc, info.normal);
    if (info.y0 >= EPS && info.y0 <= cy->p.y)
    {
        *t = (info.t2);
        return true;
    }
    if (info.y1 >= EPS && info.y1 <= cy->p.y)
    {
        *t = (info.t1);
        return true;
    }
    return false;
}

// double	find_inter_co(t_obj *co, t_ray *ray, t_cone info)
// {
// 	if (info.delta < 0)
// 		return (-1.0);
// 	info.t1 = (-info.b + sqrt(info.delta)) / (2 * info.a);
// 	info.t2 = (-info.b - sqrt(info.delta)) / (2 * info.a);
// 	if (info.t1 < EPS)
// 		return (-1.0);
// 	if (info.t1 > info.t2)
// 		info.t = info.t2;
// 	else if (info.t1 < info.t2)
// 		info.t = info.t1;
// 	info.y0 = dot_product(ray->direc, info.v) * info.t2
// 		+ dot_product(info.x, info.v);
// 	info.y1 = dot_product(ray->direc, info.v) * info.t1
// 		+ dot_product(info.x, info.v);
// 	if (info.y0 >= EPS && info.y0 <= co->p.y)
// 		return (info.t2);
// 	if (info.y1 >= EPS && info.y1 <= co->p.y)
// 		return (info.t1);
// 	return (-1.0);
// }
