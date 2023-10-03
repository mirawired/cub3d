/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 10:05:02 by corecaps          #+#    #+#             */
/*   Updated: 2023/10/03 14:57:14 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

void	nmi_ai(t_raydata *raydata)
{
	int			i;
	int			grid_size_x;
	int			grid_size_y;
	t_int_point	dest;

	i = 0;
	grid_size_x = WIDTH / (raydata->map_width);
	grid_size_y = HEIGHT / (raydata->map_height);
	while (i < SPRITENBR)
	{
		dest = bfs(raydata, (t_int_point){(int)(raydata->spr->sprite[i].x),
				(int)(raydata->spr->sprite[i].y)}, (t_int_point)
			{(int)(raydata->player->pos.x / grid_size_x),
				(int)(raydata->player->pos.y / grid_size_y)});
		if (dest.x == 0 && dest.y == 0)
			continue ;
		raydata->spr->sprite[i].x
			+= (dest.x - (int)raydata->spr->sprite[i].x) * 0.05;
		raydata->spr->sprite[i].y
			+= (dest.y - (int)raydata->spr->sprite[i].y) * 0.05;
		i++;
	}
}
