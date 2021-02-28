/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_2_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 15:16:36 by lbrandy           #+#    #+#             */
/*   Updated: 2021/02/28 17:19:57 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <math.h>
#include <stdio.h>

double posX;
double posY;
double dirX;
double dirY;
double planeX;
double planeY;

void draw_frame(t_all *all)
{
	int i;
	
	i = 0;
	mlx_clear_window(all->win->mlx, all->win->win);
	while (i < all->textures->x)
	{
		double cameraX = 2 * i / (double)all->textures->x - 1;
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;
		int mapX = (int)posX;
		int mapY = (int)posY;
		double sideDistX;
		double sideDistY;
		double deltaDistX;
		double deltaDistY;
		if (rayDirY == 0)
			deltaDistX = 0;
		else
			deltaDistX = (rayDirX == 0) ? 1 : fabs(1 / rayDirX);
		if (rayDirX == 0)
			deltaDistY = 0;
		else
			deltaDistY = (rayDirY == 0) ? 1 : fabs(1 / rayDirY);
		double perpWallDist;
		int stepX;
		int stepY;
		int hit = 0;
		int side;
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (all->map[mapX][mapY] == '1')
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - posY + (1 - stepY) / 2)  / rayDirY;
		int lineHeight = (int)(all->textures->y / perpWallDist);
		int drawStart = -lineHeight / 2 + all->textures->y / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + all->textures->y / 2;
		if (drawEnd >= all->textures->y)
			drawEnd = all->textures->y - 1;
		int color;
		if (rayDirX < 0 && side == 0)
			color = 0x00FF0000;
		if (rayDirX > 0 && side == 0)
			color = 0x0000FF00;
		if (rayDirY < 0 && side == 1)
		{
			color = 0x000000FF;
		}
		if (rayDirY > 0 && side == 1)
			color = 0x00FF0099;
		int j = 0;
		while (j < drawStart)
		{
			my_mlx_pixel_put(all, i, j, 0x00000000);
			j++;
		}
		while (j < drawEnd)
		{
			my_mlx_pixel_put(all, i, j, color);
			j++;
		}
		while (j < all->textures->y)
		{
			my_mlx_pixel_put(all, i, j, 0x00000000);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(all->win->mlx, all->win->win, all->win->img, 0, 0);
}

int drawing(int keycode, t_all *all)
{
	double oldDirX;
	double oldPlaneX;
	double moveSpeed = 0.05;
	double rotSpeed = 0.1;

	if (keycode == 13)
	{
		if (all->map[(int)(posX + dirX * moveSpeed)][(int)(posY)] == '0')
			posX += dirX * moveSpeed;
		if (all->map[(int)(posX)][(int)(posY + dirY * moveSpeed)] == '0')
			posY += dirY * moveSpeed;
	}
	if (keycode == 1)
	{
		if (all->map[(int)(posX - dirX * moveSpeed)][(int)(posY)] == '0')
			posX -= dirX * moveSpeed;
		if (all->map[(int)(posX)][(int)(posY - dirY * moveSpeed)] == '0')
			posY -= dirY * moveSpeed;
	}
	if (keycode == 124)
	{
		oldDirX = dirX;
		dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
		dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
		oldPlaneX = planeX;
		planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
		planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
	}
	if (keycode == 123)
	{
		oldDirX = dirX;
		dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
		dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
		oldPlaneX = planeX;
		planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
		planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
	}
	draw_frame(all);
	return(0);
}

void	raycasting(t_all *all)
{
	posX = all->pos->pos_x;
	posY = all->pos->pos_y;
	dirX = all->pos->dir_x;
	dirY = all->pos->dir_y;
	planeX = all->pos->plane_x;
	planeY = all->pos->plane_y;
	all->win = (t_win *)malloc(sizeof(t_win));
	all->win->mlx = mlx_init();
	all->win->win = mlx_new_window(all->win->mlx, all->textures->x, all->textures->y, "Cub3D");
	all->win->img = (char *)mlx_new_image(all->win->mlx, all->textures->x, all->textures->y);
    all->win->addr = (char *)mlx_get_data_addr(all->win->img, 
			&(all->win->bpp), &(all->win->length), &(all->win->endian));
	draw_frame(all);
	mlx_hook(all->win->win, 2, 1L<<0, &drawing, all);
	mlx_loop(all->win->mlx);
	/*for (int i = 0; i < all->textures->x)
	{
		double cameraX = 2 * i / (double)all->textures->x - 1;
		double raydirX = dirX + planeX * cameraX;
		double raydirY = dirY + planeY * cameraX;
		int mapX = (int)posX;
		int mapY = (int)posY;
		double sideDistX;
		double sideDistY;
		double deltaDistX;
		double deltaDistY;
		if (raydirY == 0)
			deltaDistX = 0;
		else
			deltaDistX = (rayDirX == 0) ? 1 : fabs(1 / rayDirX);
		if (raydirX == 0)
			deltaDistY = 0;
		else
			deltaDistY = (rayDirY == 0) ? 1 : fabs(1 / rayDirY);
		double perpWallDist;
		int stepX;
		int stepY;
		int hit = 0;
		int side;
		if (rayDirx < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}
		while (hit == 0)
		{
			if (sideDistX += sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (all->map[mapX][mapY] > 0)
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - posY + (1 - stepY) / 2)  / rayDirY;
		int lineHeight (int)(h / perpWallDist);
		int drawStart = -lineHeight / 2 + h / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2;
		if (drawEnd >= all->textures->y)
			drawEnd = all->textures->y - 1;
		int color;
		if (rayDirX < 0 && side == 0)
			color = 0x00FF0000;
		if (rayDirX > 0 && side == 0)
			color = 0x0000FF00;
		if (rayDirY < 0 && side == 1)
			color = 0x000000FF;
		if (rayDirY > 0 && side == 1)
			color = 0x00FF0099;
		int j = 0;
		while (j < drawStart)
		{
			my_mlx_pixel_put(all, i, j, 0x00000000);
			j++;
		}
		while (j < drawEnd)
		{
			my_mlx_pixel_put(all, i, j, color);
			j++;
		}
		while (j < all->textures->y)
		{
			my_mlx_pixel_put(all, i, j, 0x00000000);
			j++;
		}
	}*/
}
