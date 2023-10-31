/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_analy_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:12:25 by asekmani          #+#    #+#             */
/*   Updated: 2023/10/31 15:12:31 by asekmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	ambient_analy(t_minirt *rt, char **arv)
{
	if (!arv || !arv[1] || !arv[2] || arv[3])
		ft_err("invalid args for Ambient Light!");
	if (rt->scene->ambient.counter != 0)
		ft_err("Error : no more than one Ambient Light");
	rt->scene->ambient.counter++;
	rt->scene->ambient.ratio = ft_atod(arv[1]);
	if (rt->scene->ambient.ratio < 0 || rt->scene->ambient.ratio > 1)
		ft_err("Error : Ambient Light must be in range [0.0,1.0]");
	// sc->amb.col = get_color(arv[2]);
}