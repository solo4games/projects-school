/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:07:20 by lbrandy           #+#    #+#             */
/*   Updated: 2020/11/04 18:09:58 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *mas, size_t n)
{
	char	*temp;
	size_t	i;

	temp = (char*)mas;
	i = 0;
	while (i < n)
	{
		temp[i] = 0;
		i++;
	}
}
