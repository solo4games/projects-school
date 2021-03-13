/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 13:58:48 by lbrandy           #+#    #+#             */
/*   Updated: 2021/03/13 15:41:31 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		count_of_sprites(char **map)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '2')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

void	array_of_sprites(t_all *all)
{
	int i;
	int j;
	int k;

	k = 0;
	i = 0;
	all->data_sprite->sprites = (t_sprite *)malloc(all->data_sprite->count_sprites * sizeof(t_sprite));
	while (i < all->pos->map_height && all->map[i])
	{
		j = 0;
		while (all->map[i][j])
		{
			if (all->map[i][j] == '2')
			{
				all->map[i][j] = 's';
				all->data_sprite->sprites[k].x = (double)i;
				all->data_sprite->sprites[k].y = (double)j;
				k++;
			}
			j++;
		}
		i++;
	}
}

void	bubble_sort(t_sprite *sprite, int num)
{
	int			i;
	int			sort;
	t_sprite	tmp;

	sort = 0;
	while (!sort)
	{
		i = 0;
		sort = 1;
		while (i < num - 1)
		{
			if (sprite[i].dist < sprite[i + 1].dist)
			{
				tmp = sprite[i];
				sprite[i] = sprite[i + 1];
				sprite[i + 1] = tmp;
				sort = 0;
			}
			i++;
		}
	}
}

void	init_sprite_dist(t_datasprite *data_sprite, t_pos *pos)
{
	int	i;
	
	i = 0;
	while (i < data_sprite->count_sprites)
	{
		data_sprite->sprites[i].dist = (pos->pos_x - data_sprite->sprites[i].x)
			* (pos->pos_x - data_sprite->sprites[i].x) + 
			(pos->pos_y - data_sprite->sprites[i].y) *
			(pos->pos_y - data_sprite->sprites[i].y);
		i++;
	}
	data_sprite->tex_width = 64;
	data_sprite->tex_height = 64;
}

void	calculate_draw(t_datasprite *sprite, t_textures *res)
{
	sprite->draw_start_y = -sprite->sprite_height / 2 + res->y / 2;
	if (sprite->draw_start_y < 0)
		sprite->draw_start_y = 0;
	sprite->draw_end_y = sprite->sprite_height / 2 + res->y / 2;
	if (sprite->draw_end_y >= res->y)
		sprite->draw_end_y = res->y - 1;
	sprite->sprite_width = abs((int)(res->y / sprite->transform_y));
	sprite->draw_start_x = -sprite->sprite_width / 2 + sprite->sprite_screen_x - 0.6;
	if (sprite->draw_start_x < 0)
		sprite->draw_start_x = 0;
	sprite->draw_end_x = sprite->sprite_width / 2 + sprite->sprite_screen_x - 0.6;
	if (sprite->draw_end_x >= res->x)
		sprite->draw_end_x = res->x - 1;
}

void	calc_sprite(t_datasprite *sprite, int i, t_pos *pos, t_textures *res)
{
	sprite->sprite_x = sprite->sprites[i].x - pos->pos_x + 0.5;
	sprite->sprite_y = sprite->sprites[i].y - pos->pos_y + 0.5;
	sprite->inv_det = 1.0 / (pos->plane_x * pos->dir_y - pos->dir_x * pos->plane_y);
	sprite->transform_x = sprite->inv_det * (pos->dir_y * sprite->sprite_x - pos->dir_x * sprite->sprite_y);
	sprite->transform_y = sprite->inv_det * (-pos->plane_y * sprite->sprite_x + pos->plane_x * sprite->sprite_y);
	sprite->sprite_screen_x = (int)((res->x / 2) * (1 + sprite->transform_x / sprite->transform_y));
	sprite->sprite_height = abs((int)(res->y / sprite->transform_y));
	calculate_draw(sprite, res);
}

void	init_sprite(t_all *all)
{
	all->data_sprite = (t_datasprite *)malloc(sizeof(t_datasprite));
	all->data_sprite->count_sprites = count_of_sprites(all->map);
	array_of_sprites(all);
	all->data_sprite->z_buffer = (double *)malloc((all->textures->x + 1) * sizeof(double));
}

void	draw_sprite(t_datasprite *s, t_textures *res, t_datatext *tex, t_all *all)
{
	int	y;
	int	d;

	while (s->stripe < s->draw_end_x)
	{
		s->tex_x = (int)(256 * (s->stripe - (-s->sprite_width / 2 +
		s->sprite_screen_x)) * s->tex_width / s->sprite_width) / 256;
		if (s->transform_y > 0 && s->stripe > 0 && s->stripe < res->x &&
				s->transform_y < s->z_buffer[s->stripe])
		{
			y = s->draw_start_y;
			while (y < s->draw_end_y)
			{
				d = y * 256 - res->y * 128 + s->sprite_height * 128;
				s->tex_y = ((d * s->tex_height) / s->sprite_height) / 256;
				s->color = (*(int *)(tex->addr + ((s->tex_x + (s->tex_y * 64)) * (tex->bpp / 8))));
				if ((s->color & 0x00FFFFFF) != 0)
					my_mlx_pixel_put(all, s->stripe, y, s->color);
				y++;
			}
		}
		s->stripe++;
	}
}

void	draw_sprites(t_all *all)
{
	int		i;

	i = 0;
	init_sprite_dist(all->data_sprite, all->pos);
	bubble_sort(all->data_sprite->sprites, all->data_sprite->count_sprites);
	while (i < all->data_sprite->count_sprites)
	{
		calc_sprite(all->data_sprite, i, all->pos, all->textures);
		all->data_sprite->stripe = all->data_sprite->draw_start_x;
		draw_sprite(all->data_sprite, all->textures, all->S, all);
		i++;
	}
}
