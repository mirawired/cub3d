/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 10:05:29 by corecaps          #+#    #+#             */
/*   Updated: 2023/09/25 10:05:31 by corecaps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

void draw_minimap(t_raydata *raydata) {
	int grid_size_x = MAP_WIDTH / (raydata->map_width);
	int grid_size_y = MAP_HEIGHT / (raydata->map_height);
	t_color grid_color;
	grid_color.s_rgb.r = (char) 255;
	grid_color.s_rgb.g = (char) 0;
	grid_color.s_rgb.b = (char) 0;
	t_color nmi_color = {0xFFFF00};
	for (int i = 0; i < raydata->map_height; i++) {
		for (int j = 0; j < raydata->map_width; j++) {
			if (raydata->map[i][j] == 1) {
				fill_rectangle(raydata, grid_color,
							   (t_point) {(double) (j * grid_size_x) + OFFSET_MAP_X,
										  (double) (i * grid_size_y) + OFFSET_MAP_Y},
							   (t_point) {(double) ((j + 1) * grid_size_x) + OFFSET_MAP_X,
										  (double) ((i + 1) * grid_size_y) + OFFSET_MAP_Y});
			}
			for (int k = 0; k < SPRITENBR; k++) {
				if (j == (int) raydata->spr->sprite[k].x && i == (int) raydata->spr->sprite[k].y) {
					fill_rectangle(raydata, nmi_color,
								   (t_point) {(double) (j * grid_size_x + (double) grid_size_x / 3) + OFFSET_MAP_X,
											  (double) (i * grid_size_y + (double) grid_size_y / 3) + OFFSET_MAP_Y},
								   (t_point) {(double) ((j + 1) * grid_size_x - (double) grid_size_x / 3) + OFFSET_MAP_X,
											  (double) ((i + 1) * grid_size_y - (double) grid_size_y / 3) + OFFSET_MAP_Y});
				}
			}
		}
	}
}
