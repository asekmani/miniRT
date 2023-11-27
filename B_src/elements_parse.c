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

void	ambient_parse(t_minirt *rt, char **arv)
{
	if (!arv || !arv[1] || !arv[2] || arv[3])
		error_msg("invalid args for Ambient Light!");
	if (rt->scene->ambient.counter != 0)
		error_msg("no more than one Ambient Light");
	rt->scene->ambient.counter++;
	rt->scene->ambient.ratio = ft_atod(arv[1]);
	if (rt->scene->ambient.ratio < 0 || rt->scene->ambient.ratio > 1)
		error_msg("Ambient Light must be in range [0.0,1.0]");
	rt->scene->ambient.color = color_parse(arv[2]);
}

void	light_parse(t_minirt *rt, char **arv)
{
	t_light	*light;

	if (!arv || !arv[1] || !arv[2] || !arv[3] || arv[4])
		error_msg("invalid light !");
	light = init_light(rt);
	light->coord = vectors_parse(arv[1]);
	light->ratio = ft_atod(arv[2]);
	if (light->ratio < 0 || light->ratio > 1)
		error_msg("ratio must be in range [0.0,1.0]");
	light->color = color_parse(arv[3]);
}

void	camera_parse(t_minirt *rt, char **arv)
{
	if ((!arv) || (!arv[1]) || (!arv[2]) || (!arv[3]) || (arv[4]))
		error_msg("invalid args for camera !");
	if (rt->scene->camera.counter != 0)
		error_msg("no more than one camera");
	rt->scene->camera.counter++;
	rt->scene->camera.coord = vectors_parse(arv[1]);
	rt->scene->camera.orient = vectors_parse(arv[2]);
	if (rt->scene->camera.orient.x > 1 || rt->scene->camera.orient.y > 1
		|| rt->scene->camera.orient.z > 1)
		error_msg("invalid camera orientation!");
	if (rt->scene->camera.orient.x < -1 || rt->scene->camera.orient.y < -1
		|| rt->scene->camera.orient.z < -1)
		error_msg("invalid camera orientation!");
	if (rt->scene->camera.orient.x == 0 && rt->scene->camera.orient.y == 0
		&& rt->scene->camera.orient.z == 0)
		error_msg("invalid camera orientation!");
	rt->scene->camera.fov = ft_atod(arv[3]);
	if (rt->scene->camera.fov < 0 || rt->scene->camera.fov > 180)
		error_msg("FOV must be in range [0,180]");
	set_camera_scene(rt);
}
