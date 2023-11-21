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

void init_minirt(t_minirt *rt)
{
	rt->vars.mlx = mlx_init();
	if (rt->vars.mlx == NULL)
		exit(1);
	rt->vars.win = mlx_new_window(rt->vars.mlx, W, H, "My cute MiniRT!!");
	if (rt->vars.win == NULL)
	{
		free(rt->vars.win);
		exit(1);
	}
	rt->img.img = mlx_new_image(rt->vars.mlx, W, H);
	rt->img.addr = mlx_get_data_addr(rt->img.img, &rt->img.bits_per_pixel,
									 &rt->img.line_length, &rt->img.endian);
}

t_scene *init_scence(void)
{
	t_scene *scene;

	g_memory = NULL;
	scene = memory_adr(&g_memory, (sizeof(t_scene)));
	if (!scene)
		return (NULL);
	scene->obj = NULL;
	scene->ambient.counter = 0;
	scene->camera.counter = 0;
	scene->light = NULL;
	return (scene);
}

t_light *init_light(t_minirt *rt)
{
	t_light *new;

	new = malloc(sizeof(t_light));
	if (!new)
		error_msg("Error : light allocation!");
	new->next = rt->scene->light;
	rt->scene->light = new;
	return (new);
}

t_obj *init_obj(t_minirt *rt)
{
	t_obj *new;

	new = memory_adr(&g_memory, sizeof(t_obj));
	if (!new)
		return (NULL);
	new->color.x = new->color.y = new->color.z = 0;
	new->coord.x = new->coord.y = new->coord.z = 0;
	new->orient.x = new->orient.y = new->orient.z = 0;
	new->p.x = new->p.y = new->p.z = 0;
	new->next = rt->scene->obj;
	rt->scene->obj = new;
	return (new);
}

t_vec create_vectorv(double x, double y, double z)
{
	t_vec result;
	result.x = x;
	result.y = y;
	result.z = z;
	return result;
}

t_vec create_vector()
{
	t_vec result;
	result.x = 0;
	result.y = 0;
	result.z = 0;
	return result;
}

t_ray create_ray()
{
	t_ray result;
	result.coord = create_vector();
	result.direc = create_vector();
	return result;
}

t_obj create_t_obj()
{
	t_obj result;
	result.color = create_vector();
	result.coord = create_vector();
	result.cy_axe = create_vector();
	result.id = 0;
	result.next = NULL;
	result.orient = create_vector();
	result.p = create_vector();
	return result;
}

t_intersection create_int()
{
	t_intersection inter;
	inter.n = create_vector();
	inter.p = create_vector();
	inter.t = -1;
	return inter;
}

t_color_calculator init_color_calculator()
{

	t_color_calculator result;
	result.color_result = create_vector();
	result.inter_obj = create_t_obj();
	result.coord_light = create_vector();
	result.n = create_vector();
	result.p = create_vector();
	result.pos_light = create_ray();
	result.norm_light = create_vector();
	result.dis = 0;
	result.inter = false;
	result.inter_light = false;
	result.pixel = 0;
	result.pos_light = create_ray();
	result.norm_light = create_vector();
	return result;
}
