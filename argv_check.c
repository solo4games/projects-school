
#include "./source/libft/libft.h"
#include "cub3D.h"

int	argc_check(int argc)
{
	if (argc < 2)
	{
		write(2, "ERROR:Submit the map!\n", 24);
		return(0);
	}
	if (argc > 3)
	{
		write(2, "ERROR:too many arguments!\n", 27);
		return(0);
	}
	return (1);
}

int	file_check(char *map)
{
	char *temp;

	if (!map)
		return(0);
	if (ft_strlen(map) < 5)
		return(0);
	if (!(temp = ft_strrchr(map, '.')))
		return(0);
	if (ft_strlen(++temp) > 3)
		return(0);
	if (ft_strncmp("cub", temp, 3) == 0)
		return(1);
	return(0);
}

int	argv_check(int argc, char **argv)
{
	if (argc_chec(argc) == 0)
		return(0);
	if (argc > 1)
	{
		if (file_check(argv[1]) == 0)
			return(0);
		
	}
	return(1);
}
