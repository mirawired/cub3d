/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horiz.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:00:59 by avassor           #+#    #+#             */
/*   Updated: 2023/10/08 17:15:13 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/raycast.h"

void	draw_horiz(t_raydata *data)
{
	t_h	h;
	int	x;
	int	y;
	t_color color;

	y = 0;
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
		h.floorx = data->player->pos.x + h.rawdist * h.raydirx0;
		h.floory = data->player->pos.y + h.rawdist * h.raydiry0;
		x = 0;
		while (x < WIDTH)
		{
			h.cellx = (int)h.floorx;
			h.celly = (int)h.floory;
			h.tx = (int)(data->texture[NO]->width * ((int)h.floorx - h.cellx) & (data->texture[NO]->width -1));
			h.ty = (int)(data->texture[NO]->height * ((int)h.floory - h.celly) & (data->texture[NO]->height -1));
			h.floorx += h.floorstepx;
			h.floory += h.floorstepy;
			color = data->texture[NO]->texture[data->texture[NO]->width * h.ty + h.tx];
			my_mlx_pixel_put(data->img_buffer, color, (t_int_point){x, y});
			x++;
		}
		y++;
	}
}
