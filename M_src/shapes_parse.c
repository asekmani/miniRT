/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:12:43 by asekmani          #+#    #+#             */
/*   Updated: 2023/10/31 15:12:47 by asekmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	sphere_parse(t_minirt *rt, char **arv)
{
	t_obj	*obj;

	rt->scene->counter++;
	if (!arv || !arv[1] || !arv[2] || !arv[3] || arv[4])
		error_msg("invalid args for sphere!", rt);
	obj = init_obj(rt);
	obj->id = SP;
	obj->coord = vectors_parse(arv[1], rt);
	obj->p.x = ft_atod(arv[2]);
	if (obj->p.x <= 0)
		error_msg("invalid diameter sphere!", rt);
	obj->color = color_parse(arv[3], rt);
}

void	plane_parse(t_minirt *rt, char **arv)
{
	t_obj	*obj;

	rt->scene->counter++;
	if (!arv || !arv[1] || !arv[2] || !arv[3] || arv[4])
		error_msg("invalid args for plane!", rt);
	obj = init_obj(rt);
	obj->id = PL;
	obj->coord = vectors_parse(arv[1], rt);
	obj->orient = vectors_parse(arv[2], rt);
	if (obj->orient.x > 1 || obj->orient.y > 1 || obj->orient.z > 1)
		error_msg("invalid 3d orientation for plane", rt);
	if (obj->orient.x < -1 || obj->orient.y < -1 || obj->orient.z < -1)
		error_msg("invalid 3d orientation for plane", rt);
	obj->color = color_parse(arv[3], rt);
}

void	cylinder_parse(t_minirt *rt, char **arv)
{
	t_obj	*obj;

	rt->scene->counter++;
	if (!arv || !arv[1] || !arv[2] || !arv[3] || !arv[4] || !arv[5] || arv[6])
		error_msg("invalid args for cylinder",rt);
	obj = init_obj(rt);
	obj->id = CY;
	obj->coord = vectors_parse(arv[1], rt);
	obj->orient = vectors_parse(arv[2], rt);
	if (obj->orient.x > 1 || obj->orient.y > 1 || obj->orient.z > 1)
		error_msg("invalid 3d orientation for cylinder", rt);
	if (obj->orient.x < -1 || obj->orient.y < -1 || obj->orient.z < -1)
		error_msg("invalid 3d orientation for cylinder", rt);
	obj->p.x = ft_atod(arv[3]);
	obj->p.y = ft_atod(arv[4]);
	if (obj->p.x <= 0 || obj->p.y <= 0)
		error_msg("invalid diameter cylinder!", rt);
	obj->color = color_parse(arv[5], rt);
}
