/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:55:34 by jgarcia           #+#    #+#             */
/*   Updated: 2023/10/10 14:02:39 by corecaps         ###   ########.fr       */
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
	result.x = (result.x / WIDTH) * ((WIDTH / 4) / raydata->map_width)
		* raydata->map_width;
	result.y = (result.y / HEIGHT) * ((HEIGHT / 3) / raydata->map_height)
		* raydata->map_height;
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
