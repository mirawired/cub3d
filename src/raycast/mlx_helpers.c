/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corecaps </var/mail/corecaps>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 10:04:04 by corecaps          #+#    #+#             */
/*   Updated: 2023/09/25 10:04:07 by corecaps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void launch_game_loop(t_raydata *raydata) {
	mlx_hook(raydata->mlx_win, 2, 1L << 0, key_pressed, raydata);
	mlx_loop_hook(raydata->mlx,render,raydata);
	mlx_loop(raydata->mlx);
}

void init_mlx(t_raydata *raydata) {
	raydata->mlx = mlx_init();
	raydata->mlx_win = mlx_new_window(raydata->mlx,WIDTH,HEIGHT,"CUB3D");
	raydata->img_buffer->img = mlx_new_image(raydata->mlx,
											 WIDTH +  1,
											 HEIGHT + 1);
	raydata->img_buffer->address = mlx_get_data_addr(raydata->img_buffer->img,
													 &raydata->img_buffer->bit_per_pixel,
													 &raydata->img_buffer->line_length,
													 &raydata->img_buffer->endian);
}
