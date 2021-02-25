/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 13:17:20 by lbrandy           #+#    #+#             */
/*   Updated: 2021/02/09 17:42:01 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "./source/libft/libft.h"
#include "cub3D.h"

void	init_dir(t_pos *pos, char temp)
{
	if (temp == 'N' || temp == 'S')
	{
		pos->dir_x = 0;
		pos->dir_y = 1;
		pos->plane_x = 0.66;
		pos->plane_y = 0;
		if (temp == 'N')
		{
			pos->dir_y = -1;
			pos->plane_x = -0.66;
		}
	}
	else if (temp == 'W' || temp = 'E')
	{
		pos->dir_x = -1;
		pos->dir_y = 0;
		pos->plane_x = 0;
		pos->plane_y = 0.66;
		if (temp == 'E')
		{
			pos->dir_x = 1;
			pos->plane_y = -0.66;
		}
	}
}

void	init_pos(char **map, t_pos *pos)
{
	int		i;
	int		j;
	char	temp;

	i = 0;
	while (map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if(map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E')
			{
				pos->pos_x = j;
				pos->pos_y = i;
				temp = map[i][j];
			}
			j++;
		}
		i++;
	}
	init_dir(pos, temp);
	pos->map_width = j;
	pos->map_height = i;
	pos->time = 0;
	pos->old_time = 0;
}

void	init_struct(t_textures *t)
{
	t->x = -1;
	t->y = -1;
	t->NO_texture = NULL;
	t->SO_texture = NULL;
	t->WE_texture = NULL;
	t->EA_texture = NULL;
	t->S_texture = NULL;
	t->F = -1;
	t->C = -1;
}

int main (int argc, char *argv[])
{
	int fd;
	t_list *list;
	char *line;
	t_all *all;

	(void)argc;
	all = (t_all*)malloc(sizeof(t_all));
	all->count_params = 0;
	all->textures = (t_textures*)malloc(sizeof(t_textures));
	all->pos = (t_pos *)malloc(sizeof(t_pos));
	init_struct(all->textures);
	if (ft_strlen(argv[1]) > 4)
	{
		if (ft_strncmp(&(argv[1][ft_strlen(argv[1]) - 4]), ".cub", 4) == 0)
		{
			if ((fd = open_file(argv[1])) == -1)
				return(-1);
			while (get_next_line(fd, &line) == 1)
				ft_lstadd_back(&list, ft_lstnew(line));
			ft_parse(&list, all);
			ft_skip(&list);
			parse_map(list, all);
			if (check_map(all->map))
			{
				init_pos(all->map, all->pos);
				raycasting(all);
			}
		}
		else
			write(1, "yes", 3);
	}
	else
		write(1, "es", 2);
}
