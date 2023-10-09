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

void	move_forward(t_raydata *raydata)
{
	t_point new_pos;
	new_pos.x = raydata->player->pos.x + 10 * cos(raydata->player->angle * RADIAN);
	new_pos.y = raydata->player->pos.y;
	if (!check_collision(raydata,new_pos))
	{
		raydata->player->pos.x = new_pos.x;
	}
	new_pos.x = raydata->player->pos.x;
	new_pos.y = raydata->player->pos.y + 10 * (sin(raydata->player->angle * RADIAN));
	if (!check_collision(raydata,new_pos))
	{
		raydata->player->pos.y = new_pos.y;
	}
	clamp_player(raydata);
}

void	move_backward(t_raydata *raydata)
{
	t_point new_pos;

	new_pos.x = raydata->player->pos.x - cos(raydata->player->angle * RADIAN) * 10;
	new_pos.y = raydata->player->pos.y;
	if (!check_collision(raydata,new_pos))
	{
		raydata->player->pos.x = new_pos.x;
	}
	new_pos.x = raydata->player->pos.x;
	new_pos.y = raydata->player->pos.y - sin(raydata->player->angle * RADIAN) * 10;
	if (!check_collision(raydata,new_pos))
	{
		raydata->player->pos.y = new_pos.y;
	}
	clamp_player(raydata);
}

void	turn_left(t_raydata *raydata)
{
	t_point	old_dir;
	t_point	old_plane;

	old_dir = raydata->player->dir_vector;
	old_plane = raydata->player->plane_vector;
	raydata->player->dir_vector.x = raydata->player->dir_vector.x
		* cos(-3 * RADIAN)
		- raydata->player->dir_vector.y * sin(-3 * RADIAN);
	raydata->player->dir_vector.y = old_dir.x * sin(-3 * RADIAN)
		+ raydata->player->dir_vector.y * cos(-3 * RADIAN);
	raydata->player->plane_vector.x = raydata->player->plane_vector.x
		* cos(-3 * RADIAN) - raydata->player->plane_vector.y
		* sin(-3 * RADIAN);
	raydata->player->plane_vector.y = old_plane.x * sin(-3 * RADIAN)
		+ raydata->player->plane_vector.y * cos(-3 * RADIAN);
	raydata->player->angle -= 3;
	if (raydata->player->angle < 0)
		raydata->player->angle = 359;
}

void	turn_right(t_raydata *raydata)
{
	t_point	old_dir;
	t_point	old_plane;

	old_dir = raydata->player->dir_vector;
	old_plane = raydata->player->plane_vector;
	raydata->player->dir_vector.x = raydata->player->dir_vector.x
		* cos(3 * RADIAN) - raydata->player->dir_vector.y * sin(3 * RADIAN);
	raydata->player->dir_vector.y = old_dir.x * sin(3 * RADIAN)
		+ raydata->player->dir_vector.y * cos(3 * RADIAN);
	raydata->player->plane_vector.x = raydata->player->plane_vector.x
		* cos(3 * RADIAN) - raydata->player->plane_vector.y * sin(3 * RADIAN);
	raydata->player->plane_vector.y = old_plane.x * sin(3 * RADIAN)
		+ raydata->player->plane_vector.y * cos(3 * RADIAN);
	raydata->player->angle += 3;
	if (raydata->player->angle > 359)
		raydata->player->angle = 0;
}
