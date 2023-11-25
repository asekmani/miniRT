/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 11:36:49 by asekmani          #+#    #+#             */
/*   Updated: 2022/11/30 11:14:21 by asekmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static int	ft_count_w(char const *str, char c)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && str[i] == c)
			i++;
		if (str[i] != '\0')
			nbr++;
		while (str[i] != '\0' && str[i] != c)
			i++;
	}
	return (nbr);
}

static void	*ft_free(char **s, size_t j)
{
	while (j > 0)
	{
		j--;
		free(s[j]);
	}
	free(s);
	return (NULL);
}

static size_t	ft_get_word_len(char const *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static char	*ft_word(char const *str, char c)
{
	size_t	i;
	char	*word;

	if (!str)
		return (NULL);
	word = (char *)malloc(sizeof(char) * (ft_get_word_len(str, c) + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < ft_strlen(str) && str[i] != c)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *str, char c)
{
	int		i;
	char	**res;

	if (!str)
		return (NULL);
	res = (char **)ft_calloc(ft_count_w(str, c) + 1, sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	while (*str != '\0')
	{
		while (*str != '\0' && *str == c)
			str++;
		if (*str != '\0')
		{
			res[i] = ft_word(str, c);
			if (!res[i])
				return (ft_free(res, i));
			i++;
		}
		while (*str != '\0' && *str != c)
			str++;
	}
	res[i] = 0;
	return (res);
}
