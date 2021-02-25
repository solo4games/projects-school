
#include "cub3D.h"
#include "./source/libft/libft.h"

int	open_file(char *file)
{
	int fd;

	if ((fd = open(file, O_RDONLY)) < 0)
	{
		clone(fd);
		fd = -1;
	}
	return (fd);
}

t_list	*file_read(int fd)
{
	char	*line;
	t_list	*list;
	int	i;

	line = NULL:
	list = NULL;
	while ((i = get_next_line(fd, &line)) > 0)
		ft_lstaddback(&list, ft_lstnew(line));
	ft_lstaddback(&list, ft_lstnew(line));
	if (i < 0)
		return (NULL);
	return(list);
}
