/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:56:07 by asekmani          #+#    #+#             */
/*   Updated: 2023/10/30 13:56:13 by asekmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	init_minirt(t_minirt	*rt)
{
	rt->vars.mlx = mlx_init();
    if (rt->vars.mlx == NULL)
        exit(1);
    rt->vars.win = mlx_new_window(rt->vars.mlx, WIDTH, HEIGHT, "My cute MiniRT!!");
    if (rt->vars.win == NULL)
	{
		free(rt->vars.win);
		exit(1);
	}
	rt->img.img = mlx_new_image(rt->vars.mlx, WIDTH, HEIGHT);
	rt->img.addr = mlx_get_data_addr(rt->img.img, &rt->img.bits_per_pixel,
			&rt->img.line_length, &rt->img.endian);
}

t_scene	*init_scence(void)
{
    t_scene	*scene;

	g_memory = NULL;
	scene = memory_adr(&g_memory, (sizeof(t_scene)));
	if (!scene)
		return (NULL);
	scene->objs = NULL;
	scene->ambient.counter = 0;
	// scene->cam.count = 0;
	scene->light = NULL;
	return(scene);
}