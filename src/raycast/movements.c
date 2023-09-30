/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 10:04:15 by corecaps          #+#    #+#             */
/*   Updated: 2023/09/25 10:04:18 by corecaps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"


void move_forward(t_raydata *raydata) {
	raydata->player->pos.x += 10 * cos(raydata->player->angle * RADIAN);
	raydata->player->pos.y += 10 * (sin(raydata->player->angle * RADIAN));
	clamp_player(raydata);
}

void move_backward(t_raydata *raydata) {
	raydata->player->pos.x -= cos(raydata->player->angle * RADIAN) * 10;
	raydata->player->pos.y -= sin(raydata->player->angle * RADIAN) * 10;
	clamp_player(raydata);
}

void turn_left(t_raydata *raydata) {
	t_point old_dir;
	t_point old_plane;

	old_dir = raydata->player->dir_vector;
	old_plane = raydata->player->plane_vector;
	raydata->player->dir_vector.x =
			raydata->player->dir_vector.x * cos(-3 * RADIAN) -
			raydata->player->dir_vector.y * sin(-3 * RADIAN);
	raydata->player->dir_vector.y = old_dir.x * sin(-3 * RADIAN) +
									raydata->player->dir_vector.y *
									cos(-3 * RADIAN);
	raydata->player->plane_vector.x =
			raydata->player->plane_vector.x * cos(-3 * RADIAN) -
			raydata->player->plane_vector.y * sin(-3 * RADIAN);
	raydata->player->plane_vector.y = old_plane.x * sin(-3 * RADIAN) +
									  raydata->player->plane_vector.y *
									  cos(-3 * RADIAN);
	raydata->player->angle -= 3;
	if (raydata->player->angle < 0)
		raydata->player->angle = 359;
}

void turn_right(t_raydata *raydata) {
	t_point old_dir;
	t_point old_plane;

	old_dir = raydata->player->dir_vector;
	old_plane = raydata->player->plane_vector;
	raydata->player->dir_vector.x =
			raydata->player->dir_vector.x * cos(3 * RADIAN) -
			raydata->player->dir_vector.y * sin(3 * RADIAN);
	raydata->player->dir_vector.y = old_dir.x * sin(3 * RADIAN) +
									raydata->player->dir_vector.y *
									cos(3 * RADIAN);
	raydata->player->plane_vector.x =
			raydata->player->plane_vector.x * cos(3 * RADIAN) -
			raydata->player->plane_vector.y * sin(3 * RADIAN);
	raydata->player->plane_vector.y = old_plane.x * sin(3 * RADIAN) +
									  raydata->player->plane_vector.y *
									  cos(3 * RADIAN);
	raydata->player->angle += 3;
	if (raydata->player->angle > 359)
		raydata->player->angle = 0;
}
