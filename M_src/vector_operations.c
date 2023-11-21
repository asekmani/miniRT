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

// Addition de deux vecteurs
t_vec vec_add(t_vec v1, t_vec v2)
{
    t_vec result;

    result.x = v1.x + v2.x;
    result.y = v1.y + v2.y;
    result.z = v1.z + v2.z;
    return result;
}
// Soustraction de deux vecteurs
t_vec vec_subtract(t_vec v1, t_vec v2)
{
    t_vec result;

    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;
    result.z = v1.z - v2.z;
    return result;
}
// Multiplication d'un vecteur par un scalaire
t_vec vec_multiply(t_vec v, double scalar)
{
    t_vec result;

    result.x = v.x * scalar;
    result.y = v.y * scalar;
    result.z = v.z * scalar;
    return result;
}

double	module_v(t_vec	v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
}
// Produit scalaire de deux vecteurs
double dot_product(t_vec v1, t_vec v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
// Norme (magnitude) d'un vecteur
double vec_length(t_vec v)
{
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}
// Division d'un vecteur par un scalaire
t_vec vec_divide(t_vec v, double scalar)
{
    // Assurez-vous que le scalaire n'est pas égal à zéro pour éviter la division par zéro
    if (scalar != 0)
    {
        t_vec result;

        result.x = v.x / scalar;
        result.y = v.y / scalar;
        result.z = v.z / scalar;
        return result;
    }
    // Gestion du cas où le scalaire est égal à zéro (vous pouvez choisir le comportement approprié)
    // Par exemple, renvoyer un vecteur nul ou lever une erreur.
    // Dans cet exemple, renvoyer un vecteur nul.
    else
    {
        t_vec result;

        result = (t_vec){0.0, 0.0, 0.0};
        return(result);
    }
}
// Normalisation d'un vecteur (rendre sa norme égale à 1)
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

t_vec vect_cross(t_vec u, t_vec v)
{
    t_vec w;

    w.x = (u.y * v.z) - (u.z * v.y);
    w.y = (u.x * v.z) - (u.z * v.x);
    w.z = (u.x * v.y) - (u.y * v.x);
    return (w);
}
// Normalisation d'une couleur
t_vec norm_color(t_vec v)
{
    t_vec result;

    result.x = v.x / 255;
    result.y = v.y / 255;
    result.z = v.z / 255;
    return result;
}
// calcul de norme
double norm(t_vec v)
{
    return v.x * v.x + v.y * v.y + v.z * v.z;
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
