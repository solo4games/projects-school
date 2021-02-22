/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 13:27:27 by lbrandy           #+#    #+#             */
/*   Updated: 2021/02/22 13:33:10 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "./source/libft/libft.h"
#include <stdio.h>
#include "cub3D.h"

int     len_number_int(int n)
{
    int count;

    count = 0;
    if (n == 0)
        count += 1;
    while (n != 0)
    {
        count++;
        n = n / 10;
    }
    return (count);
}

int		check_structure(t_textures *textures)
{
	return(textures->x == -1 || textures->y == -1 || textures->NO_texture == NULL ||
		   	textures->SO_texture == NULL || textures->WE_texture == NULL ||
			textures->EA_texture == NULL || textures->S_texture == NULL ||
			textures->F == -1 || textures->C == -1);
}

int		count_digits(char *str)
{
	int counter;

	counter = 0;
	if (*str == '-')
		return (-1);
	while (ft_isdigit(*str))
	{
		counter++;
		str++;
	}
	return (counter);
}

void	ft_skip_numbers(char **str)
{
	while (ft_isdigit(**str) || **str == '-')
		(*str)++;
}

void	init_res(t_textures *win, char *str, t_all *all)
{
	int counter;

	counter = 0;
	if (win->x == -1 && win->y == -1)
	{
		while (!(*str >= 48 && *str <= 57) && *str != '-')
			str++;
		if (count_digits(str) >	10 || count_digits(str) == -1)
			win->x = 10000;
		else
			win->x = ft_atoi(str);
		ft_skip_numbers(&str);
		if (win->x > 640)//change to normal
			win->x = 640;
		while (!(*str >= 48 && *str <= 57) && *str != '-')
			str++;
		if (count_digits(str) > 10 || count_digits(str) == -1)
			win->y = 10000;
		else
			win->y = ft_atoi(str);
		ft_skip_numbers(&str);
		if (win->y > 480)//change to normal
			win->y = 480;
		(all->count_params)++;
	}
	else
		printf("Error\n");
}	

void	init_text(char **textures, char *str, t_all *all)
{
	while (*str != '.')
		str++;
	*textures = str;
	(all->count_params)++;
}

void	init_color(t_textures *col, char *str, t_all *all)
{
	int	R;
	int	G;
	int	B;

	if (ft_strncmp(str, "F ", 2) == 0)
	{
		while(*str < '0' && *str > '9')
			str++;
		R = ft_atoi(str);
		str += len_number_int(R) + 1;
		G = ft_atoi(str);
		str += len_number_int(G) + 1;
		B = ft_atoi(str);
		col->F = R << 16 | G << 8 | B;
		(all->count_params)++;
	}
	if (ft_strncmp(str, "C ", 2) == 0)
    {
        while(*str < '0' && *str > '9')
            str++;
        R = ft_atoi(str);
        str += len_number_int(R) + 1;
        G = ft_atoi(str);
        str += len_number_int(G) + 1;
        B = ft_atoi(str);
		col->C = R << 16 | G << 8 | B;
		(all->count_params)++;
    }
}

void	parse_map(t_list *list, t_all *all)
{
	int i;
	int	count;
	t_list *start_map;

	i = 0;
	count  = 0;
	start_map = list;
	while(start_map)
	{
		count++;
		start_map = start_map->next;
	}
	all->map = (char **)ft_calloc(count + 1, sizeof (char *));
	while (i < count)
	{
		all->map[i] = ft_strdup(list->content);
		list = list->next;
		i++;
	}
	for (int k = 0; k < count; k++)
		printf("map2 = %s\n", all->map[k]); 
	printf("parse map\n");
}

void	ft_skip(t_list **list)
{
	char	*s;
	int		i;

	s = "\n 012";
	i = 0;
	while(ft_strncmp((*list)->content, "", 1) == 0)
		*list = (*list)->next;
}

void	ft_parse(t_list **list, t_all *all)
{
	while (*list)
	{
		if (ft_strncmp((*list)->content, "R ", 2) == 0)
			init_res(all->textures, (*list)->content, all);
		if (ft_strncmp((*list)->content, "NO ", 3) == 0)
			init_text(&(all->textures->NO_texture), (*list)->content, all);
		if (ft_strncmp((*list)->content, "SO ", 3) == 0)
            init_text(&(all->textures->SO_texture), (*list)->content, all);
		if (ft_strncmp((*list)->content, "WE ", 3) == 0)
            init_text(&(all->textures->WE_texture), (*list)->content, all);
		if (ft_strncmp((*list)->content, "EA ", 3) == 0)
            init_text(&(all->textures->EA_texture), (*list)->content, all);
		if (ft_strncmp((*list)->content, "S ", 2) == 0)
            init_text(&(all->textures->S_texture), (*list)->content, all);
		init_color(all->textures, (*list)->content, all);
		(*list) = (*list)->next;
		if (check_structure(all->textures) == 0)
			break;
	}
	/*if (all->count_params == 8 && check_structure(all->textures) == 0)
	{
		printf("NIIIIIIIIICE %d - ", all->textures->x);
	}*/
}

