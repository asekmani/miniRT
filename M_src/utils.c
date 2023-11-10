/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:56:43 by asekmani          #+#    #+#             */
/*   Updated: 2023/10/26 14:56:47 by asekmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;
	char	*res_char;
	size_t	total_size;
	size_t i;

	if (nmemb >= SIZE_MAX || size >= SIZE_MAX)
		return (NULL);
	res = malloc(nmemb * size);
	if (!res)
		return (NULL);
	res_char = (char *)res;
	total_size = nmemb * size;
	i = 0;
	while (++i < total_size)
	{
		res_char[i] = '\0';
		i++;
	}
	return (res);
}

double	ft_atod(const char *str)
{
	double	nb;
	int		signe;
	int		i;
	int		aux;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	signe = 1;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			signe = -1;
	nb = 0;
	while (str[i] >= '0' && str[i] <= '9')
		nb = nb * 10 + (str[i++] - '0');
	if (str[i] != '.')
		return ((double)nb * signe);
	aux = 10;
	while (str[++i] >= '0' && str[i] <= '9')
	{
		nb = nb + (double)(str[i] - '0') / aux;
		aux = aux * 10;
	}
	return ((double)nb * signe);
}

void	free_split(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}