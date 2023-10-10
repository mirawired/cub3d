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
 * find_player:
 * - find the player in the map and set its position
 * - set the player's initial position
 * - return 1 if found, 0 if not
 ************************************************************************** */

int	find_player(t_raydata *raydata, int i, double gs_x, double gs_y)
{
	int	j;
	int	found;

	j = 0;
	found = 0;
	while (j < raydata->arg->width)
	{
		if (raydata->arg->fmap[i][j] < 0)
		{
			raydata->player->pos.x = (double) j * gs_x + gs_x / 2;
			raydata->player->pos.y = (double) i * gs_y + gs_y / 2;
			raydata->player->init_pos.x = raydata->player->pos.x;
			raydata->player->init_pos.y = raydata->player->pos.y;
			found = 1;
			raydata->arg->fmap[i][j] = 0;
		}
		j++;
	}
	return (found);
}

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
	raydata->player->angle = 0;
	raydata->player->size = 10;
	raydata->player->dir_vector.x = 1;
	raydata->player->dir_vector.y = 0;
	raydata->player->plane_vector.x = 0;
	raydata->player->plane_vector.y = 0.66;
}
