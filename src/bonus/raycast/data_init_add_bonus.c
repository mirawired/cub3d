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
			found = 1;
			raydata->arg->fmap[i][j] = 0;
		}
		j++;
	}
	return (found);
}
