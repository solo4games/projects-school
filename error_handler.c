/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 15:40:37 by lbrandy           #+#    #+#             */
/*   Updated: 2021/03/17 16:03:22 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void		map_errors(int code)
{
	if (code == 0)
		write(2, "ERROR:\nminilibx error!\n", 23);
	else if (code == 1)
		write(2, "ERROR:\nmalloc error!\n", 21);
	else if (code == 2)
		write(2, "ERROR:\nincorrect resolution!\n", 28);
	else if (code == 3)
		write(2, "ERROR:\nnot correct path or extension of file!\n", 47);
	else if (code == 4)
		write(2, "ERROR:\nduplicate data!\n", 23);
	else if (code == 5)
		write(2, "ERROR:\nbad color!\n", 17);
	else if (code == 6)
		write(2, "ERROR:\ntrash in file!\n", 22);
	else if (code == 7)
		write(2, "ERROR:\nspaces in map!\n", 22);
	else if (code == 8)
		write(2, "ERROR:\nnot enough data!\n", 23);
	else if (code == 9)
		write(2, "ERROR:\nplayer not found\n", 24);
}

void			error_handler(int type_error, int code)
{
	if (type_error == 1)
		write(2, "ERROR:\nopening error!\n", 24);
	if (type_error == 2)
		write(2, "ERROR:\nreading error!\n", 24);
	if (type_error == 3)
		map_errors(code);
	if (type_error == 4)
		write(2, "ERROR:\nmlx library error!\n", 27);
	if (type_error == 5)
		write(2, "ERROR:\nargv error!\n", 20);
	if (type_error == 6)
		write(2, "ERROR:\ninvalid third argument\n", 31);
	exit(2);
}


