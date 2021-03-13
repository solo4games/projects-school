/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:08:50 by lbrandy           #+#    #+#             */
/*   Updated: 2021/03/13 16:33:14 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	check_textures(t_textures *tex, int side)
{
	if (side == 1)
		if (tex->NO != NULL)
			write(1, "error\n", 6);
	if (side == 2)
		if (tex->SO != NULL)
			write(1, "error\n", 6);
	if (side == 3)
		if (tex->WE != NULL)
			write(1, "error\n", 6);
	if (side == 4)
		if (tex->EA != NULL)
			write(1, "error\n", 6);
	if (side == 5)
		if (tex->S != NULL)
			write(1, "error\n", 6);
}

void	check_xpm(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != ' ')
		i++;
	if (i < 5)
		write(1, "error\n", 6);
	if (ft_strncmp(".xpm", s[i - 4], 4) != 0)
		write(1, "error\n", 6);
}

void	pars_textures(t_textures *text, int side, char *s)
{
	int	i;

	i = 0;
	check_textures(all->textures, side);
	skip_spaces(&s);
	while (s[i] && s[i] != ' ')
		i++;
	if (s[i] != '\0')
		write(1, "error\n", 6);
	if (side == 1)
		text->NO = ft_substr(s, 0, i);
	if (side == 2)
		text->SO = ft_substr(s, 0, i);
	if (side == 3)
		text->WE = ft_substr(s, 0, i);
	if (side == 4)
		text->EA = ft_substr(s, 0, i);
	if (side == 5)
		text->S = ft_substr(s, 0, i);
}

