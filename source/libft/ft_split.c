/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 18:31:18 by lbrandy           #+#    #+#             */
/*   Updated: 2020/11/04 17:41:21 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		**mas_free(char **mas, int j)
{
	j--;
	while (j >= 0)
	{
		free(mas[j]);
		j--;
	}
	free(mas);
	return (NULL);
}

static int		word_count(char const *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count + 1);
}

static	char	**spliter(char const *s, char c, char **mas, int count)
{
	int	i;
	int	len;
	int	j;

	i = 0;
	j = 0;
	while (j < count && s[i])
	{
		len = 0;
		if (s[i] != c)
		{
			while (s[i] != c && s[i])
			{
				len++;
				i++;
			}
			if (!(mas[j++] = ft_substr(s, i - len, len)))
				return (mas_free(mas, j));
		}
		i++;
	}
	mas[j] = NULL;
	return (mas);
}

char			**ft_split(char const *s, char c)
{
	char	**temp;

	if (!s)
		return (NULL);
	temp = (char **)malloc(sizeof(char *) * (word_count(s, c)));
	if (!temp)
		return (NULL);
	return (spliter(s, c, temp, word_count(s, c) - 1));
}
