/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:55:55 by jgarcia           #+#    #+#             */
/*   Updated: 2023/10/10 21:20:27 by avassor          ###   ########.fr       */
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
	y = draw_start;
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
	double perpwalldist;
	t_texture_index texture_index;
	int grid_size_x = WIDTH / data->map_width;
	int grid_size_y = HEIGHT / data->map_height;
	t_point pos = {data->player->pos.x / grid_size_x, data->player->pos.y / grid_size_y};

	draw_horiz(data, pos);
	draw_horiz(data, pos);
	for (int x = 0; x < WIDTH; x++) {
		double camerax = 2 * x / (double) WIDTH - 1;
		t_point ray_dir = {data->player->dir_vector.x + data->player->plane_vector.x * camerax,
						   data->player->dir_vector.y + data->player->plane_vector.y * camerax};
		int mapx = (int) pos.x;
		int mapy = (int) pos.y;
		t_point sidedist;
		t_point deltadist = {fabs(1 / ray_dir.x), fabs(1 / ray_dir.y)};
		int stepx;
		int stepy;
		int hit = 0;
		int side;
		if (ray_dir.x < 0) {
			stepx = -1;
			sidedist.x = (pos.x - mapx) * deltadist.x;
		} else {
			stepx = 1;
			sidedist.x = (mapx + 1.0 - pos.x) * deltadist.x;
		}
		if (ray_dir.y < 0) {
			stepy = -1;
			sidedist.y = (pos.y - mapy) * deltadist.y;
		} else {
			stepy = 1;
			sidedist.y = (mapy + 1.0 - pos.y) * deltadist.y;
		}
		while (hit == 0) {
			if (sidedist.x < sidedist.y) {
				sidedist.x += deltadist.x;
				mapx += stepx;
				if (mapx < 0 || mapx >= data->map_width )
					break;
				side = 0;
			} else {
				sidedist.y += deltadist.y;
				mapy += stepy;
				if (mapy < 0 || mapy >= data->map_height)
					break;
				side = 1;
			}
			if (data->map[mapy][mapx] > 0)
				hit = 1;
		}
		if (side == 0)
			perpwalldist = sidedist.x - deltadist.x;
		else
			perpwalldist = sidedist.y - deltadist.y;
		int lineheight = (int) (HEIGHT / perpwalldist);
		int drawstart = -lineheight / 2 + HEIGHT / 2;
		if (drawstart < 0)
			drawstart = 0;
		int drawend = lineheight / 2 + HEIGHT / 2;
		if (drawend >= HEIGHT)
			drawend = HEIGHT - 1;
		double wall_x;
		if (side == 0) wall_x = pos.y + perpwalldist * ray_dir.y;
		else wall_x = pos.x + perpwalldist * ray_dir.x;
		wall_x -= floor((wall_x));
		if (side == 0) {
			if (ray_dir.x > 0) texture_index = WE;
			else texture_index = EA;
		} else {
			if (ray_dir.y > 0) texture_index = NO;
			else texture_index = SO;
		}
		draw_slice(data, texture_index, drawstart, drawend, x, wall_x, perpwalldist);
		data->spr->zbuffer[x] = perpwalldist;
	}
	clamp_sprites(data);
	draw_sprites(data, pos);
}
