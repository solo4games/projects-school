

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

