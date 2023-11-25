/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:48:28 by asekmani          #+#    #+#             */
/*   Updated: 2023/10/04 16:07:19 by asekmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

char	*ft_strjoin(char *s, char c)
{
	char	*out;
	int		n;

	n = 2;
	if (s)
		while (*s && s++)
			n++;
	out = malloc(n * sizeof(char));
	out[--n] = '\0';
	out[--n] = c;
	if (s)
	{
		while (n--)
			out[n] = *--s;
		free(s);
	}
	return (out);
}

char	*get_next_line(int fd)
{
	char		c;
	static char	*line;

	line = NULL;
	if (line)
		free(line);
	line = NULL;
	while (read(fd, &c, 1) && (c != '\n' || line == NULL))
	{
		if (c == '\n')
			continue ;
		line = ft_strjoin(line, c);
	}
	return (line);
}
