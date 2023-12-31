/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 10:04:15 by corecaps          #+#    #+#             */
/*   Updated: 2023/09/30 13:36:06 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/* **************************************************************************
 * move_forward:
 * - Moves the player forward.
 ************************************************************************** */

void	move_forward(t_raydata *raydata)
{
	raydata->player->pos.x = raydata->player->pos.x
		+ PLAYERSPEED * cos(raydata->player->angle * RADIAN);
	raydata->player->pos.y = raydata->player->pos.y + PLAYERSPEED
		* (sin(raydata->player->angle * RADIAN));
	clamp_player(raydata);
}

/* **************************************************************************
 * move_backward:
 * - Moves the player backward.
 ************************************************************************** */

void	move_backward(t_raydata *raydata)
{
	raydata->player->pos.x -= cos(raydata->player->angle
			* RADIAN) * 10;
	raydata->player->pos.y -= sin(raydata->player->angle
			* RADIAN) * 10;
	clamp_player(raydata);
}

/* **************************************************************************
 * turn_left:
 * - Turns the player left.
 ************************************************************************** */

void	turn_left(t_raydata *raydata)
{
	t_point	old_dir;
	t_point	old_plane;

	old_dir = raydata->player->dir_vector;
	old_plane = raydata->player->plane_vector;
	raydata->player->dir_vector.x = raydata->player->dir_vector.x
		* cos(-ROTSPEED * RADIAN)
		- raydata->player->dir_vector.y * sin(-ROTSPEED * RADIAN);
	raydata->player->dir_vector.y = old_dir.x * sin(-ROTSPEED * RADIAN)
		+ raydata->player->dir_vector.y * cos(-ROTSPEED * RADIAN);
	raydata->player->plane_vector.x = raydata->player->plane_vector.x
		* cos(-ROTSPEED * RADIAN) - raydata->player->plane_vector.y
		* sin(-ROTSPEED * RADIAN);
	raydata->player->plane_vector.y = old_plane.x * sin(-ROTSPEED * RADIAN)
		+ raydata->player->plane_vector.y * cos(-ROTSPEED * RADIAN);
	raydata->player->angle -= ROTSPEED;
	if (raydata->player->angle < 0)
		raydata->player->angle = 359;
}

/* **************************************************************************
 * turn_right:
 * - Turns the player right.
 ************************************************************************** */

void	turn_right(t_raydata *raydata)
{
	t_point	old_dir;
	t_point	old_plane;

	old_dir = raydata->player->dir_vector;
	old_plane = raydata->player->plane_vector;
	raydata->player->dir_vector.x = raydata->player->dir_vector.x
		* cos(ROTSPEED * RADIAN) - raydata->player->dir_vector.y
		* sin(ROTSPEED * RADIAN);
	raydata->player->dir_vector.y = old_dir.x * sin(ROTSPEED * RADIAN)
		+ raydata->player->dir_vector.y * cos(ROTSPEED * RADIAN);
	raydata->player->plane_vector.x = raydata->player->plane_vector.x
		* cos(ROTSPEED * RADIAN) - raydata->player->plane_vector.y
		* sin(ROTSPEED * RADIAN);
	raydata->player->plane_vector.y = old_plane.x * sin(ROTSPEED * RADIAN)
		+ raydata->player->plane_vector.y * cos(ROTSPEED * RADIAN);
	raydata->player->angle += ROTSPEED;
	if (raydata->player->angle > 359)
		raydata->player->angle = 0;
}
