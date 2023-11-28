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

void	check_id(t_minirt *rt, char **arv, char *id, char *gnl)
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
	else
	{
		free_scene(rt);
		free_split(arv);
		free(gnl);
		error_msg("invalid identifier!!");
	}
}

void	ft_parsing(t_minirt *rt, int fd)
{
	char	**arv;
	char	*gnl;

	while (1)
	{
		gnl = get_next_line(fd);
		arv = ft_split(gnl, ' ');
		if (arv == NULL)
			break ;
		if (*arv)
			check_id(rt, arv, *arv, gnl);
		free_split(arv);
		free(gnl);
	}
	close(fd);
}
