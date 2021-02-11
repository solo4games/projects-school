/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 11:10:21 by lbrandy           #+#    #+#             */
/*   Updated: 2020/11/04 16:03:51 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*src_temp;

	i = 0;
	src_temp = (unsigned char *)src;
	if (!((unsigned char *)dst || src_temp))
		return (NULL);
	if ((unsigned char *)dst > src_temp)
	{
		while (len > 0)
		{
			((unsigned char *)dst)[len - 1] = src_temp[len - 1];
			len--;
		}
	}
	else
	{
		while (i < len)
		{
			((unsigned char *)dst)[i] = src_temp[i];
			i++;
		}
	}
	return ((unsigned char *)dst);
}
