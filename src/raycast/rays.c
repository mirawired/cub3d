/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:55:55 by jgarcia           #+#    #+#             */
/*   Updated: 2023/09/30 22:18:58 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/raycast.h"

void	draw_slice(t_raydata *data, t_r *r, int x)
{
	float		texture_step;
	float		texture_pos;
	int			y;
	t_texture	*texture;
	t_color		color;

	texture = data->texture[r->texture_index];
	texture_step = 1.0 * texture->height / (r->drawEnd - r->drawStart);
	y = 0;
	while (y++ < r->drawStart)
		my_mlx_pixel_put(data->img_buffer, data->ceil_color,
			(t_int_point){x, y});
	texture_pos = 0;
	r->wall_x *= texture->width;
	while (y < r->drawEnd)
	{
		set_color(&color, texture, texture_pos, r);
		my_mlx_pixel_put(data->img_buffer, color, (t_int_point){x, y});
		y++;
		texture_pos += texture_step;
	}
	while (y++ < HEIGHT)
		my_mlx_pixel_put(data->img_buffer, data->floor_color,
			(t_int_point){x, y});
}

void	draw_rays(t_raydata *data)
{
	t_r	*r;
	int	x;

	x = 0;
	r = r_init(data);
	while (x < WIDTH)
	{
		r->cameraX = 2 * x / (double) WIDTH - 1;
		r->ray_dir.x = data->player->dir_vector.x + data->player->plane_vector.x
			* r->cameraX;
		r->ray_dir.y = data->player->dir_vector.y + data->player->plane_vector.y
			* r->cameraX;
		r->MapX = (int)r->pos.x;
		r->MapY = (int)r->pos.y;
		r->deltaDist.x = fabs(1 / r->ray_dir.x);
		r->deltaDist.y = fabs(1 / r->ray_dir.y);
		r->hit = 0;
		ray_comp_1(r);
		ray_comp_2(data, r);
		ray_comp_3(r);
		draw_slice(data, r, x);
		x++;
	}
	free(r);
}

void	ray_comp_1(t_r *r)
{
	if (r->ray_dir.x < 0)
	{
		r->stepX = -1;
		r->sideDist.x = (r->pos.x - r->MapX) * r->deltaDist.x;
	}
	else
	{
		r->stepX = 1;
		r->sideDist.x = (r->MapX + 1.0 - r->pos.x) * r->deltaDist.x;
	}
	if (r->ray_dir.y < 0)
	{
		r->stepY = -1;
		r->sideDist.y = (r->pos.y - r->MapY) * r->deltaDist.y;
	}
	else
	{
		r->stepY = 1;
		r->sideDist.y = (r->MapY + 1.0 - r->pos.y) * r->deltaDist.y;
	}
}

void	ray_comp_2(t_raydata *data, t_r *r)
{
	while (r->hit == 0)
	{
		if (r->sideDist.x < r->sideDist.y)
		{
			r->sideDist.x += r->deltaDist.x;
			r->MapX += r->stepX;
			r->side = 0;
			r->ray_color = (t_color){0x0000FF};
		}
		else
		{
			r->sideDist.y += r->deltaDist.y;
			r->MapY += r->stepY;
			r->side = 1;
			r->ray_color = (t_color){0x00FF00};
		}
		if (data->map[r->MapY][r->MapX] > 0)
			r->hit = 1;
	}
	if (r->side == 0)
		r->perpWallDist = r->sideDist.x - r->deltaDist.x;
	else
		r->perpWallDist = r->sideDist.y - r->deltaDist.y;
	r->lineHeight = (int)(HEIGHT / r->perpWallDist);
}

void	ray_comp_3(t_r *r)
{
	r->drawStart = -r->lineHeight / 2 + HEIGHT / 2;
	if (r->drawStart < 0)
		r->drawStart = 0;
	r->drawEnd = r->lineHeight / 2 + HEIGHT / 2;
	if (r->drawEnd >= HEIGHT)
		r->drawEnd = HEIGHT - 1;
	if (r->side == 0)
		r->wall_x = r->pos.y + r->perpWallDist * r->ray_dir.y;
	else
		r->wall_x = r->pos.x + r->perpWallDist * r->ray_dir.x;
	r->wall_x -= floor((r->wall_x));
	if (r->side == 0)
	{
		if (r->ray_dir.x > 0)
			r->texture_index = WE;
		else
			r->texture_index = EA;
	}
	else
	{
		if (r->ray_dir.y > 0)
			r->texture_index = NO;
		else
			r->texture_index = SO;
	}
}
