/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 14:28:17 by lbrandy           #+#    #+#             */
/*   Updated: 2021/01/30 18:50:49 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	temp;
	int	i;
	int	minus;

	temp = 0;
	i = 0;
	minus = 1;
	while (str[i] <= 26 || str[i] == 32)
		i++;
	if (str[i] == 45)
	{
		i++;
		minus *= -1;
	}
	else if (str[i] == 43)
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		temp = temp * 10 + (str[i] - '0');
		i++;
	}
	return (temp * minus);
}
