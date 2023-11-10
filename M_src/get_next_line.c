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

int	ft_strchr_gnl(char *s, char c)
{
	int	i;

	i = 0;
	if(!s)
		return (0);
	while(s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_join_gnl(char *s1, char c)
{
	char	*join;
	int		i;

	i = -1;
	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		s1[0] = 0;
	}
	join = malloc(ft_strlen(s1) + 2);
	if (!join)
		return (free(s1), NULL);
	while (s1[++i])
		join[i] = s1[i];
	join[i] = c;
	join[i + 1] = '\0';
	free(s1);
	return (join);
}

void	ft_clean_gnl(char *line, char *buff)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(line[i] && line[i] != 10)
		i++;
	if (line[i] == 10)
		i++;
	while (line[i])
	{
		buff[j] = line[i];
		line[i] = '\0';
		i++;
		j++;
	}
	buff[j] = '\0';
}

char	*get_next_line(int	fd)
{
	char	buffer[2];
	char	*line;
	int		byte_read;

	if (fd < 0)
		return (NULL);
	line = NULL;
	while (1)
	{
		byte_read = read(fd, buffer, 1);
		if (byte_read < 0)
			return (free(line), NULL);
		if (byte_read == 0 || ft_strchr_gnl(line, '\n'))
			break;
		buffer[byte_read] = 0;
		line = ft_join_gnl(line, buffer[0]);
	}
	if (!line || !line[0])
		return(free(line), NULL);
	else
		ft_clean_gnl(line, buffer);
	return (line);
}
