/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:50:08 by asekmani          #+#    #+#             */
/*   Updated: 2023/11/13 18:50:16 by asekmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_vec	vec_add(t_vec v1, t_vec v2)
{
	t_vec	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return (result);
}

t_vec	vec_subtract(t_vec v1, t_vec v2)
{
	t_vec	result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}

t_vec	vec_multiply(t_vec v, double scalar)
{
	t_vec	result;

	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
	return (result);
}

t_vec	vec_divide(t_vec v, double scalar)
{
	t_vec	result;

	if (scalar != 0)
	{
		result.x = v.x / scalar;
		result.y = v.y / scalar;
		result.z = v.z / scalar;
		return (result);
	}
	else
	{
		result = (t_vec){0.0, 0.0, 0.0};
		return (result);
	}
}

double	vec_length(t_vec v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}
