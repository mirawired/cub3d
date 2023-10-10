/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corecaps <corecaps@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:28:57 by corecaps          #+#    #+#             */
/*   Updated: 2023/10/10 13:29:01 by corecaps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

/* **************************************************************************
 * check_nm_collision:
 * - check if the player is on a sprite
 * - return 1 if true, 0 if false
 ************************************************************************** */

int	check_nmi_collision(t_raydata *raydata)
{
	t_int_point	player;
	t_point		grid_size;
	int			i;

	grid_size.x = WIDTH / raydata->map_width;
	grid_size.y = HEIGHT / raydata->map_height;
	player.x = (int)(raydata->player->pos.x / grid_size.x);
	player.y = (int)(raydata->player->pos.y / grid_size.y);
	i = 0;
	while (i < SPRITENBR)
	{
		if (player.x == (int)raydata->spr->sprite[i].x
			&& player.y == (int)raydata->spr->sprite[i].y)
			return (1);
		i++;
	}
	return (0);
}
