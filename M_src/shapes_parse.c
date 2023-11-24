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

	if (!arv || !arv[1] || !arv[2] || !arv[3] || arv[4])
		error_msg("invalid args for sphere!");
	obj = init_obj(rt);
	obj->id = SP;
	obj->coord = vectors_parse(arv[1]);
	obj->p.x = ft_atod(arv[2]);
	if (obj->p.x <= 0)
		error_msg("invalid diameter sphere!");
	obj->color = color_parse(arv[3]);
}

void	plane_parse(t_minirt *rt, char **arv)
{
	t_obj	*obj;

	if (!arv || !arv[1] || !arv[2] || !arv[3] || arv[4])
		error_msg("invalid args for plane!");
	obj = init_obj(rt);
	obj->id = PL;
	obj->coord = vectors_parse(arv[1]);
	obj->orient = vectors_parse(arv[2]);
	if (obj->orient.x > 1 || obj->orient.y > 1 || obj->orient.z > 1)
		error_msg("invalid 3d orientation for plane");
	if (obj->orient.x < -1 || obj->orient.y < -1 || obj->orient.z < -1)
		error_msg("invalid 3d orientation for plane");
	obj->color = color_parse(arv[3]);
}

void	cylinder_parse(t_minirt *rt, char **arv)
{
	t_obj	*obj;

	if (!arv || !arv[1] || !arv[2] || !arv[3] || !arv[4] || !arv[5] || arv[6])
		error_msg("invalid args for cylinder");
	obj = init_obj(rt);
	obj->id = CY;
	obj->coord = vectors_parse(arv[1]);
	obj->orient = vectors_parse(arv[2]);
	if (obj->orient.x > 1 || obj->orient.y > 1 || obj->orient.z > 1)
		error_msg("invalid 3d orientation for cylinder");
	if (obj->orient.x < -1 || obj->orient.y < -1 || obj->orient.z < -1)
		error_msg("invalid 3d orientation for cylinder");
	obj->p.x = ft_atod(arv[3]);
	obj->p.y = ft_atod(arv[4]);
	if (obj->p.x <= 0 || obj->p.y <= 0)
		error_msg("invalid diameter cylinder!");
	obj->color = color_parse(arv[5]);
}

void	cone_parse(t_minirt *rt, char **arv)
{
	t_obj	*obj;

	if (!arv || !arv[1] || !arv[2] || !arv[3] || !arv[4]
		|| !arv[5] || !arv[6] || arv[7])
		error_msg("invalid args for cone");
	obj = init_obj(rt);
	obj->id = CO;
	obj->coord = vectors_parse(arv[1]);
	obj->orient = vectors_parse(arv[2]);
	if (obj->orient.x > 1 || obj->orient.y > 1 || obj->orient.z > 1)
		error_msg("invalid 3d orientation for cone");
	if (obj->orient.x < -1 || obj->orient.y < -1 || obj->orient.z < -1)
		error_msg("invalid 3d orientation for cone");
	obj->p.x = ft_atod(arv[3]);
	if (obj->p.x <= 0 && obj->p.x > 180)
		error_msg("invalid diameter cone");
	obj->p.y = ft_atod(arv[4]);
	if (obj->p.x <= 0 && obj->p.x > 180)
		error_msg("invalid diameter cone");
	obj->p.z = ft_atod(arv[5]);
	if (obj->p.x <= 0 && obj->p.x > 180)
		error_msg("invalid diameter cone");
	obj->color = color_parse(arv[6]);
}
