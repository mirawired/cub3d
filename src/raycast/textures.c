/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 10:04:46 by corecaps          #+#    #+#             */
/*   Updated: 2023/09/30 13:39:25 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	fill_texture_buffer(t_buffer *img, const t_texture *texture,
	const char *addr)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < texture->height)
	{
		x = 0;
		while (x < texture->width)
		{
			color = *(unsigned int *)(addr + (y * (*img).line_length + x
						* ((*img).bit_per_pixel / 8)));
			texture->texture[y * texture->width + x].color = color;
			x ++;
		}
		printf("|");
		y ++;
	}
}

t_texture	*load_texture(t_raydata *raydata, char *path)
{
	t_buffer	img;
	t_texture	*texture;
	char		*addr;

	texture = gc_alloc(1, sizeof(t_texture));
	texture->width = 0;
	texture->height = 0;
	img.img = mlx_xpm_file_to_image(raydata->mlx, path,
			&texture->width, &texture->height);
	if (!img.img)
	{
		write(2, "Error\nTextures could not be loaded\n", 36);
		clean_exit(raydata);
	}
	texture->texture = gc_alloc(texture->width * texture->height,
			sizeof(t_color));
	addr = mlx_get_data_addr(img.img, &img.bit_per_pixel, &img.line_length,
			&img.endian);
	printf("Loading texture %s\t[", path);
	fill_texture_buffer(&img, texture, addr);
	mlx_destroy_image(raydata->mlx, img.img);
	printf("]\n");
	return (texture);
}
