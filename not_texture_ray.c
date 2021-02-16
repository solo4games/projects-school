/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_texture_ray.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 12:14:26 by lbrandy           #+#    #+#             */
/*   Updated: 2021/02/16 14:55:43 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "./source/libft/libft.h"
#include "cub3D.h"
#include <stdio.h>
#include <math.h>

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
	raycast->deltaDist_x = (raycast->rayDir_y == 0)? 0: ((raycast->rayDir_x == 0)? 1: fabs(1 / raycast->rayDir_x));
	raycast->deltaDist_y = (raycast->rayDir_x == 0)? 0: ((raycast->rayDir_y == 0)? 1: fabs(1 / raycast->rayDir_y));
	raycast->hit = 0;
}

void	calc_DDA(t_raycast *ray, char** map)
{
	while (ray->hit == 0)
	{
		if (ray->sideDist_x >= ray->sideDist_y)
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
		if (map[ray->map_x][ray->map_y] > 0)
			ray->hit = 1;
	}
}

void	init_draw(t_draw *draw, t_raycast *r, t_all *all, t_pos *p)
{
	int height;
	int i;

	draw->color = 0x0000FF00;
	i = 0;
	height = all->textures->y;
	if (r->side == 0)
		r->wallDist = (r->map_x - p->pos_x + (1 - r->step_x) / 2) / r->rayDir_x;
	else
		r->wallDist = (r->map_y - p->pos_y + (1 - r->step_y) / 2) / r->rayDir_y;
	draw->line_h = (int)(height / r->wallDist);
	draw->start = -draw->line_h / 2 + height / 2;
	//printf("%f\n", r->wallDist);
	if (draw->start < 0)
		draw->start = 0;
	draw->end = draw->line_h / 2 + height / 2;
	if (draw->end >= height)
		draw->end = height - 1;
	//printf("end - %d, start - %d\n", draw->end, draw->start);
	if (all->pos->dir_x < 0 && all->pos->plane_y < 0)
		draw->color = 0x00FF0000;
	if(r->side == 1)
		draw->color /= 2;
}

void	init_mlx(t_win *w, t_all *all)
{
	w->mlx = mlx_init();
	w->win = mlx_new_window(w->mlx, all->textures->x, all->textures->y, "Cub3D");
	w->img = mlx_new_image(w->mlx, all->textures->x, all->textures->y);
	w->addr = mlx_get_data_addr(w->img, &(w->bpp), &(w->length), &(w->endian));
}

int		drawing(int keycode, t_all *all)
{
	double old_dirx;
	double old_planex;

	old_dirx = 0;
	old_planex = 0;
	if (keycode == 13)
	{
		if(all->map[(int)(all->pos->pos_x + all->pos->dir_x * all->draw->ms)][(int)all->pos->pos_y] == '0')
			all->pos->pos_x += all->pos->dir_x * all->draw->ms;
		if(all->map[(int)(all->pos->pos_x)][(int)(all->pos->pos_y + all->pos->dir_y * all->draw->ms)] == '0')
			all->pos->pos_y += all->pos->dir_y * all->draw->ms;
		/*if(all->map[(int)(p->pos_x + p->dir_x * all->draw->ms),(int)p->pos_y] == '0')
			p->pos_x += p->dir_x * all->draw->ms;
		if(all->map[(int)(p->pos_x), (int)(p->pos_y + p->dir_y * all->draw->ms)] == '0')
			p->pos_y += p->dir_y * all->draw->ms;*/
	}
	if(keycode == 1)
	{
		if(all->map[(int)(all->pos->pos_x - all->pos->dir_x * all->draw->ms)][(int)all->pos->pos_y] == '0')
			all->pos->pos_x -= all->pos->dir_x * all->draw->ms;
		if(all->map[(int)(all->pos->pos_x)][(int)(all->pos->pos_y - all->pos->dir_y * all->draw->ms)] == '0')
			all->pos->pos_y -= all->pos->dir_y * all->draw->ms;
		/*if(all->map[(int)(p->pos_x - p->dir_x * all->draw->ms),(int)p->pos_y] == '0')
			p->pos_x -= p->dir_x * all->draw->ms;
		if(all->map[(int)(p->pos_x), (int)(p->pos_y - p->dir_y * all->draw->ms)] == '0')
			p->pos_y -= p->dir_y * all->draw->ms;*/
	}
	if (keycode == 124)
	{
		old_dirx = all->pos->dir_x;
		old_planex = all->pos->plane_x;
		all->pos->dir_x = all->pos->dir_x * cos(-all->draw->rs) - all->pos->dir_y * sin(-all->draw->rs);
		all->pos->dir_y = old_dirx * sin(-all->draw->rs) + all->pos->dir_y * cos(-all->draw->rs);
		all->pos->plane_x = all->pos->plane_x * cos(-all->draw->rs) - all->pos->plane_y * sin(-all->draw->rs);
		all->pos->plane_y = old_planex * sin(-all->draw->rs) + all->pos->plane_y * cos(-all->draw->rs);
		/*old_dirx = p->dir_x;
		old_planex = p->plane_x;
		p->dir_x = p->dir_x * cos(-all->draw->rs) - p->dir_y * sin(-all->draw->rs);
		p->dir_y = old_dirx * sin(-all->draw->rs) + p->dir_y * cos(-all->draw->rs);
		p->plane_x = p->plane_x * cos(-all->draw->rs) - p->plane_y * sin(-all->draw->rs);
		p->plane_y = old_planex * sin(-all->draw->rs) + p->plane_y * cos(-all->draw->rs);*/
	}
	if (keycode == 123)
	{
		old_dirx = all->pos->dir_x;
		old_planex = all->pos->plane_x;
		all->pos->dir_x = all->pos->dir_x * cos(all->draw->rs) - all->pos->dir_y * sin(all->draw->rs);
		all->pos->dir_y = old_dirx * sin(all->draw->rs) + all->pos->dir_y * cos(all->draw->rs);
		all->pos->plane_x = all->pos->plane_x * cos(all->draw->rs) - all->pos->plane_y * sin(all->draw->rs);
		all->pos->plane_y = old_planex * sin(all->draw->rs) + all->pos->plane_y * cos(all->draw->rs);
		/*old_dirx = p->dir_x;
		old_planex = p->plane_x;
		p->dir_x = p->dir_x * cos(all->draw->rs) - p->dir_y * sin(all->draw->rs);
		p->dir_y = old_dirx * sin(all->draw->rs) + p->dir_y * cos(all->draw->rs);
		p->plane_x = p->plane_x * cos(all->draw->rs) - p->plane_y * sin(all->draw->rs);
		p->plane_y = old_planex * sin(all->draw->rs) + p->plane_y * cos(all->draw->rs);*/
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
		init_raycast(all->raycast, i, all->textures->x, all->pos);
		init_step(all->raycast, all->pos);
		calc_DDA(all->raycast, all->map);
		init_draw(all->draw, all->raycast, all, all->pos);
		while(j < all->draw->end - all->draw->start)
		{
			my_mlx_pixel_put(all, i, j, all->draw->color);
			j++;
		}
		i++;
	}
}

void	raycasting(t_all *all)
{
	int i;
	int j;

	i = 0;
	all->win = (t_win *)malloc(sizeof(t_win));
	all->raycast = (t_raycast *)malloc(sizeof(t_raycast));
	all->draw = (t_draw *)malloc(sizeof(t_draw));
	all->draw->ms = 0.1;
	all->draw->rs = 0.1;
	init_mlx(all->win, all);
	while (i < all->textures->x)
	{
		j = 0;
		init_raycast(all->raycast, i, all->textures->x, all->pos);
		init_step(all->raycast, all->pos);
		calc_DDA(all->raycast, all->map);
		init_draw(all->draw, all->raycast, all, all->pos);
		/*while(j < all->draw->end - all->draw->start)
		{
			my_mlx_pixel_put(all->win, i, j, 0x00FF0000);
			j++;
		}*/
		while (j < 100)
		{
			my_mlx_pixel_put(all, 100, 100, 0x00FF0000);
			j++;
		}
		printf("i - %d\n", i);
		i++;
	}
	mlx_put_image_to_window(all->win->mlx, all->win->win, all->win->img, 0, 0);
	mlx_hook(all->win->win, 2, 1L<<0, &drawing, all);
	mlx_loop(all->win->mlx);
}
