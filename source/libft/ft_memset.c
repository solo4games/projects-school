/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 14:11:11 by lbrandy           #+#    #+#             */
/*   Updated: 2020/10/30 17:00:33 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *mas, int c, size_t len)
{
	size_t			i;
	char			*st;

	st = (char *)mas;
	i = 0;
	while (i < len)
	{
		st[i++] = (unsigned char)c;
	}
	return (mas);
}
