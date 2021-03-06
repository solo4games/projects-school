
#include "cub3D.h"
#include "./source/libft/libft.h"

void	init_all_text(t_all *all, char *texname, t_datatext *tex);
{
	tex->img = mlx_xpm_file_to_image(all->win->mlx, texname, &tex->width, &tex->height);
	if (tex->img)
		tex->addr = (char *)mlx_get_data_addr(tex->img, &tex->bpp, &tex->length, &tex->endian);
	else
		printf("ERROR\");
	free(texname);
}

void	reading_textures(t_all *all)
{
	all->NO = (t_datatext *)(malloc(sizeof(t_datatext)));
	all->SO = (t_datatext *)(malloc(sizeof(t_datatext)));
	all->WE = (t_datatext *)(malloc(sizeof(t_datatext)));
	all->EA = (t_datatext *)(malloc(sizeof(t_datatext)));
	if (!all->NO || !all->SO || !all->WE || !all->EA)
		printf("ERROR\n");
	init_all_text(all, all->textures->NO_texture, all->NO);
	init_all_text(all, all->textures->SO_texture, all->NO);
	init_all_text(all, all->textures->WE_texture, all->WE);
	init_all_text(all, all->textures->EA_texture, all->EA);
}
