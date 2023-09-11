/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:56:05 by jgarcia           #+#    #+#             */
/*   Updated: 2023/09/11 10:56:09 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/raycast.h"

void draw_minimap(t_raydata *raydata);

void nmi_ai(const t_raydata *raydata);

int render(t_raydata *raydata) {
	clear_buffer(raydata);
	draw_rays(raydata);
	draw_minimap(raydata);
	nmi_ai(raydata);
	draw_player(raydata);
	mlx_put_image_to_window(raydata->mlx,
							raydata->mlx_win,
							raydata->img_buffer->img,
							0, 0);
	return (0);
}

void nmi_ai(const t_raydata *raydata) {
	if (raydata->map[(int) raydata->spr->sprite[0].y]
		[(int) raydata->spr->sprite[0].x + 1] == 0)
		raydata->spr->sprite[0].x += 0.01;
	if (raydata->map[(int) raydata->spr->sprite[0].y + 1]
		[(int) raydata->spr->sprite[0].x] == 0)
		raydata->spr->sprite[0].y += 0.03;
	if (raydata->map[(int) raydata->spr->sprite[1].y]
		[(int) raydata->spr->sprite[1].x + 1] == 0)
		raydata->spr->sprite[1].x += 0.03;
	if (raydata->map[(int) raydata->spr->sprite[1].y + 1]
		[(int) raydata->spr->sprite[1].x] == 0)
		raydata->spr->sprite[1].y += 0.01;
	if (raydata->spr->sprite[0].x > raydata->map_width)
		raydata->spr->sprite[0].x = 0;
	if (raydata->spr->sprite[0].y > raydata->map_height)
		raydata->spr->sprite[0].y = 0;
	if (raydata->spr->sprite[1].x > raydata->map_width)
		raydata->spr->sprite[1].x = 0;
	if (raydata->spr->sprite[1].y > raydata->map_height)
		raydata->spr->sprite[1].y = 0;
}

void draw_minimap(t_raydata *raydata) {
	int grid_size_x = MAP_WIDTH / (raydata->map_width);
	int grid_size_y = MAP_HEIGHT / (raydata->map_height);
	t_color grid_color;
	grid_color.s_rgb.r = (char) 255;
	grid_color.s_rgb.g = (char) 0;
	grid_color.s_rgb.b = (char) 0;
//	for (int y = OFFSET_MAP_Y;
//		 y < MAP_HEIGHT + OFFSET_MAP_Y - grid_size_y; y += grid_size_y) {
//		draw_line(raydata, grid_color,
//				  (t_point) {
//						  (double) OFFSET_MAP_X,
//						  (double) y},
//				  (t_point) {
//						  (double) OFFSET_MAP_X +
//						  MAP_WIDTH,
//						  (double) y});
//	}
//	for (int x = OFFSET_MAP_X;
//		 x < MAP_WIDTH + OFFSET_MAP_X - grid_size_x; x += grid_size_x) {
//		draw_line(raydata, grid_color,
//				  (t_point) {(double) x, (double) OFFSET_MAP_Y},
//				  (t_point) {(double) x, (double) OFFSET_MAP_Y + MAP_HEIGHT});
//
//	}
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
			if (j == (int) raydata->spr->sprite[0].x && i == (int) raydata->spr->sprite[0].y) {
				fill_rectangle(raydata, nmi_color,
							   (t_point) {(double) (j * grid_size_x + (double) grid_size_x / 3) + OFFSET_MAP_X,
										  (double) (i * grid_size_y + (double) grid_size_y / 3) + OFFSET_MAP_Y},
							   (t_point) {(double) ((j + 1) * grid_size_x - (double) grid_size_x / 3) + OFFSET_MAP_X,
										  (double) ((i + 1) * grid_size_y - (double) grid_size_y / 3) + OFFSET_MAP_Y});
			}
			if (j == (int) raydata->spr->sprite[1].x && i == (int) raydata->spr->sprite[1].y) {
				fill_rectangle(raydata, nmi_color,
							   (t_point) {(double) (j * grid_size_x + (double) grid_size_x / 3 + OFFSET_MAP_X),
										  (double) (i * grid_size_y + (double) grid_size_y / 3 + OFFSET_MAP_Y)},
							   (t_point) {(double) ((j + 1) * grid_size_x - (double) grid_size_x / 3 + OFFSET_MAP_X),
										  (double) ((i + 1) * grid_size_y - (double) grid_size_y / 3) + OFFSET_MAP_Y});
			}
		}
	}
}
