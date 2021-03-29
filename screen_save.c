/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_save.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 11:17:56 by lbrandy           #+#    #+#             */
/*   Updated: 2021/03/29 14:33:57 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define FILEHEADER 14
#define INFOHEADER 40
#include "cub3d.h"

static void		draw_screen(t_all *all, int argc)
{
	if (!(all->win = (t_win *)malloc(sizeof(t_win))))
		error_handler("malloc error\n");
	init_mlx(all->win, all, argc);
	reading_textures(all);
	init_sprite(all);
	all->raycast = (t_raycast *)malloc(sizeof(t_raycast));
	all->draw = (t_draw *)malloc(sizeof(t_draw));
	if (!all->raycast || !all->draw)
		error_handler("malloc error\n");
	draw_frame(all);
}

static void		create_file_header(t_all *all, int fd)
{
	unsigned char	*file_header;
	int				i;
	int				file_size;

	i = 0;
	file_header = (unsigned char *)malloc(FILEHEADER * sizeof(unsigned char));
	if (!file_header)
		error_handler("malloc error\n");
	while (i < FILEHEADER)
	{
		file_header[i] = (unsigned char)(0);
		i++;
	}
	file_size = FILEHEADER + INFOHEADER +
		(4 * all->textures->x * all->textures->y);
	file_header[0] = (unsigned char)('B');
	file_header[1] = (unsigned char)('M');
	file_header[2] = (unsigned char)(file_size % 256);
	file_header[3] = (unsigned char)(file_size / 256 % 256);
	file_header[4] = (unsigned char)(file_size / 256 / 256 % 256);
	file_header[5] = (unsigned char)(file_size / 256 / 256 / 256);
	file_header[10] = (unsigned char)(FILEHEADER + INFOHEADER);
	write(fd, file_header, FILEHEADER);
	free(file_header);
}

static void		create_info_header(t_all *all, int fd)
{
	unsigned char	*info_header;
	int				i;

	i = 0;
	info_header = (unsigned char *)malloc(INFOHEADER * sizeof(unsigned char));
	if (!info_header)
		error_handler("malloc error\n");
	while (i < INFOHEADER)
	{
		info_header[i] = (unsigned char)(0);
		i++;
	}
	info_header[0] = (unsigned char)(INFOHEADER);
	info_header[4] = (unsigned char)(all->textures->x % 256);
	info_header[5] = (unsigned char)(all->textures->x / 256 % 256);
	info_header[6] = (unsigned char)(all->textures->x / 256 / 256 % 256);
	info_header[7] = (unsigned char)(all->textures->x / 256 / 256 / 256);
	info_header[8] = (unsigned char)(all->textures->y % 256);
	info_header[9] = (unsigned char)(all->textures->y / 256 % 256);
	info_header[10] = (unsigned char)(all->textures->y / 256 / 256 % 256);
	info_header[11] = (unsigned char)(all->textures->y / 256 / 256 / 256);
	info_header[12] = (unsigned char)(1);
	info_header[14] = (unsigned char)(32);
	write(fd, info_header, INFOHEADER);
	free(info_header);
}

static void		put_image_in_bmp(t_all *all, int fd)
{
	int	y;
	int	line;

	line = all->textures->x * all->win->bpp / 8;
	y = all->textures->y;
	while (y >= 0)
	{
		write(fd, (unsigned char *)(all->win->addr + y * all->win->length),
				line);
		y--;
	}
}

void			screen_save(t_all *all, int argc)
{
	int fd;

	fd = open("screen.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0655);
	draw_screen(all, argc);
	create_file_header(all, fd);
	create_info_header(all, fd);
	put_image_in_bmp(all, fd);
	close(fd);
	write(1, "Screen generate!\n", 17);
	my_exit_from_game();
}
