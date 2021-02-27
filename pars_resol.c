

#include "cub3D.h"
#include <stdio.h>

static int	count_res(char *s, int len)
{
	int i;
	int number;

	i = 0;
	if (len > 7)
		return (10000);
	while (s[i] == '0')
		i++;
	number = ft_atoi(&s[i]);
	if (number == 0)
		//error
	return (number);
}

void	skip_spaces(char **s)
{
	while (**s == ' ' && **s)
		(*s)++;
}

static int	len_number(char *temp)
{
	int len;

	len = 0;
	while (ft_isdigit(temp[len]))
		len++;
	return (len);
}

staic void	check_valid(char *resol)
{
	while (*resol)
	{
		if (!ft_isdigit(*resol) && *resol != ' ')
			return (0);
		resol++;
	}
	return (1);
}

void	pars_resol(char *resol, t_textures *text,int len)
{
	if (check_valid == 0)
		//error
	if (text->x != -1 && text->y != -1)
		//already full
	ft_skip_spaces(&resol);
	len = (len_number(&resol[len]);
	if (len < 8)
	{
		if (ft_isdigit(*resol))
			text->x = count_res(resol, len);
	}
	else
		text->x = 10000;
	while (ft_isdigit(*resol))
		resol++;
	ft_skip_spaces(&resol);
	len = (len_number(resol);
	if (len < 8)
	{
		if (ft_isdigit(*resol))
			text->y = count_res(resol, len);
	}
	else
		text->y = 10000;
	if (s[len] != '\0')
		//error
}
