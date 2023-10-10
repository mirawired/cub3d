/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:55:55 by jgarcia           #+#    #+#             */
/*   Updated: 2023/10/10 16:07:35 by avassor          ###   ########.fr       */
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
	texture_step = 1.0 * texture->height / (r->drawend - r->drawstart);
	y = 0;
	while (y++ < r->drawstart)
		my_mlx_pixel_put(data->img_buffer, data->ceil_color,
			(t_int_point){x, y});
	texture_pos = 0;
	r->wall_x *= texture->width;
	while (y < r->drawend)
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
		r->mapx = (int)r->pos.x;
		r->mapy = (int)r->pos.y;
		r->deltadist.x = fabs(1 / r->ray_dir.x);
		r->deltadist.y = fabs(1 / r->ray_dir.y);
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
		r->stepx = -1;
		r->sidedist.x = (r->pos.x - r->mapx) * r->deltadist.x;
	}
	else
	{
		r->stepx = 1;
		r->sidedist.x = (r->mapx + 1.0 - r->pos.x) * r->deltadist.x;
	}
	if (r->ray_dir.y < 0)
	{
		r->stepy = -1;
		r->sidedist.y = (r->pos.y - r->mapy) * r->deltadist.y;
	}
	else
	{
		r->stepy = 1;
		r->sidedist.y = (r->mapy + 1.0 - r->pos.y) * r->deltadist.y;
	}
}

void	ray_comp_2(t_raydata *data, t_r *r)
{
	while (r->hit == 0)
	{
		if (r->sidedist.x < r->sidedist.y)
		{
			r->sidedist.x += r->deltadist.x;
			r->mapx += r->stepx;
			if (r->mapx < 0 || r->mapx >= data->map_width)
				break ;
			r->side = 0;
			r->ray_color = (t_color){0x0000FF};
		}
		else
		{
			r->sidedist.y += r->deltadist.y;
			r->mapy += r->stepy;
			if (r->mapy < 0 || r->mapy >= data->map_height)
				break ;
			r->side = 1;
			r->ray_color = (t_color){0x00FF00};
		}
		if (data->map[r->mapy][r->mapx] > 0)
			r->hit = 1;
	}
	if (r->side == 0)
		r->perpwalldist = r->sidedist.x - r->deltadist.x;
	else
		r->perpwalldist = r->sidedist.y - r->deltadist.y;
	r->lineheight = (int)(HEIGHT / r->perpwalldist);
}

void	ray_comp_3(t_r *r)
{
	r->drawstart = -r->lineheight / 2 + HEIGHT / 2;
	if (r->drawstart < 0)
		r->drawstart = 0;
	r->drawend = r->lineheight / 2 + HEIGHT / 2;
	if (r->drawend >= HEIGHT)
		r->drawend = HEIGHT - 1;
	if (r->side == 0)
		r->wall_x = r->pos.y + r->perpwalldist * r->ray_dir.y;
	else
		r->wall_x = r->pos.x + r->perpwalldist * r->ray_dir.x;
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
