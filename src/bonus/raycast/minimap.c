/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 10:05:29 by corecaps          #+#    #+#             */
/*   Updated: 2023/10/03 16:05:08 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

void	mini_spr(t_raydata *raydata, t_map map, int i, int j)
{
	int	k;

	k = 0;
	while (k < SPRITENBR)
	{
		if (j == (int) raydata->spr->sprite[k].x
			&& i == (int) raydata->spr->sprite[k].y)
		{
			fill_rectangle(raydata, map.nmi_color, (t_point){(double)
				(j * map.grid_size_x + (double)map.grid_size_x / 3)
				+ OFFSET_MAP_X, (double)(i * map.grid_size_y
					+ (double)map.grid_size_y / 3) + OFFSET_MAP_Y},
				(t_point){(double)((j + 1) * map.grid_size_x
					- (double)map.grid_size_x / 3) + OFFSET_MAP_X,
				(double)((i + 1) * map.grid_size_y
					- (double)map.grid_size_y / 3) + OFFSET_MAP_Y});
		}
		k++;
	}
}

void	comp_minimap(t_raydata *raydata, t_map map, int i)
{
	int	j;

	j = 0;
	while (j < raydata->map_width)
	{
		if (raydata->map[i][j] == 1)
		{
			fill_rectangle(raydata, map.grid_color, (t_point)
			{(double)(j * map.grid_size_x) + OFFSET_MAP_X,
				(double)(i * map.grid_size_y) + OFFSET_MAP_Y},
				(t_point){(double)((j + 1) * map.grid_size_x) + OFFSET_MAP_X,
				(double)((i + 1) * map.grid_size_y) + OFFSET_MAP_Y});
		}
		mini_spr(raydata, map, i, j);
		j++;
	}
}

void	draw_minimap(t_raydata *raydata)
{
	t_map	map;
	int		i;

	i = 0;
	map.grid_size_x = MAP_WIDTH / (raydata->map_width);
	map.grid_size_y = MAP_HEIGHT / (raydata->map_height);
	map.grid_color.s_rgb.r = (char) 255;
	map.grid_color.s_rgb.g = (char) 0;
	map.grid_color.s_rgb.b = (char) 0;
	map.nmi_color.color = 0xFFFF00;
	while (i < raydata->map_height)
	{
		comp_minimap(raydata, map, i);
		i++;
	}
}