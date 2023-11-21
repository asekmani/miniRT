/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_camera.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:40:00 by asekmani          #+#    #+#             */
/*   Updated: 2023/11/21 14:40:03 by asekmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	set_camera_scene(t_minirt *rt)
{
	t_vec	correction;

	rt->scene->camera.FOV = rt->scene->camera.FOV * PI / 180;
	rt->scene->camera.tan = tan(rt->scene->camera.FOV / 2);
	rt->scene->camera.aspect = (double)W / (double)H;
	rt->scene->camera.forward = create_vectorv(rt->scene->camera.orient.x,
			rt->scene->camera.orient.y, rt->scene->camera.orient.z);
	rt->scene->camera.forward.x += EPS;
	correction = create_vectorv(0.0, 1.0, 0.0);
	rt->scene->camera.up = normalize(vect_cross(rt->scene->camera.forward,
				correction));
	rt->scene->camera.right = normalize(vect_cross(rt->scene->camera.forward,
				rt->scene->camera.up));
}

t_ray	create_ray_cam(t_minirt *rt, double i, double j)
{
	t_ray	result;

	result.coord = rt->scene->camera.coord;
	result.direc = vec_add(vec_add(vec_multiply(rt->scene->camera.up, i
					* rt->scene->camera.tan),
				vec_multiply(rt->scene->camera.right, j * rt->scene->camera.tan
					* rt->scene->camera.aspect)), rt->scene->camera.forward);
	result.direc = normalize(result.direc);
	return (result);
}
