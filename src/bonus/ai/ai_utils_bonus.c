/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corecaps <corecaps@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:01:04 by corecaps          #+#    #+#             */
/*   Updated: 2023/10/10 13:01:08 by corecaps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

/* **************************************************************************
 * is_within_bounds:
 * - check if the point is within the map
 ************************************************************************** */

int	is_within_bounds(t_raydata *raydata, int x, int y)
{
	if (x < 1 || x >= raydata->map_width - 1
		|| y < 1 || y >= raydata->map_height - 1)
		return (0);
	return (1);
}

/* **************************************************************************
 * find_direction:
 * - find the direction of the next node of the path
 ************************************************************************** */

t_int_point	find_direction(t_raydata *raydata, int x, int y, t_int_point inc)
{
	t_int_point	direction;
	int			i;

	i = 1;
	while (is_within_bounds(raydata, x + i * inc.x, y + i * inc.y)
		&& raydata->map[y + i * inc.y][x + i * inc.x] == 0)
		i++;
	i --;
	direction.x = x + i * inc.x;
	direction.y = y + i * inc.y;
	return (direction);
}

/* **************************************************************************
 * find_inc:
 * - find the increment to move the sprite to the next node of the path
 ************************************************************************** */

int	find_inc(int dest, int src)
{
	int	result;

	result = ((dest - src) >> (sizeof(int) * 8 - 1)) | (!!((dest - src)));
	return (result);
}
