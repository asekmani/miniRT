/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:11:31 by asekmani          #+#    #+#             */
/*   Updated: 2023/10/31 15:11:35 by asekmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	check_id(t_minirt *rt, char **arv, char *id)
{
	if (id[0] == 'A' && id[1] == '\0')
		ambient_parse(rt, arv);
	else if (id[0] == 'C' && id[1] == '\0')
		camera_parse(rt, arv);
	else if (id[0] == 'L' && id[1] == '\0')
		light_parse(rt, arv);
	else if (id[0] == 's' && id[1] == 'p' && id[2] == '\0')
		sphere_parse(rt, arv);
	else if (id[0] == 'p' && id[1] == 'l' && id[2] == '\0')
		plane_parse(rt, arv);
	else if (id[0] == 'c' && id[1] == 'y' && id[2] == '\0')
		cylinder_parse(rt, arv);
	error_msg("invalid identifier!!", rt);
}

void	ft_parsing(t_minirt *rt, int fd)
{

	while (1)
	{
		rt->gnl = get_next_line(fd);
		rt->arv = ft_split(rt->gnl, ' ');
		if (rt->arv == NULL)
			break ;
		if (*rt->arv)
			check_id(rt, rt->arv, *rt->arv);
		free_split(rt->arv);
		free(rt->gnl);
		rt->gnl = NULL;
	}
	close(fd);
}
