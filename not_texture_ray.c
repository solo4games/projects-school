/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_texture_ray.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 12:14:26 by lbrandy           #+#    #+#             */
/*   Updated: 2021/02/10 15:48:36 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./source/libft/libft.h"
#include "cub3D.h"
#include <stdio.h>
#include <math.h>
#include <mlx.h>

void	init_step(t_raycast *ray, t_pos *pos)
{
	if (ray->rayDir_x < 0)
	{
		ray->step_x = -1;
		ray->sideDist_x = (pos->pos_x - ray->map_x) * ray->deltaDist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sideDist_x = (ray->map_x + 1.0 - pos->pos_x) * ray->deltaDist_x;
	}
	if (ray->rayDir_y < 0)
	{
		ray->step_y = -1;
		ray->sideDist_y = (pos->pos_x - ray->map_x) * ray->deltaDist_x;
	}
	else
	{
		ray->step_y = 1;
		ray->sideDist_y = (ray->map_y + 1.0 - pos->pos_y) * ray->deltaDist_x;
	}
}

void	init_raycast(t_raycast *raycast, int x, int w, t_pos *pos)
{
	double temp;
	raycast->camera_x = 2 * x / (double)w - 1;
	temp = raycast->camera_x;
	raycast->rayDir_x = pos->dir_x + pos->plane_x * temp;
	raycast->rayDir_y = pos->dir_y + pos->plane_y * temp;
	raycast->map_x = (int)pos->pos_x;
	raycast->map_y = (int)pos->pos_y;
	if (raycast->rayDir_y == 0)
		raycast->deltaDist_x = 0;
	else
		raycast->deltaDist_x = (raycast->rayDir_x == 0) ? 1 : fabs(1 / raycast->rayDir_x);
	if (raycast->rayDir_x == 0)
                raycast->deltaDist_y = 0;
        else
                raycast->deltaDist_y = (raycast->rayDir_y == 0) ? 1 : fabs(1 / raycast->rayDir_y);
	raycast->hit = 0;
	raycast->wallDist = 0;
}

void	calc_DDA(t_raycast *ray, char** map)
{
	while (ray->hit == 0)
	{
		if (ray->sideDist_x < ray->sideDist_y)
		{
			ray->sideDist_x += ray->deltaDist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sideDist_y += ray->deltaDist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (map[ray->map_x][ray->map_y] == '1')
			ray->hit = 1;
	}
}

void	init_draw(t_draw *draw, t_raycast *r, t_all *all, t_pos *p)
{
	int height;
	int i;

	draw->color = 0;
	i = 0;
	height = all->textures->y;
	if (r->side == 0)
		r->wallDist = (r->map_x - p->pos_x + (1 - r->step_x) / 2) / r->rayDir_x;
	else
		r->wallDist = (r->map_y - p->pos_y + (1 - r->step_y) / 2) / r->rayDir_y;
	draw->line_h = (int)(height / r->wallDist);
	draw->start = -draw->line_h / 2 + height / 2;
	if (draw->start < 0)
		draw->start = 0;
	draw->end = draw->line_h / 2 + height / 2;
	if (draw->end >= height)
		draw->end = height - 1;
	if (all->pos->dir_x < 0 && r->side == 0)
		draw->color = 0x00FF0000;
	if (all->pos->dir_x > 0 && r->side == 0)
		draw->color = 0x0000FF00;
	if (all->pos->dir_y < 0 && r->side == 1)
                draw->color = 0x000000FF;
        if (all->pos->dir_y > 0 && r->side == 1)
                draw->color = 0x00FF0099;
	//if(r->side == 1)
	//	draw->color /= 2;
}

void	mlx_initialize(t_win *w, t_all *all)
{
	w->mlx = mlx_init();
	w->win = mlx_new_window(w->mlx, all->textures->x, all->textures->y, "Cub3D");
	w->img = mlx_new_image(w->mlx, all->textures->x, all->textures->y);
	w->addr = mlx_get_data_addr(w->img, &(w->bpp), &(w->length), &(w->endian));
}

int	drawing(int keycode, t_all *all)
{
	double old_dirx;
	double old_planex;

	old_dirx = 0;
	old_planex = 0;
	if (keycode == 13)
	{
		if(all->map[(int)(all->pos->pos_x + all->pos->dir_x * (all->draw->ms + 0.3))][(int)all->pos->pos_y] == '0')
			all->pos->pos_x += all->pos->dir_x * all->draw->ms;
		if(all->map[(int)(all->pos->pos_x)][(int)(all->pos->pos_y + all->pos->dir_y * (all->draw->ms + 0.3))] == '0')
			all->pos->pos_y += all->pos->dir_y * all->draw->ms;
	}
	if(keycode == 1)
	{
		if(all->map[(int)(all->pos->pos_x - all->pos->dir_x * (all->draw->ms + 0.01))][(int)all->pos->pos_y] == '0')
			all->pos->pos_x -= all->pos->dir_x * all->draw->ms;
		if(all->map[(int)(all->pos->pos_x)][(int)(all->pos->pos_y - all->pos->dir_y * (all->draw->ms + 0.01))] == '0')
			all->pos->pos_y -= all->pos->dir_y * all->draw->ms;//right +- left -+
	}
	if (keycode == 124)
	{
		old_dirx = all->pos->dir_x;
		old_planex = all->pos->plane_x;
		all->pos->dir_x = all->pos->dir_x * cos(-all->draw->rs) - all->pos->dir_y * sin(-all->draw->rs);
		all->pos->dir_y = old_dirx * sin(-all->draw->rs) + all->pos->dir_y * cos(-all->draw->rs);
		all->pos->plane_x = all->pos->plane_x * cos(-all->draw->rs) - all->pos->plane_y * sin(-all->draw->rs);
		all->pos->plane_y = old_planex * sin(-all->draw->rs) + all->pos->plane_y * cos(-all->draw->rs);
	}
	if (keycode == 123)
	{
		old_dirx = all->pos->dir_x;
		old_planex = all->pos->plane_x;
		all->pos->dir_x = all->pos->dir_x * cos(all->draw->rs) - all->pos->dir_y * sin(all->draw->rs);
		all->pos->dir_y = old_dirx * sin(all->draw->rs) + all->pos->dir_y * cos(all->draw->rs);
		all->pos->plane_x = all->pos->plane_x * cos(all->draw->rs) - all->pos->plane_y * sin(all->draw->rs);
		all->pos->plane_y = old_planex * sin(all->draw->rs) + all->pos->plane_y * cos(all->draw->rs);
	}
	draw_frame(all);
	return(0);
}

void	draw_frame(t_all *all)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < all->textures->x)
	{
		j = 0;
		init_raycast(all->raycast, i, (double)all->textures->x, all->pos);
		init_step(all->raycast, all->pos);
		calc_DDA(all->raycast, all->map);
		init_draw(all->draw, all->raycast, all, all->pos);
		while(j < all->draw->end - all->draw->start)
		{
			my_pixel_put(all->win, i, j, all->draw->color);
			j++;
		}
		i++;
	}
}

int close_window(int keycode, t_all *all)
{
	(void)keycode;
	mlx_destroy_window(all->win->mlx, all->win->win);
	return (0);
}


void	raycasting(t_all *all)
{
	int i;
	int j;

	i = 0;
	all->win = (t_win *)malloc(sizeof(t_win));
	all->raycast = (t_raycast *)malloc(sizeof(t_raycast));
	all->draw = (t_draw *)malloc(sizeof(t_draw));
	all->draw->ms = 0.15;
	all->draw->rs = 0.1;
	//mlx_initialize(all->win, all);
	//all->win->mlx = mlx_init();
	//all->win->win = mlx_new_window(all->win->mlx, all->textures->x, all->textures->y, "Cub3D");
	//all->win->img = mlx_new_image(all->win->mlx, all->textures->x, all->textures->y);
	//all->win->addr = mlx_get_data_addr(all->win->img, &(all->win->bpp), &(all->win->length), &(all->win->endian));	
	while (i < all->textures->x)
	{
		j = 0;
		init_raycast(all->raycast, i, all->textures->x, all->pos);
		init_step(all->raycast, all->pos);
		calc_DDA(all->raycast, all->map);
		init_draw(all->draw, all->raycast, all, all->pos);
		while(j < all->draw->end - all->draw->start)
		{
		//	printf("Here\n");
		//	my_pixel_put(all->win, i, j, all->draw->color);
			j++;
		}
		i++;
	}
	//mlx_hook(all->win->win, 3, 1L<<1, close_window, all);
	//mlx_loop(all->win->mlx);
}
