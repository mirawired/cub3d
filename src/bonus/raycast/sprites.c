/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 12:36:22 by avassor           #+#    #+#             */
/*   Updated: 2023/10/10 19:11:34 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/raycast.h"

/* **************************************************************************
 * sort_sprites:
 * - Sorts the sprites by distance from the player.
 ************************************************************************** */

void	sort_sprites(t_spr	*spr, t_point pos)
{
	int	i;

	i = 0;
	while (i < SPRITENBR)
	{
		spr->sprite_order[i] = i;
		spr->sprite_dist[i] = ((pos.x - spr->sprite[i].x)
				* (pos.x - spr->sprite[i].x) + (pos.y - spr->sprite[i].y)
				* (pos.y - spr->sprite[i].y));
		i++;
	}
	i = 0;
	while (i < SPRITENBR)
	{
		if (spr->sprite_dist[i] < spr->sprite_dist[i + 1])
		{
			spr->sprite_order[i] = i + 1;
			spr->sprite_order[i + 1] = i;
			break ;
		}
		i++;
	}
}

/* **************************************************************************
 * comp_long:
 * - Computes the long values needed for the sprite calculations.
 ************************************************************************** */

void	comp_long(t_raydata *data, t_cs *cs)
{
	cs->inv_det = 1.0 / (data->player->plane_vector.x
			* data->player->dir_vector.y - data->player->dir_vector.x
			* data->player->plane_vector.y);
	cs->transx = cs->inv_det * (data->player->dir_vector.y * cs->spritex
			- data->player->dir_vector.x * cs->spritey);
	cs->transy = cs->inv_det * (-data->player->plane_vector.y * cs->spritex
			+ data->player->plane_vector.x + data->player->plane_vector.x
			* cs->spritey);
}

/* **************************************************************************
 * comp_sprites:
 * - Computes the values needed for the sprite calculations.
 ************************************************************************** */

void	comp_sprites(t_raydata *data, t_sprite *curr, t_point pos)
{
	t_cs	*cs;

	cs = &data->spr->cs;
	cs->spritex = curr->x - pos.x;
	cs->spritey = curr->y - pos.y;
	comp_long(data, cs);
	cs->sprite_screen_x = (int)((WIDTH / 2) * (1 + cs->transx / cs->transy));
	cs->v_move_screen = (int)(0.0 / cs->transy);
	cs->sprite_height = ft_abs((int)(HEIGHT / cs->transy)) / 1;
	cs->draw_start_y = -cs->sprite_height / 2 + HEIGHT / 2 + cs->v_move_screen;
	if (cs->draw_start_y < 0)
		cs->draw_start_y = 0;
	cs->draw_end_y = cs->sprite_height / 2 + HEIGHT / 2 + cs->v_move_screen;
	if (cs->draw_end_y >= HEIGHT)
		cs->draw_end_y = HEIGHT - 1;
	cs->sprite_width = ft_abs((int)(HEIGHT / cs->transy)) / 1;
	cs->draw_start_x = -cs->sprite_width / 2 + cs->sprite_screen_x;
	if (cs->draw_start_x < 0)
		cs->draw_start_x = 0;
	cs->draw_end_x = cs->sprite_width / 2 + cs->sprite_screen_x;
	if (cs->draw_end_x >= WIDTH)
		cs->draw_end_x = WIDTH;
	cs->stripe = cs->draw_start_x;
}

/* **************************************************************************
 * sprite_pxl:
 * - Draws the sprite pixels.
 ************************************************************************** */

void	sprite_pxl(t_raydata *data, t_cs *cs, t_sprite *curr)
{
	t_color	color;
	int		texx;
	int		texy;
	int		y;
	int		d;

	texx = (int)(256 * (cs->stripe - (-cs->sprite_width / 2
					+ cs->sprite_screen_x)) * 64 / cs->sprite_width) / 256;
	y = cs->draw_start_y;
	if (cs->transy > 0 && cs->transy < data->spr->zbuffer[cs->stripe])
	{
		while (y < cs->draw_end_y)
		{
			d = (y - cs->v_move_screen) * 256 - HEIGHT * 128
				+ cs->sprite_height * 128;
			texy = ((d * 64) / cs->sprite_height) / 256;
			color = curr->texture[data->spr->spr_i % 2]
				->texture[64 * texy + texx];
			if (color.color != BLACK)
				my_mlx_pixel_put(data->img_buffer, color,
					(t_int_point){cs->stripe, y});
			y++;
		}
	}
}

/* **************************************************************************
 * draw_sprites:
 * - Draws the sprites.
 ************************************************************************** */

void	draw_sprites(t_raydata *data, t_point pos)
{
	t_sprite	curr;
	t_spr		*spr;
	t_cs		*cs;
	int			i;

	i = 0;
	spr = data->spr;
	sort_sprites(spr, pos);
	spr->spr_i++;
	while (i < SPRITENBR)
	{
		curr = spr->sprite[spr->sprite_order[i]];
		comp_sprites(data, &curr, pos);
		cs = &spr->cs;
		while (cs->stripe < cs->draw_end_x)
		{
			sprite_pxl(data, cs, &curr);
			cs->stripe++;
		}
		i++;
	}
}
