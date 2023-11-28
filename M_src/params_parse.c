/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:10:25 by asekmani          #+#    #+#             */
/*   Updated: 2023/11/03 12:10:28 by asekmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_vec	color_parse(char *str, t_minirt *rt)
{
	t_vec	color;
	char	**rgb;

	rgb = ft_split(str, ',');
	if (!rgb || !rgb[1] || !rgb[2] || rgb[3])
		error_msg("invalid color!", rt);
	color.x = ft_atoi(rgb[0]);
	color.y = ft_atoi(rgb[1]);
	color.z = ft_atoi(rgb[2]);
	if (color.x > 255 || color.y > 255 || color.z > 255)
		error_msg("invalid color!", rt);
	if (color.x < 0 || color.y < 0 || color.z < 0)
		error_msg("invalid color!", rt);
	free_split(rgb);
	return (color);
}

t_vec	vectors_parse(char *str, t_minirt *rt)
{
	t_vec	vectors;
	char	**arg;

	arg = ft_split(str, ',');
	if (!arg || !arg[1] || !arg[2] || arg[3])
		error_msg("invalid vectors", rt);
	vectors.x = ft_atod(arg[0]);
	vectors.y = ft_atod(arg[1]);
	vectors.z = ft_atod(arg[2]);
	free_split(arg);
	return (vectors);
}
