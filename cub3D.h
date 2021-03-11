/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 14:05:58 by lbrandy           #+#    #+#             */
/*   Updated: 2021/03/11 15:24:30 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "./source/libft/libft.h"
#include <mlx.h>
#include <stdio.h>
#include <math.h>

typedef struct	s_win
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			length;
	int 		endian;
}				  t_win;

typedef struct	s_draw
{
	int			line_h;
	int			start;
	int			end;
	int			color;
	int			tex_width;
	int			tex_height;
	double		wall_x;
	double		step;
	int			tex_x;
	int			tex_y;
	double		tex_pos;
	double		ms;
	double		rs;
}				t_draw;

typedef struct	s_raycast
{
	double		camera_x;
	double		rayDir_x;
	double		rayDir_y;
	int			map_x;
	int			map_y;
	double		sideDist_x;
	double		sideDist_y;
	double		deltaDist_x;
	double		deltaDist_y;
	double		wallDist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
}				t_raycast;

typedef struct	s_pos
{
	int			map_width;
	int			map_height;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		old_time;
	double		time;
}				t_pos;

typedef struct	s_textures
{
	int			x;
	int			y;
	char		*NO_texture;
	char		*SO_texture;
	char		*WE_texture;
	char		*EA_texture;
	char		*S_texture;
	int			F;
	int			C;
}				t_textures;

typedef struct	s_sprite
{
	double		x;
	double		y;
	double		dist;
}				t_sprite;

typedef struct	s_datasprite
{
	t_sprite	*sprites;
	int			count_sprites;
	double		sprite_x;
	double		sprite_y;
	double		inv_det;
	double		transform_x;
	double		transform_y;
	int			sprite_screen_x;
	int			tex_height;
	int			tex_width;
	int			sprite_height;
	int			sprite_width;
	int			draw_start_x;
	int			draw_start_y;
	int			draw_end_x;
	int			draw_end_y;
	int			stripe;
	int			tex_x;
	int			tex_y;
	int			color;
	double		*z_buffer;
}				t_datasprite;

typedef struct	s_datatext
{
	void		*img;
	char		*addr;
	int			bpp;
	int			length;
	int			endian;
	int			height;
	int			width;
}				t_datatext;

typedef struct	s_all
{
	t_datatext	*NO;
	t_datatext	*SO;
	t_datatext	*WE;
	t_datatext	*EA;
	t_datatext	*S;
	t_win		*win;
	t_textures	*textures;
	t_pos		*pos;
	t_raycast	*raycast;
	t_draw		*draw;
	t_datasprite	*data_sprite;
	char		**map;
	int			count_params;
}				t_all;

void			ft_parse(t_list **list, t_all *all);
void			parse_map(t_list *list, t_all *all);
void			ft_skip(t_list **list);
void			my_mlx_pixel_put(t_all *all, int x, int y, int color);
void			raycasting(t_all *all);
void			draw_frame(t_all *all);
int				check_map(char **map);
void			reading_textures(t_all *all);
void			draw_wall(t_all *all, t_draw *d, int *y, int x);
void			init_mlx(t_win *w, t_all *all);
void			draw_sprites(t_all *all);
void			draw_sprite(t_datasprite *s, t_textures *res, t_datatext *tex, t_all *all);
void			init_sprite(t_all *all);
void			calc_sprite(t_datasprite *sprite, int i, t_pos *pos, t_textures *res);
void			calculate_draw(t_datasprite *sprite, t_textures *res);
void			init_sprite_dist(t_datasprite *data_sprite, t_pos *pos);
void			bubble_sort(t_sprite *spr, int num);
void			array_of_sprites(t_all *all);
int				count_of_sprites(char **map);

#endif
