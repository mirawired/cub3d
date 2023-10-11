/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:55:55 by jgarcia           #+#    #+#             */
/*   Updated: 2023/10/11 10:38:49 by avassor          ###   ########.fr       */
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
	texture_step = 1.0 * texture->height / (r->draw_end - r->draw_start);
	y = 0;
	while (y++ < r->draw_start)
		my_mlx_pixel_put(data->img_buffer, data->ceil_color,
			(t_int_point){x, y});
	texture_pos = 0;
	r->wall_x *= texture->width;
	while (y < r->draw_end)
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
		r->camerax = 2 * x / (double) WIDTH - 1;
		r->ray_dir.x = data->player->dir_vector.x + data->player->plane_vector.x
			* r->camerax;
		r->ray_dir.y = data->player->dir_vector.y + data->player->plane_vector.y
			* r->camerax;
		r->map_x = (int)r->pos.x;
		r->map_y = (int)r->pos.y;
		r->delta_dist.x = fabs(1 / r->ray_dir.x);
		r->delta_dist.y = fabs(1 / r->ray_dir.y);
		r->hit = 0;
		ray_comp_1(r);
		ray_comp_2(data, r);
		ray_comp_3(r);
		draw_slice(data, r, x);
		x++;
	}
}

void	ray_comp_1(t_r *r)
{
	if (r->ray_dir.x < 0)
	{
		r->step_x = -1;
		r->side_dist.x = (r->pos.x - r->map_x) * r->delta_dist.x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist.x = (r->map_x + 1.0 - r->pos.x) * r->delta_dist.x;
	}
	if (r->ray_dir.y < 0)
	{
		r->step_y = -1;
		r->side_dist.y = (r->pos.y - r->map_y) * r->delta_dist.y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist.y = (r->map_y + 1.0 - r->pos.y) * r->delta_dist.y;
	}
}

void	ray_comp_2(t_raydata *data, t_r *r)
{
	while (r->hit == 0)
	{
		if (r->side_dist.x < r->side_dist.y)
		{
			ray_inc_h(r);
			if (r->map_x < 0 || r->map_x >= data->map_width)
				break ;
		}
		else
		{
			ray_inc_v(r);
			if (r->map_y < 0 || r->map_y >= data->map_height)
				break ;
		}
		if (data->map[r->map_y][r->map_x] > 0)
			r->hit = 1;
	}
	if (r->side == 0)
		r->perp_wall_dist = r->side_dist.x - r->delta_dist.x;
	else
		r->perp_wall_dist = r->side_dist.y - r->delta_dist.y;
	r->line_height = (int)(HEIGHT / r->perp_wall_dist);
}

void	ray_comp_3(t_r *r)
{
	r->draw_start = -r->line_height / 2 + HEIGHT / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_height / 2 + HEIGHT / 2;
	if (r->draw_end >= HEIGHT)
		r->draw_end = HEIGHT - 1;
	if (r->side == 0)
		r->wall_x = r->pos.y + r->perp_wall_dist * r->ray_dir.y;
	else
		r->wall_x = r->pos.x + r->perp_wall_dist * r->ray_dir.x;
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
