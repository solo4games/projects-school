/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 10:41:42 by lbrandy           #+#    #+#             */
/*   Updated: 2020/11/04 16:03:39 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t				i;
	unsigned char		*dst_temp;
	unsigned char		*src_temp;

	dst_temp = (unsigned char *)dst;
	src_temp = (unsigned char *)src;
	i = 0;
	while ((i < n) && (src_temp[i] != (unsigned char)c))
	{
		dst_temp[i] = src_temp[i];
		i++;
	}
	if (i == n)
		return (NULL);
	dst_temp[i] = src_temp[i];
	return (&dst_temp[i + 1]);
}
