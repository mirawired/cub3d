/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:55:17 by jgarcia           #+#    #+#             */
/*   Updated: 2023/09/11 10:55:26 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/raycast.h"

void clean_exit(t_raydata *raydata) {
	mlx_destroy_image(raydata->mlx, raydata->img_buffer->img);
	mlx_destroy_window(raydata->mlx, raydata->mlx_win);
	mlx_destroy_display(raydata->mlx);
	free(raydata->mlx);
	gc_free();
	exit(0);
}

int	key_pressed(int keycode, t_raydata *raydata) {
	if (keycode == 65307)
		clean_exit(raydata);
	if (keycode == 97 || keycode == 65361)
		turn_left(raydata);
	if (keycode == 100 || keycode == 65363)
		turn_right(raydata);
	if (keycode == 101)
		strafe_right(raydata);
	if (keycode == 113)
		strafe_left(raydata);
	if (keycode == 119 || keycode == 65362)
		move_forward(raydata);
	if (keycode == 115 || keycode == 65364)
		move_backward(raydata);
	return (0);
}


