/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horiz.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:00:59 by avassor           #+#    #+#             */
/*   Updated: 2023/10/10 12:11:43 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/raycast.h"

void	draw_horiz(t_raydata *data, t_point pos, int grid_size_x, int grid_size_y)
{
	t_h	h;
	int	x;
	int	y;
	t_color color;

	y = 1;
	while (y < HEIGHT)
	{
		h.raydirx0 = data->player->dir_vector.x - data->player->plane_vector.x;
		h.raydiry0 = data->player->dir_vector.y - data->player->plane_vector.y;
		h.raydirx1 = data->player->dir_vector.x + data->player->plane_vector.x;
		h.raydiry1 = data->player->dir_vector.y + data->player->plane_vector.y;
		h.p = y - HEIGHT / 2;
		h.posz = 0.5 * HEIGHT;
		h.rawdist = h.posz / h.p;
		h.floorstepx = h.rawdist * (h.raydirx1 - h.raydirx0) / WIDTH;
		h.floorstepy = h.rawdist * (h.raydiry1 - h.raydiry0) / WIDTH;
		h.floorx = pos.x + h.rawdist * h.raydirx0;
		h.floory = pos.y + h.rawdist * h.raydiry0;
		x = 1;
		while (x < WIDTH)
		{
			h.cellx = (int)h.floorx;
			h.celly = (int)h.floory;
			h.tx = (int)(data->texture[FLOOR]->width * (h.floorx - h.cellx)) & (data->texture[FLOOR]->width - 1);
			h.ty = (int)(data->texture[FLOOR]->height * (h.floory - h.celly)) & (data->texture[FLOOR]->height - 1);
			h.floorx += h.floorstepx;
			h.floory += h.floorstepy;
			color = data->texture[FLOOR]->texture[data->texture[FLOOR]->width * h.ty + h.tx];
			color.color = (color.color >> 1) & 8355711;
			my_mlx_pixel_put(data->img_buffer, color, (t_int_point){x, y});
			color = data->texture[CEIL]->texture[data->texture[CEIL]->width * h.ty + h.tx];
			color.color = (color.color >> 1) & 8355711;
			my_mlx_pixel_put(data->img_buffer, color, (t_int_point){x, HEIGHT - y - 1});
			x++;
		}
		y++;
	}
}
