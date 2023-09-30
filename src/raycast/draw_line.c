/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:54:54 by jgarcia           #+#    #+#             */
/*   Updated: 2023/09/30 13:13:28 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/raycast.h"

/******************************************************************************
** Bresenham's line algorithm                                                 *
** https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm                 *
******************************************************************************/

void	do_neg(int *inc, int *delta_coord)
{
	*inc = -1;
	*delta_coord = -*delta_coord;
}

static void	draw_line_low(t_raydata *raydata, t_color color, t_point from,
	t_point to)
{
	int			y_inc;
	int			d;
	t_int_point	delta_coord;
	t_int_point	coord;

	delta_coord.x = (int)(to.x - from.x);
	delta_coord.y = (int)(to.y - from.y);
	y_inc = 1;
	if (delta_coord.y < 0)
		do_neg(&y_inc, &delta_coord.y);
	d = (2 * delta_coord.y) - delta_coord.x;
	coord.x = (int) from.x;
	coord.y = (int) from.y;
	while (coord.x <= (int)(to.x))
	{
		my_mlx_pixel_put(raydata->img_buffer, color, coord);
		if (d > 0)
		{
			coord.y += y_inc;
			d += 2 * (delta_coord.y - delta_coord.x);
		}
		else
			d += 2 * delta_coord.y;
		coord.x++;
	}
}

static void	draw_line_high(t_raydata *raydata, t_color color, t_point from,
	t_point to)
{
	int			x_inc;
	int			d;
	t_int_point	coord;
	t_int_point	delta_coord;

	delta_coord.x = (int)(to.x - from.x);
	delta_coord.y = (int)(to.y - from.y);
	x_inc = 1;
	if (delta_coord.x < 0)
		do_neg(&x_inc, &delta_coord.x);
	d = (2 * delta_coord.x) - delta_coord.y;
	coord.y = (int)(from.y);
	coord.x = (int)(from.x);
	while (coord.y <= (int)(to.y))
	{
		my_mlx_pixel_put(raydata->img_buffer, color, coord);
		if (d > 0)
		{
			coord.x += x_inc;
			d += 2 * (delta_coord.x - delta_coord.y);
		}
		else
			d += 2 * delta_coord.x;
		coord.y++;
	}
}

void	draw_line(t_raydata *raydata, t_color color, t_point from, t_point to)
{
	if (ft_abs((int)(to.y - from.y)) < ft_abs((int)(to.x - from.x)))
	{
		if (from.x > to.x)
			draw_line_low(raydata, color, to, from);
		else
			draw_line_low(raydata, color, from, to);
	}
	else
	{
		if (from.y > to.y)
			draw_line_high(raydata, color, to, from);
		else
			draw_line_high(raydata, color, from, to);
	}
}
