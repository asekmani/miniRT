/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:05:13 by asekmani          #+#    #+#             */
/*   Updated: 2023/11/22 13:05:16 by asekmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_vec norm_color(t_vec v)
{
    t_vec result;

    result.x = v.x / 255;
    result.y = v.y / 255;
    result.z = v.z / 255;
    return result;
}

t_vec	add_color(t_vec col1, t_vec col2)
{
	t_vec	res;

	res = vec_add(col1, col2);
	if (res.x > 255)
		res.x = 255;
	if (res.y > 255)
		res.y = 255;
	if (res.z > 255)
		res.z = 255;
	return (res);
}

t_vec calcul_coef_color(t_vec obj_color, t_vec amb_col, double ratio)
{
	t_vec result;

	result.x = obj_color.x * (amb_col.x / 255) * ratio; 
	result.y = obj_color.y * (amb_col.y / 255) * ratio; 
	result.z = obj_color.z * (amb_col.z / 255) * ratio; 
	return (result);
}