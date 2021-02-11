/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 14:05:58 by lbrandy           #+#    #+#             */
/*   Updated: 2021/02/11 17:10:13 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "./source/libft/libft.h"

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

typedef struct	s_all
{
	t_win		*win;
	t_textures	*textures;
	t_pos		*pos;
	t_raycast	*raycast;
	t_draw		*draw;
	char		**map;
	int			count_params;
}				t_all;

void			ft_parse(t_list **list, t_all *all);
void			parse_map(t_list *list, t_all *all);
void			ft_skip(t_list **list);
void			my_pixel_put(t_win *win, int x, int y, int color);

#endif
