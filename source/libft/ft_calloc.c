/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 15:01:20 by lbrandy           #+#    #+#             */
/*   Updated: 2020/11/01 19:42:15 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char *p;

	p = (unsigned char *)malloc(count * size);
	if (!p)
		return (NULL);
	else
		ft_bzero(p, count * size);
	return (p);
}
