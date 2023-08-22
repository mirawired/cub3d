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

int raycast(t_data *data, t_arg *arg)
{
	(void)data;
	(void)arg;
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
    raydata->player = malloc(sizeof (t_player));
	raydata->player->pos.x = (double)HEIGHT /2;
	raydata->player->pos.y = (double) WIDTH /2;
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