/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:12:25 by asekmani          #+#    #+#             */
/*   Updated: 2023/10/31 15:12:31 by asekmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void ambient_parse(t_minirt *rt, char **arv)
{
	if (!arv || !arv[1] || !arv[2] || arv[3])
		error_msg("invalid args for Ambient Light!");
	if (rt->scene->ambient.counter != 0)
		error_msg("Error : no more than one Ambient Light");
	rt->scene->ambient.counter++;
	rt->scene->ambient.ratio = ft_atod(arv[1]);
	if (rt->scene->ambient.ratio < 0 || rt->scene->ambient.ratio > 1)
		error_msg("Error : Ambient Light must be in range [0.0,1.0]");
	rt->scene->ambient.color = color_parse(arv[2]);
}

void set_camera_scene(t_minirt *rt)
{
	rt->scene->camera.FOV = rt->scene->camera.FOV * PI / 180;
	rt->scene->camera.tan = tan(rt->scene->camera.FOV / 2);
	rt->scene->camera.aspect = (double)W / (double)H;
	rt->scene->camera.forward = create_vectorv(rt->scene->camera.orient.x, rt->scene->camera.orient.y, rt->scene->camera.orient.z);
	rt->scene->camera.forward.x += EPS;
	t_vec correction = create_vectorv(0.0, 1.0, 0.0);
	rt->scene->camera.up = normalize(vect_cross(rt->scene->camera.forward, correction));
	rt->scene->camera.right = normalize(vect_cross(rt->scene->camera.forward, rt->scene->camera.up));
}

t_ray create_ray_cam(t_minirt *rt, double i, double j)
{
	t_ray result;

	result.coord = rt->scene->camera.coord;

	result.direc = vec_add(vec_add(vec_multiply(rt->scene->camera.up, i * rt->scene->camera.tan),
								   vec_multiply(rt->scene->camera.right, j * rt->scene->camera.tan * rt->scene->camera.aspect)),
						   rt->scene->camera.forward);
	result.direc = normalize(result.direc);
	return result;
}

void camera_parse(t_minirt *rt, char **arv)
{
	if (!arv || !arv[1] || !arv[2] || !arv[3] || arv[4])
		error_msg("invalid args for camera !");
	if (rt->scene->camera.counter != 0)
		error_msg("Error : no more than one camera");
	rt->scene->camera.counter++;
	rt->scene->camera.coord = vectors_parse(arv[1]);
	rt->scene->camera.orient = vectors_parse(arv[2]);

	if (rt->scene->camera.orient.x > 1 || rt->scene->camera.orient.y > 1 || rt->scene->camera.orient.z > 1)
		error_msg("Error : invalid camera orientation!");
	if (rt->scene->camera.orient.x < -1 || rt->scene->camera.orient.y < -1 || rt->scene->camera.orient.z < -1)
		error_msg("Error : invalid camera orientation!");
	if (rt->scene->camera.orient.x == 0 && rt->scene->camera.orient.y == 0 && rt->scene->camera.orient.z == 0)
		error_msg("Error : invalid camera orientation!");
	rt->scene->camera.FOV = ft_atod(arv[3]);
	if (rt->scene->camera.FOV < 0 || rt->scene->camera.FOV > 180)
		error_msg("Error : FOV must be in range [0,180]");
	set_camera_scene(rt);
}

void light_parse(t_minirt *rt, char **arv)
{
	t_light *light;

	if (!arv || !arv[1] || !arv[2] || !arv[3] || arv[4])
		error_msg("Error : invalid light !");
	light = init_light(rt);
	light->coord = vectors_parse(arv[1]);
	light->ratio = ft_atod(arv[2]);
	if (light->ratio < 0 || light->ratio > 1)
		error_msg("Error : ratio must be in range [0.0,1.0]");
	light->color = color_parse(arv[3]);
}