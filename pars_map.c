

#include "cub3D.h"

t_list	*skip_empty_lines(t_list *tmp)
{
	char *s;

	while (tmp)
	{
		s = tmp->content;
		if (s)
		{
			while (*s == ' ')
				s++;
			if (*s != '\0')
				break;
		}
		tmp = tmp->next;
	}
	return (tmp);
}

int	check_str(char *s)
{
	if (!*s)
		return (1);
	while (*s)
	{
		if (*s != ' ')
			return (0);
		s++;
	}
	return (0);
}

void	check_trash(t_list *map)
{
	int count;

	count = 0;
	if (map)
	{
		while (map)
		{
			count++;
			map = map->next;
		}
	}
	else
		return ;
	if (count > 1)
		write(1, "error\n", 6);
}

void	init_pos(t_all *all, t_pos *pos)
{
	int i;
	int j;
	char dir;

	i = 0;
	dir = '\0';
	while (all->map[i])
	{
		j = 0;
		while (all->map[i][j])
		{
			if (ft_strchr(" 012WSEN", all->map[i][j]) == NULL)
				write(1, "error\n", 6);
			else if (all->map[i][j] == 'N' || all->map[i][j] == 'E'
				|| all->map[i][j] == W || all->map[i][j] == 'S')
			{
				if (dir != '\0')
					write(1, "error\n", 6);
				else
				{
					pos->pos_x = i + 0.5;
					pos->pos_y = j + 0.5;
					all->map[i][j] = '0';
					init_dir(t_pos *pos, dir);//взять тот что уже есть в парсере
				}
			}
			j++;
		}
		i++;
	}
	if (dir == '\0')
		write(1, "error\n", 6);
	pos->map_height = i;
}

void	check_up_down(char **map, int i, int h)
{
	while (map[0][i])
	{
		if (map[0][i] == '1' || map[0][i] == ' ')
			i++;
		else
			write(1, "error\n", 6);
	}
	i = 0;
	while (map[h - 1][i])
	{
		if (map[h - 1][i] == '1' || map[h - 1][i] == ' ')
			i++;
		else
			write(1, "error\n", 6);
	}
}

void	check_bound(t_all *all, char **map)
{
	int i;
	int h;

	i = 0;
	h = all->pos->map_height;
	check_up_down(all->map, i);
	while (map[i][0])
        {
                if (map[i][0] == '1' || map[i][0] == ' ')
                        i++;
                else
                        write(1, "error\n", 6);
        }
        i = 0;
	while (map[i][ft_strlen(map[i]) - 1])
	{
		if (map[i][ft_strlen(map[i]) - 1] == '1' ||
			map[i][ft_strlen(map[i]) - 1] == ' ')
			i++;
		else
			write(1, "error\n", 6);
	}
}

int	max_width_map(char **map)
{
	int i;
	int j;
	int max;

	i = 0;
	max = 0;
	while (map[i])
	{
		j = 0;
		whilel (map[i][j])
			j++;
		if (j > max)
			max = j;
		i++;
	}
	return (max);
}

int	copy_all_map(t_pos *p, char **map, int i, t_all *all)
{
	int	k;
	char	new_symbol;
	int	j;

	k = 0;
	new_symbol = '^';
	while (k < p->map_height)
	{
		map[i] = (char *)ft_calloc(p->map_width + 1, sizeof(char));
		ft_strcpy(map[i], all->map[k]);
		if ((int)ft_strlen(all->map[k]) < p->map_width)
		{
			j = ft_strlen(all->map[k]);
			while (j < p->map_width)
			{
				map[i][j] = new_symbol;
				j++;
			}
		}
		k++;
		i++;
	}
	return (i);
}

char	**copy_map(t_pos *p, t_all *all)
{
	char	**new;
	int	i;
	char	new_symbol;

	new_symbol = '^';
	i = 0;
	new = (char **)ft_calloc(p->map_height + 3, sizeof(char *));
	new[i] = (char *)ft_calloc(p->map_width + 1, sizeof(char));
	ft_memset(new[i++], new_symbol, p->map_width);
	i = copy_all_map(p, new, i, all);
	map[i] = (char *)ft_calloc(p->map_width + 1, sizeof(char));
	ft_memset(new[i], new_symbol, p->map_width);
	return (new);
}

void	flood_fill(char **map, t_pos *p, int x, int y)
{
	char new_color;

	new_color = '*';
	if (x > 0 && x < p->map_width && y > 0 && y < (p->map_height + 2)
			&& (map[y][x] == ' ' || map[y][x] == '^'))
		write(1, "errro\n", 6);
	if (x >= 0 && x < p->map_width && y >= 0 && y < (p->map_height + 2)
			&& (map[y][x] == '0' || map[y][x] == '2'))
	{
		map[y][x] = new_color;
		flood_fill(map, p, x + 1, y);
		flood_fill(map, p, x - 1, y);
		flood_fill(map, p, x, y + 1);
		flood_fill(map, p, x, y - 1);
	}
}

void	free_new_map(t_pos *p, char **new_map)
{
	int i;

	i = 0;
	while (i < p->map_height + 2)
	{
		free(new_map[i]);
		i++;
	}
	free(new_map);
}

void	flood(t_pos *pos, t_all *all)
{
	int	i;
	int	j;
	char	**new_map;

	i = 1;
	pos->map_height = max_width_map(all->map);
	new_map = copy_map(pos, all);
	while (new_map[i] && i < (pos->map_height + 2))
	{
		j = 0;
		while (new_map[i][j])
		{
			if (new_map[i][j] == '0' || new_map[i][j] == '2')
				flood_fill(new_map, pos, j, i);
			j++;
		}
		i++;
	}
	free_new_map(pos, new_map);
}

/*void	to_zero(t_all *all, t_pos *p)
{
	int i;
	int j;

	i = 0;
	while (all->map[i])*/ // непонятно надо посмотреть
