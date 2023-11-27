/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:29:37 by asekmani          #+#    #+#             */
/*   Updated: 2023/10/26 16:29:40 by asekmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void free_scene(t_minirt *rt)
{
	t_light *light;
	t_light *next;
	t_obj *ob;
	t_obj *next_o;

	if(rt->scene)
		{
			light = rt->scene->light;
			while (light)
			{
			    next = light->next;
				free(light);
				light = next;
			}
		   ob = rt->scene->obj;
			while (ob)
			{
				next_o = ob->next;
				free(ob);
				ob = next_o;
			}
			free(rt->scene);
			rt->scene = NULL;
		}
}

void	clean_exit(int exit_code, t_minirt *rt)
{
	if (!rt)
		exit(exit_code);
	if (rt->img.img)
		mlx_destroy_image(rt->vars.mlx, rt->img.img);
	if (rt->vars.win && rt->vars.mlx)
		mlx_destroy_window(rt->vars.mlx, rt->vars.win);
	if (rt->vars.mlx)
	{	
		mlx_loop_end(rt->vars.mlx);
		mlx_destroy_display(rt->vars.mlx);
		free(rt->vars.mlx);
	}
	free_scene(rt);
	exit(exit_code);
}

int	end_minirt(t_minirt *mlx)
{
	clean_exit(0, mlx);
	return (0);
}

int	exit_key(int keycode, t_minirt *rt)
{
	if (keycode == 65307)
		end_minirt(rt);
	return (0);
}

void	error_msg(char *str)
{
	printf("Error : %s\n", str);
	exit(1);
}
