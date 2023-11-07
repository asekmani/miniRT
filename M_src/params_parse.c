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

t_col	color_parse(char *str)
{
	t_col	color;
	char	**rgb;

	rgb = ft_split(str, ',');
	if (!rgb || !rgb[1] || !rgb[2] || rgb[3])
		error_msg("Error : invalid color!");
	color.r = ft_atoi(rgb[0]);
    color.g = ft_atoi(rgb[1]);
    color.b = ft_atoi(rgb[2]);
	if (color.r > 255 || color.g > 255 || color.b > 255)
		error_msg("Error : invalid color!");
	if (color.r < 0 || color.g < 0 || color.b < 0)
		error_msg("Error : invalid color!");
	free_split(rgb);
	return (color);
}

t_vec	vectors_parse(char *str)
{
	t_vec	vectors;
	char	**arg;

	arg = ft_split(str, ',');
	if (!arg || !arg[1] || !arg[2] || arg[3])
		error_msg("Error : invalid vectors");
	vectors.x = ft_atod(arg[0]);
    vectors.y = ft_atod(arg[1]);
    vectors.z = ft_atod(arg[2]);
	free_split(arg);
	return (vectors);
}