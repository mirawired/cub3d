/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:55:34 by jgarcia           #+#    #+#             */
/*   Updated: 2023/10/10 21:26:51 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/raycast.h"

/* **************************************************************************
 * calc_point:
 * - determine the position of a point from a starting point, an angle
 * and a distance.
 ************************************************************************** */

t_point	calc_point(t_point from, double angle, double distance)
{
	t_point	result;

	result.x = from.x + cos(angle) * distance;
	result.y = from.y + sin(angle) * distance;
	return (result);
}

/* **************************************************************************
 * clamp:
 * - clamp a point to the map.
 ************************************************************************** */

t_point	clamp(t_point point, t_raydata *raydata)
{
	t_point	result;

	result.x = point.x;
	result.y = point.y;
	result.x = (result.x / WIDTH) * (MAP_WIDTH / raydata->map_width)
		* raydata->map_width + OFFSET_MAP_X;
	result.y = (result.y / HEIGHT) * (MAP_HEIGHT / raydata->map_height)
		* raydata->map_height + OFFSET_MAP_Y;
	return (result);
}

/* **************************************************************************
 * draw_player:
 * - draw the player on the map.
 ************************************************************************** */

void	draw_player(t_raydata *raydata)
{
	t_draw_player	d;

	d.player_color.color = 0xFFFFFF;
	d.player_pos.x = raydata->player->pos.x;
	d.player_pos.y = raydata->player->pos.y;
	d.player_angle = raydata->player->angle * RADIAN;
	d.left = calc_point(d.player_pos, d.player_angle + 90
			* RADIAN, raydata->player->size);
	d.right = calc_point(d.player_pos, d.player_angle - 90
			* RADIAN, raydata->player->size);
	d.front = calc_point(d.player_pos, d.player_angle,
			raydata->player->size * 2);
	d.front = clamp(d.front, raydata);
	d.left = clamp(d.left, raydata);
	d.right = clamp(d.right, raydata);
	draw_line(raydata, d.player_color, d.left, d.front);
	draw_line(raydata, d.player_color, d.right, d.front);
}
