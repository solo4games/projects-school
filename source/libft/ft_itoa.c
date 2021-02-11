/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 15:49:57 by lbrandy           #+#    #+#             */
/*   Updated: 2020/11/04 18:28:52 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_rev(int count, char *num)
{
	int		i;
	int		k;
	char	temp;

	k = 0;
	i = 0;
	if (num[0] == '-')
		i++;
	while (k < count / 2)
	{
		temp = num[count - k - 1];
		num[count - k - 1] = num[i];
		num[i] = temp;
		k++;
		i++;
	}
	return (num);
}

static int	ft_counting(int n)
{
	int	temp;
	int	count;

	temp = n;
	count = 0;
	if (n == 0)
		count++;
	while (temp != 0)
	{
		if (temp < 0)
		{
			temp *= -1;
			count++;
		}
		temp /= 10;
		count++;
	}
	return (count);
}

char		*ft_itoa(int n)
{
	char	*num;
	int		i;
	int		count;

	i = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	count = ft_counting(n);
	num = (char *)malloc((count + 1) * sizeof(char));
	if (!num)
		return (NULL);
	if (n < 0)
	{
		num[i++] = '-';
		n *= -1;
	}
	while (i < count)
	{
		num[i++] = (n % 10) + '0';
		n /= 10;
	}
	num = ft_rev(count, num);
	num[i] = '\0';
	return (num);
}
