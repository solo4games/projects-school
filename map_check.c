/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 13:33:18 by lbrandy           #+#    #+#             */
/*   Updated: 2021/02/22 14:39:44 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>

int		sign_check(char sign)
{
	char *temp;

	temp = "012 NEWS";
	while (*temp)
	{
		if (*temp == sign)
			return (1);
		temp++;
	}
	return (0);
}

int		check_map(char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!(sign_check(map[i][j])))
				return (-1);
			j++;
		}
		i++;
	}
	return (1);
}

