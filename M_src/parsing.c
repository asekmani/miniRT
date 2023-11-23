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
	// else if (id[0] == 'c' && id[1] == 'o' && id[2] == '\0')
	// 	cone_parse(rt, arv);
	else
		error_msg("Error : invalid identifier!!");
}

void	ft_parsing(t_minirt *rt, int fd)
{
	char	**arv;

	while (1)
	{
		arv = ft_split(get_next_line(fd), ' ');
		if (arv == NULL)
			break ;
		if (*arv)
			check_id(rt, arv, *arv);
		free_split(arv);
	}
	close(fd);
}
