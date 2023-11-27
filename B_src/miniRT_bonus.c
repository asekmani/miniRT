/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 15:37:56 by asekmani          #+#    #+#             */
/*   Updated: 2023/10/14 15:38:00 by asekmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"


static int	check_and_open_file(int arc, char **arv)
{
	int	i;
	int	fd;

	fd = 0;
	if (arc != 2)
		return (1);
	if (!arv[1])
		return (1);
	i = ft_strlen(arv[1]);
	if (i < 4)
		return (1);
	if (arv[1][i - 1] == 't' || arv[1][i - 2] == 'r' || arv[1][i - 3] == '.')
	{
		fd = open(arv[1], O_RDONLY);
		if (fd < 0)
			return (1);
		close(fd);
	}
	else
		return (1);
	return (0);
}

int	main(int arc, char **arv)
{
	int			fd;
	t_minirt	rt;

	if (check_and_open_file(arc, arv) != 0)
		error_msg("wrong args!");
	fd = open(arv[1], O_RDONLY);
	rt.scene = init_scence();
	if (!rt.scene)
		error_msg("no scene!");
	ft_parsing(&rt, fd);
	init_minirt(&rt);
	render_rt(&rt);
	return (0);
}
