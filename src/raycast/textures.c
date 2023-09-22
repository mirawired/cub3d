//
// Created by corecaps on 9/22/23.
//

#include "../../inc/cub3d.h"

void fill_texture_buffer(t_buffer *img, const t_texture *texture, const char *addr) {
	int	x;
	int	y;
	int color;

	y = 0;
	while (y < texture->height)
	{
		x = 0;
		while (x < texture->width)
		{
			color = *(unsigned int *)(addr + (y * (*img).line_length + x * ((*img).bit_per_pixel / 8)));
			texture->texture[y * texture->width + x].color = color;
			x ++;
		}
		printf("|");
		y ++;
	}
}

t_texture	*load_texture(void *mlx, char *path)
{
	t_buffer	img;
	t_texture	*texture;
	char		*addr;

	texture = gc_alloc(1,sizeof(t_texture));
	if (!texture)
		return (NULL);
	texture->width = 0;
	texture->height = 0;
	img.img = mlx_xpm_file_to_image(mlx, path, &texture->width, &texture->height);
	if (!img.img)
		return (NULL);
	texture->texture = gc_alloc( texture->width * texture->height,sizeof(t_color));
	addr = mlx_get_data_addr(img.img, &img.bit_per_pixel, &img.line_length, &img.endian);
	printf("Loading texture %s\t[", path);
	fill_texture_buffer(&img, texture, addr);
	mlx_destroy_image(mlx, img.img);
	printf("]\n");
	return (texture);
}