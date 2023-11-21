/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:41:26 by asekmani          #+#    #+#             */
/*   Updated: 2023/11/21 18:41:35 by asekmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_vec	create_vectorv(double x, double y, double z)
{
	t_vec	result;

	result.x = x;
	result.y = y;
	result.z = z;
	return (result);
}

t_vec	create_vector(void)
{
	t_vec	result;

	result.x = 0;
	result.y = 0;
	result.z = 0;
	return (result);
}

t_ray	create_ray(void)
{
	t_ray	result;

	result.coord = create_vector();
	result.direc = create_vector();
	return (result);
}

t_obj	create_t_obj(void)
{
	t_obj	result;

	result.color = create_vector();
	result.coord = create_vector();
	result.cy_axe = create_vector();
	result.id = 0;
	result.next = NULL;
	result.orient = create_vector();
	result.p = create_vector();
	return (result);
}

t_inter	create_inter(void)
{
	t_inter	inter;

	inter.n = create_vector();
	inter.p = create_vector();
	inter.t = -1;
	return (inter);
}
