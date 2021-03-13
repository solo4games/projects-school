/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:38:42 by lbrandy           #+#    #+#             */
/*   Updated: 2021/03/13 17:06:03 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void		check_color(t_textures *tex, int type)
{
	if (type == 0)
		if (tex->F != -1)
			write(1, "error\n", 1);
	if (type == 1)
		if (tex->C != -1)
			write(1, "error\n", 1);
}

static void	skip(char **s, int flag)
{
	if (flag == 0)
		while ((**s < '0' || **s > '9') && **s)
			(*s)++;
	if (flag == 1)
		while (**s >= '0' && **s <= '9' && **s)
			(*s)++;
}

static void	color_init(char **s, int *count)
{
	int	color;

	color = ft_atoi(*s);
	skip(s, 1);
	skip(s, 0);
	(*count)++;
}

void		create_color(char *s, t_textures *tex, int *count, int type)
{
	int R;
	int G;
	int B;

	R = color_init(&s, count);
	G = color_init(&s, count);
	B = color_init(&s, count);
	if (type == 0)
		tex->F = R << 16 | G << 8 | B;
	if (type == 1)
		tex->C = R << 16 | G << 8 | B;
}


void		pars_colors(t_textures *tex, int type, char *s)
{
	int count;

	count = 0;
	check_color(tex, type);
	skip_spaces(&s);
	create_color(s, tex, &count, type);
	if (count != 3 || *s != '\0')
		write(1, "error\n", 6);
}
