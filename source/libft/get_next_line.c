/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 13:25:28 by lbrandy           #+#    #+#             */
/*   Updated: 2021/01/25 16:13:04 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*static char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*temp;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	temp = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		temp[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		temp[i + j] = s2[j];
		j++;
	}
	temp[i + j] = '\0';
	return (temp);
}*/

/*static char		*ft_strdup(const char *s1)
{
	char	*copy;
	int		i;

	copy = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!copy)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}*/

static char		*left_checking(char **line, char **left)
{
	char	*p;

	p = NULL;
	if (*left)
	{
		if ((p = ft_strchr(*left, '\n')))
		{
			*p = '\0';
			if (!(*line = ft_strdup(*left)))
				ft_clean_left(left);
			*left = ft_strcpy(*left, ++p);
		}
		else
		{
			*line = ft_strdup(*left);
			free(*left);
			*left = NULL;
		}
	}
	else if (!(*line = ft_strdup("")))
		ft_clean_left(left);
	return (p);
}

static int		doing_line(char **p, char *buf, char **left, char **line)
{
	char	*temp;

	if ((*p = ft_strchr(buf, '\n')))
	{
		**p = '\0';
		(*p)++;
		if (!(*left = ft_strdup(*p)))
		{
			free(*line);
			*line = 0;
			free(buf);
			return (-1);
		}
	}
	temp = *line;
	if (!(*line = ft_strjoin(*line, buf)))
	{
		free(*left);
		free(temp);
		return (-1);
	}
	free(temp);
	return (1);
}

int				get_next_line(int fd, char **line)
{
	char			*buf;
	static char		*left;
	int				n;
	char			*p;

	buf = NULL;
	if (BUFFER_SIZE < 1 || read(fd, buf, 0) < 0 || (!(line)) ||
			(!(buf = malloc(sizeof(char) * (BUFFER_SIZE + 1)))))
		return (-1);
	p = left_checking(line, &left);
	if (!(*line))
		return (-1);
	while (!p && (n = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[n] = '\0';
		if (doing_line(&p, buf, &left, line) == -1)
		{
			free(buf);
			return (-1);
		}
	}
	free(buf);
	return (p ? 1 : 0);
}
