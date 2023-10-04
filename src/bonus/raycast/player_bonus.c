/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:55:34 by jgarcia           #+#    #+#             */
/*   Updated: 2023/10/04 15:47:01 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/raycast.h"

t_point	calc_point(t_point from, double angle, double distance)
{
	t_point	result;

	result.x = from.x + cos(angle) * distance;
	result.y = from.y + sin(angle) * distance;
	return (result);
}

t_point	clamp(t_point point, t_raydata *raydata)
{
	t_point	result;

	result.x = point.x;
	result.y = point.y;
	// result.x = (result.x / WIDTH) * MAP_WIDTH + OFFSET_MAP_X;
	// result.y = (result.y / HEIGHT) * MAP_HEIGHT + OFFSET_MAP_Y;
	result.x = (result.x / WIDTH) * ((WIDTH / 4) / raydata->map_width) * raydata->map_width + OFFSET_MAP_X;
	result.y = (result.y / HEIGHT) * ((HEIGHT / 3) / raydata->map_height) * raydata->map_height + OFFSET_MAP_Y;
	if (result.x < OFFSET_MAP_X)
		result.x = OFFSET_MAP_X;
	if (result.x > OFFSET_MAP_X + MAP_WIDTH)
		result.x = OFFSET_MAP_X + MAP_WIDTH;
	if (result.y < OFFSET_MAP_Y)
		result.y = OFFSET_MAP_Y;
	if (result.y > OFFSET_MAP_Y + MAP_HEIGHT)
		result.y = OFFSET_MAP_Y + MAP_HEIGHT;
	return (result);
}

void	draw_player(t_raydata *raydata)
{
	t_color	player_color;
	t_point	player_pos;
	double	player_angle;
	t_point	front;
	t_point	left;
	t_point	right;

	player_color.color = 0xFFFFFF;
	player_pos.x = raydata->player->pos.x;
	player_pos.y = raydata->player->pos.y;
	player_angle = raydata->player->angle * RADIAN;
	left = calc_point(player_pos, player_angle + 90
			* RADIAN, raydata->player->size);
	right = calc_point(player_pos, player_angle - 90
			* RADIAN, raydata->player->size);
	front = calc_point(player_pos, player_angle, raydata->player->size * 2);
	front = clamp(front, raydata);
	left = clamp(left, raydata);
	right = clamp(right, raydata);
	draw_line(raydata, player_color, left, front);
	draw_line(raydata, player_color, right, front);
}

// 23/26
