/* ************************************************************************** */
/*                                                4                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 23:50:13 by jgarcia           #+#    #+#             */
/*   Updated: 2023/02/15 23:50:48 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/raycast.h"
t_color *load_texture(void *mlx, char *path)
{
    t_buffer img;
    int img_width;
    int img_height;

    img.img = mlx_xpm_file_to_image(mlx, path, &img_width, &img_height);
    if (!img.img)
        return (NULL);
    t_color *texture = malloc(sizeof(t_color) * img_width * img_height);
    if (!texture)
        return (NULL);
    char *addr = mlx_get_data_addr(img.img, &img.bit_per_pixel, &img.line_length, &img.endian);
    printf("Loading texture %s\t[", path);
    for (int y = 0; y < img_height; y++)
    {
        for (int x = 0; x < img_width; x++)
        {
            int color = *(unsigned int *)(addr + (y * img.line_length + x * (img.bit_per_pixel / 8)));
            texture[y * img_width + x].color = color;
        }
        printf("|");
    }
    printf("]\n");
    return (texture);
}

int raycast(t_arg *arg)
{
	t_raydata *raydata;

	raydata = malloc(sizeof (t_raydata));
	if (!raydata)
		return (1);
	raydata->img_buffer = malloc(sizeof(t_buffer));
	if (!raydata->img_buffer)
		return (1);
    raydata->mlx = NULL;
	raydata->mlx = mlx_init();
    raydata->mlx_win = mlx_new_window(raydata->mlx,TWIDTH,HEIGHT,"RAYCAST");
	raydata->img_buffer->img = mlx_new_image(raydata->mlx,
										  TWIDTH +  1,
										  HEIGHT + 1);
	raydata->img_buffer->address = mlx_get_data_addr(raydata->img_buffer->img,
												  &raydata->img_buffer->bit_per_pixel,
												  &raydata->img_buffer->line_length,
												  &raydata->img_buffer->endian);

    raydata->EA = load_texture(raydata->mlx,arg->EA);
    raydata->WE = load_texture(raydata->mlx,arg->WE);
    raydata->NO = load_texture(raydata->mlx,arg->NO);
    raydata->SO = load_texture(raydata->mlx,arg->SO);
    raydata->player = malloc(sizeof (t_player));
    int found = 0;
    double grid_size_x = (double) WIDTH / arg->width;
    double grid_size_y = (double) HEIGHT / arg->height;
    for (int i=0;i < arg->height;i++) {
        for (int j=0;j < arg->width;j++) {
            if (arg->fmap[i][j] < 0) {
                raydata->player->pos.x = (double) j * grid_size_x + grid_size_x / 2;
                raydata->player->pos.y = (double) i * grid_size_y + grid_size_y / 2;
                found = 1;
            }
        }
    }
    if (found == 0) {
        raydata->player->pos.x = (double) HEIGHT / 2;
        raydata->player->pos.y = (double) WIDTH / 2;
    }
    raydata->player->angle = 0;
    raydata->player->size = 10;
    raydata->player->dir_vector.x = 1;
    raydata->player->dir_vector.y = 0;
    raydata->player->plane_vector.x = 0;
    raydata->player->plane_vector.y = 0.66;
    raydata->map = arg->fmap;
    raydata->map_height = arg->height;
    raydata->map_width = arg->width;
    mlx_hook(raydata->mlx_win, 2, 1L << 0, key_pressed, raydata);
	mlx_loop_hook(raydata->mlx,render,raydata);
	mlx_loop(raydata->mlx);
	return (0);
}