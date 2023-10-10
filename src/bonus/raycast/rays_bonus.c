/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:55:55 by jgarcia           #+#    #+#             */
/*   Updated: 2023/10/10 12:15:04 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/raycast.h"

void	draw_slice(t_raydata *data, int texture_index, int draw_start, int draw_end, int x, double wall_x, double dist)
{
	float		texture_step;
	float		texture_pos;
	int			y;
	t_texture	*texture;

	texture = data->texture[texture_index];
	texture_step = 1.0 * texture->height / (draw_end - draw_start);
	y = 0;
	while (y++ < draw_start) ;
	texture_pos = 0;
	wall_x *= texture->width;
	while (y < draw_end) {
		t_color color = texture->texture[(int) texture_pos * texture->width + (int) wall_x];
		color.s_rgb.r -= (int) dist;
		color.s_rgb.g -= (int) dist;
		color.s_rgb.b -= (int) dist;
		my_mlx_pixel_put(data->img_buffer, color, (t_int_point) {x, y});
		y++;
		texture_pos += texture_step;
	}
}

void draw_rays(t_raydata *data) {
	double perpWallDist;
	t_texture_index texture_index;
	int grid_size_x = WIDTH / data->map_width;
	int grid_size_y = HEIGHT / data->map_height;
	t_point pos = {data->player->pos.x / grid_size_x, data->player->pos.y / grid_size_y};

	draw_horiz(data, pos);
	for (int x = 0; x < WIDTH; x++) {
		double cameraX = 2 * x / (double) WIDTH - 1;
		t_point ray_dir = {data->player->dir_vector.x + data->player->plane_vector.x * cameraX,
						   data->player->dir_vector.y + data->player->plane_vector.y * cameraX};
		int MapX = (int) pos.x;
		int MapY = (int) pos.y;
		t_point sideDist;
		t_point deltaDist = {fabs(1 / ray_dir.x), fabs(1 / ray_dir.y)};
		int stepX;
		int stepY;
		int hit = 0;
		int side;
		if (ray_dir.x < 0) {
			stepX = -1;
			sideDist.x = (pos.x - MapX) * deltaDist.x;
		} else {
			stepX = 1;
			sideDist.x = (MapX + 1.0 - pos.x) * deltaDist.x;
		}
		if (ray_dir.y < 0) {
			stepY = -1;
			sideDist.y = (pos.y - MapY) * deltaDist.y;
		} else {
			stepY = 1;
			sideDist.y = (MapY + 1.0 - pos.y) * deltaDist.y;
		}
		while (hit == 0) {
			if (sideDist.x < sideDist.y) {
				sideDist.x += deltaDist.x;
				MapX += stepX;
				if (MapX < 0 || MapX >= data->map_width )
					break;
				side = 0;
			} else {
				sideDist.y += deltaDist.y;
				MapY += stepY;
				if (MapY < 0 || MapY >= data->map_height)
					break;
				side = 1;
			}
			if (data->map[MapY][MapX] > 0)
				hit = 1;
		}
		if (side == 0)
			perpWallDist = sideDist.x - deltaDist.x;
		else
			perpWallDist = sideDist.y - deltaDist.y;
		int lineHeight = (int) (HEIGHT / perpWallDist);
		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if (drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;
		double wall_x;
		if (side == 0) wall_x = pos.y + perpWallDist * ray_dir.y;
		else wall_x = pos.x + perpWallDist * ray_dir.x;
		wall_x -= floor((wall_x));
		if (side == 0) {
			if (ray_dir.x > 0) texture_index = WE;
			else texture_index = EA;
		} else {
			if (ray_dir.y > 0) texture_index = NO;
			else texture_index = SO;
		}
		draw_slice(data, texture_index, drawStart, drawEnd, x, wall_x, perpWallDist);
		data->spr->zbuffer[x] = perpWallDist;
	}
	clamp_sprites(data);
	draw_sprites(data, pos);
}
