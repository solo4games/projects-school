/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 16:54:31 by lbrandy           #+#    #+#             */
/*   Updated: 2020/11/06 16:26:17 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		find_start(char const *s1, char const *set)
{
	size_t	j;
	int		start;

	start = 0;
	while (s1[start])
	{
		j = 0;
		while (set[j])
		{
			if (s1[start] == set[j])
				break ;
			j++;
		}
		if (j == ft_strlen(set))
			break ;
		start++;
	}
	return (start);
}

static int		find_end(char const *s1, char const *set)
{
	size_t	j;
	int		end;

	end = ft_strlen(s1) - 1;
	while (end > -1)
	{
		j = 0;
		while (set[j])
		{
			if (s1[end] == set[j])
				break ;
			j++;
		}
		if (j == ft_strlen(set))
			break ;
		end--;
	}
	return (end);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char	*temp;
	int		start;
	int		end;
	int		k;

	if (!s1)
		return (NULL);
	start = find_start(s1, set);
	end = find_end(s1, set);
	k = 0;
	temp = (start > end) ? (char *)malloc(1) : (char *)malloc(end - start + 2);
	if (!temp)
		return (NULL);
	while (start <= end)
	{
		temp[k] = s1[start];
		k++;
		start++;
	}
	temp[k] = '\0';
	return (temp);
}
