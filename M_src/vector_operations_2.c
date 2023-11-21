/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 19:03:50 by asekmani          #+#    #+#             */
/*   Updated: 2023/11/21 19:03:53 by asekmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

double	vec_module(t_vec	v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
}

t_vec vect_cross(t_vec u, t_vec v)
{
    t_vec w;

    w.x = (u.y * v.z) - (u.z * v.y);
    w.y = (u.x * v.z) - (u.z * v.x);
    w.z = (u.x * v.y) - (u.y * v.x);
    return (w);
}

// Produit scalaire de deux vecteurs
double dot_product(t_vec v1, t_vec v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

t_vec normalize(t_vec v)
{
    double length;
    t_vec result;

    length = vec_length(v);
    result.x = v.x / length;
    result.y = v.y / length;
    result.z = v.z / length;
    return result;
}

double norm(t_vec v)
{
    return v.x * v.x + v.y * v.y + v.z * v.z;
}
