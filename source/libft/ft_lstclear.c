/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 12:05:07 by lbrandy           #+#    #+#             */
/*   Updated: 2020/11/04 15:02:08 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*next;

	if (lst)
	{
		temp = *lst;
		while (temp)
		{
			next = temp->next;
			del(temp->content);
			free(temp);
			temp = next;
		}
		*lst = NULL;
	}
}
