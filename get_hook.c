/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 10:35:49 by lbrandy           #+#    #+#             */
/*   Updated: 2021/03/21 13:10:03 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_press_but(int keycode, t_all *all)
{
	if (keycode == 13)
		all->hooks->key_w = 1;
	if (keycode == 0)
		all->hooks->key_a = 1;
	if (keycode == 1)
		all->hooks->key_s = 1;
	if (keycode == 2)
		all->hooks->key_d = 1;
	if (keycode == 53)
		all->hooks->key_esc = 1;
	if (keycode == 124)
		all->hooks->key_rot_right = 1;
	if (keycode == 123)
		all->hooks->key_rot_left = 1;
	all->hooks->flag = 1;
	return (0);
}

int	ft_release_but(int keycode, t_all *all)
{
	if (keycode == 13)
		all->hooks->key_w = 0;
	if (keycode == 0)
		all->hooks->key_a = 0;
	if (keycode == 1)
		all->hooks->key_s = 0;
	if (keycode == 2)
		all->hooks->key_d = 0;
	if (keycode == 53)
		all->hooks->key_esc = 0;
	if (keycode == 124)
		all->hooks->key_rot_right = 0;
	if (keycode == 123)
		all->hooks->key_rot_left = 0;
	if (all->hooks->key_rot_left == 0 && all->hooks->key_rot_left == 0 &&
			all->hooks->key_esc == 0 && all->hooks->key_d == 0 &&
			all->hooks->key_s == 0 && all->hooks->key_a == 0 &&
			all->hooks->key_w == 0)
	all->hooks->flag = 0;
	return (0);
}
