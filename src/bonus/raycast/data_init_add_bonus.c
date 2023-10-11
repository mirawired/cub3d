/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init_add_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 10:05:19 by corecaps          #+#    #+#             */
/*   Updated: 2023/10/03 15:40:35 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

/* **************************************************************************
 * data_reset:
 * - reset the player's position
 * - reset the sprite's position
 * - reset the player's vectors and angle
 ************************************************************************** */

void	data_reset(t_raydata *raydata)
{
	raydata->player->pos.x = raydata->player->init_pos.x;
	raydata->player->pos.y = raydata->player->init_pos.y;
	raydata->spr->sprite[0].x = 1.0;
	raydata->spr->sprite[0].y = 1.0;
	raydata->spr->sprite[1].x = raydata->map_width - 2;
	raydata->spr->sprite[1].y = 1.0;
	raydata->spr->sprite[2].x = 1.0;
	raydata->spr->sprite[2].y = raydata->map_height - 2;
	raydata->spr->sprite[3].x = raydata->map_width - 2;
	raydata->spr->sprite[3].y = raydata->map_height - 2;
	raydata->spr->spr_i = 0;
	raydata->player->angle = raydata->player->init_angle;
	raydata->player->size = 5;
	raydata->player->dir_vector.x = 1;
	raydata->player->dir_vector.y = 0;
	raydata->player->plane_vector.x = 0;
	raydata->player->plane_vector.y = 0.66;
	rotate_player(raydata, raydata->player->angle);
}

void	rotate_player(t_raydata *raydata, double angle)
{
	t_point	old_dir;
	t_point	old_plane;

	old_dir = raydata->player->dir_vector;
	old_plane = raydata->player->plane_vector;
	raydata->player->dir_vector.x = raydata->player->dir_vector.x
		* cos(angle * RADIAN)
		- raydata->player->dir_vector.y * sin(angle * RADIAN);
	raydata->player->dir_vector.y = old_dir.x * sin(angle * RADIAN)
		+ raydata->player->dir_vector.y * cos(angle * RADIAN);
	raydata->player->plane_vector.x = raydata->player->plane_vector.x
		* cos(angle * RADIAN) - raydata->player->plane_vector.y
		* sin(angle * RADIAN);
	raydata->player->plane_vector.y = old_plane.x * sin(angle * RADIAN)
		+ raydata->player->plane_vector.y * cos(angle * RADIAN);
}
