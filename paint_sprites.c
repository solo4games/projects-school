/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 13:58:48 by lbrandy           #+#    #+#             */
/*   Updated: 2021/03/22 11:46:29 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	sprite->sprite_width = abs((int)(res->x * 0.66 / sprite->transform_y));
	sprite->draw_start_x = -sprite->sprite_width / 2 + sprite->sprite_screen_x;
	if (sprite->draw_start_x < 0)
		sprite->draw_start_x = 0;
	sprite->draw_end_x = sprite->sprite_width / 2 + sprite->sprite_screen_x;
	if (sprite->draw_end_x >= res->x)
		sprite->draw_end_x = res->x - 1;
}

void	calc_sprite(t_datasprite *sprite, int i, t_pos *pos, t_textures *res)
{
	sprite->sprite_x = sprite->sprites[i].x - pos->pos_x + 0.5;
	sprite->sprite_y = sprite->sprites[i].y - pos->pos_y + 0.5;
	sprite->inv_det = 1.0 / (pos->plane_x * pos->dir_y -
			pos->dir_x * pos->plane_y);
	sprite->transform_x = sprite->inv_det * (pos->dir_y *
			sprite->sprite_x - pos->dir_x * sprite->sprite_y);
	sprite->transform_y = sprite->inv_det * (-pos->plane_y *
			sprite->sprite_x + pos->plane_x * sprite->sprite_y);
	sprite->sprite_screen_x = (int)((res->x / 2) * (1 +
				sprite->transform_x / sprite->transform_y));
	sprite->sprite_height = abs((int)(res->x * 0.66 / sprite->transform_y));
	calculate_draw(sprite, res);
}

void	draw_sprite(t_datasprite *s, t_textures *r, t_datatext *t, t_all *all)
{
	int	y;
	int	d;

	while (s->stripe < s->draw_end_x)
	{
		s->tex_x = (int)(256 * (s->stripe - (-s->sprite_width / 2 +
		s->sprite_screen_x)) * s->tex_width / s->sprite_width) / 256;
		if (s->transform_y > 0 && s->stripe > 0 && s->stripe < r->x &&
				s->transform_y < s->z_buffer[s->stripe])
		{
			y = s->draw_start_y;
			while (y < s->draw_end_y)
			{
				d = y * 256 - r->y * 128 + s->sprite_height * 128;
				s->tex_y = ((d * s->tex_height) / s->sprite_height) / 256;
				s->color = (*(int *)(t->addr + ((s->tex_x + (s->tex_y *
										t->width)) * (t->bpp / 8))));
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
		draw_sprite(all->data_sprite, all->textures, all->s, all);
		i++;
	}
}
