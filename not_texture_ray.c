/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_texture_ray.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 12:14:26 by lbrandy           #+#    #+#             */
/*   Updated: 2021/03/06 17:18:03 by lbrandy          ###   ########.fr       */
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
		ray->sideDist_y = (pos->pos_y - ray->map_y) * ray->deltaDist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sideDist_y = (ray->map_y + 1.0 - pos->pos_y) * ray->deltaDist_y;
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

void	calc_DDA(t_raycast *ray, char** map, t_pos *p)
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
	printf("stepx - %d stepy - %d\n", ray->step_x, ray->step_y);
	if (ray->side == 0)
		ray->wallDist = (ray->map_x - p->pos_x + (1 - ray->step_x) / 2) / ray->rayDir_x;
	else
		ray->wallDist = (ray->map_y - p->pos_y + (1 - ray->step_y) / 2) / ray->rayDir_y;
}

void	init_draw(t_draw *draw, t_raycast *r, t_all *all, t_pos *p)
{
	int height;
	int i;

	draw->color = 0;
	i = 0;
	height = all->textures->y;
	draw->tex_width = 64;
	draw->tex_height = 64;
	draw->line_h = (int)(height / r->wallDist);
	draw->start = -draw->line_h / 2 + height / 2;
	if (draw->start < 0)
		draw->start = 0;
	draw->end = draw->line_h / 2 + height / 2;
	if (draw->end >= height)
		draw->end = height - 1;
	printf("start - %d end - %d\n; raydir_x - %f\n", draw->start, draw->end, all->pos->plane_x);
	if (r->side == 0)
		draw->wall_x = p->pos_y + r->wallDist * r->rayDir_y;
	else
		draw->wall_x = p->pos_x + r->wallDist * r->rayDir_x;
	draw->wall_x -= floor((draw->wall_x));
	draw->tex_x = (int)(draw->wall_x * (double)draw->tex_width);
	if (r->side == 0 && r->rayDir_x > 0)
		draw->tex_x = draw->tex_width - draw->tex_x - 1;
	if (r->side == 1 && r->rayDir_y < 0)
		draw->tex_x = draw->tex_width - draw->tex_x - 1;
	draw->step = 1.0 * draw->tex_height / draw->line_h;
	draw->tex_pos = (draw->start - height / 2 + draw->line_h / 2) * draw->step;
	/*if (all->raycast->rayDir_x < 0 && r->side == 0)
		draw->color = 0x00FF0000;
	if (all->raycast->rayDir_x > 0 && r->side == 0)
		draw->color = 0x0000FF00;
	if (all->raycast->rayDir_y < 0 && r->side == 1)
    	draw->color = 0x000000FF;
	if (all->raycast->rayDir_y > 0 && r->side == 1)
		draw->color = 0x00FF0099;*/
}

void	init_mlx(t_win *w, t_all *all)
{
	w->mlx = mlx_init();
	w->win = mlx_new_window(w->mlx, all->textures->x, all->textures->y, "Cub3D");
	w->img = (char *)mlx_new_image(w->mlx, all->textures->x, all->textures->y);
	w->addr = (char *)mlx_get_data_addr(w->img, &(w->bpp), &(w->length), &(w->endian));
}

int		drawing(int keycode, t_all *all)
{
	double old_dirx;
	double old_planex;

	old_dirx = 0;
	old_planex = 0;
	if (keycode == 13)//пофиксить заходы в стену
	{
		if(all->map[(int)(all->pos->pos_x + all->pos->dir_x * (all->draw->ms))][(int)all->pos->pos_y] == '0')
			all->pos->pos_x += all->pos->dir_x * all->draw->ms;
		if(all->map[(int)(all->pos->pos_x)][(int)(all->pos->pos_y + all->pos->dir_y * (all->draw->ms))] == '0')
			all->pos->pos_y += all->pos->dir_y * all->draw->ms;
	}
	if (keycode == 0)
	{
		if(all->map[(int)(all->pos->pos_x + all->pos->dir_x * (all->draw->ms))][(int)all->pos->pos_y] == '0')
			all->pos->pos_x -= all->pos->dir_y * all->draw->ms;
		if(all->map[(int)(all->pos->pos_x)][(int)(all->pos->pos_y + all->pos->dir_y * (all->draw->ms))] == '0')
			all->pos->pos_y += all->pos->dir_x * all->draw->ms;
	}
	if(keycode == 1)
	{
		if(all->map[(int)(all->pos->pos_x - all->pos->dir_x * (all->draw->ms))][(int)all->pos->pos_y] == '0')
			all->pos->pos_x -= all->pos->dir_x * all->draw->ms;
		if(all->map[(int)(all->pos->pos_x)][(int)(all->pos->pos_y - all->pos->dir_y * (all->draw->ms))] == '0')
			all->pos->pos_y -= all->pos->dir_y * all->draw->ms;
	}
	if (keycode == 2)
	{
		if(all->map[(int)(all->pos->pos_x + all->pos->dir_x * (all->draw->ms))][(int)all->pos->pos_y] == '0')
			all->pos->pos_x += all->pos->dir_y * all->draw->ms;
		if(all->map[(int)(all->pos->pos_x)][(int)(all->pos->pos_y + all->pos->dir_y * (all->draw->ms))] == '0')
			all->pos->pos_y -= all->pos->dir_x * all->draw->ms;
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
	mlx_clear_window(all->win->mlx, all->win->win);
	while (i < all->textures->x)
	{
		j = 0;
		init_raycast(all->raycast, i, all->textures->x, all->pos);
		init_step(all->raycast, all->pos);
		calc_DDA(all->raycast, all->map, all->pos);
		init_draw(all->draw, all->raycast, all, all->pos);
		while (j < all->draw->start)
		{
			my_mlx_pixel_put(all, i, j, 0x00000000);
			j++;
		}
		/*while (j < all->draw->end)
		{
			my_mlx_pixel_put(all, i, j, 0x00FF0000);
			j++;
		}*/
		draw_wall(all, all->draw, &j, i);
		while (j < all->textures->y)
		{
			my_mlx_pixel_put(all, i, j, 0x00000000);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(all->win->mlx, all->win->win, all->win->img, 0, 0);
}

void	draw_wall(t_all *all, t_draw *d, int *y, int x)
{
	while (*y < d->end)
	{
		d->tex_y = (int)d->tex_pos & (d->tex_height - 1);
		d->tex_pos += d->step;
		if (all->raycast->side == 0 && all->raycast->rayDir_x < 0)
			d->color = (*(int *)(all->SO->addr + (d->tex_x + d->tex_y *
							all->SO->width) * (all->SO->bpp / 8)));
		if (all->raycast->side == 0 && all->raycast->rayDir_x > 0)
			d->color = (*(int *)(all->EA->addr + (d->tex_x + d->tex_y *
							all->EA->width) * (all->EA->bpp / 8)));
		if (all->raycast->side == 1 && all->raycast->rayDir_y < 0)
			d->color = (*(int *)(all->NO->addr + (d->tex_x + d->tex_y *
							all->NO->width) * (all->NO->bpp / 8)));
		if (all->raycast->side == 1 && all->raycast->rayDir_y > 0)
			d->color = (*(int *)(all->WE->addr + (d->tex_x + d->tex_y *
							all->WE->width) * (all->WE->bpp / 8)));
		my_mlx_pixel_put(all, x, *y, d->color);
		(*y)++;
	}
}

void	raycasting(t_all *all)
{
	int i;

	i = 0;
	all->raycast = (t_raycast *)malloc(sizeof(t_raycast));
	all->draw = (t_draw *)malloc(sizeof(t_draw));
	all->draw->ms = 0.05;
	all->draw->rs = 0.1;
	draw_frame(all);
	mlx_hook(all->win->win, 2, 1L<<0, &drawing, all);
	mlx_loop(all->win->mlx);
}
