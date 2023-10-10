/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:55:05 by jgarcia           #+#    #+#             */
/*   Updated: 2023/10/09 12:42:31 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/raycast.h"

/* **************************************************************************
 * my_mlx_pixel_put:
 * - put a pixel in the image buffer
 * - if the pixel is in the map, make it darker
 ************************************************************************** */

int	my_mlx_pixel_put(t_buffer *data, t_color color, t_int_point coord)
{
	char	*dst;

	if (coord.x < 0 || coord.x > WIDTH || coord.y < 0 || coord.y > HEIGHT)
		return (-1);
	dst = data->address
		+ (coord.y * data->line_length + coord.x * (data->bit_per_pixel / 8));
	*(unsigned int *)dst = color.color;
	return (0);
}

/* **************************************************************************
 * ft_abs:
 * - return the absolute value of a number
 ************************************************************************** */

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

/* **************************************************************************
 * fill_rectangle:
 * - fill a rectangle in the image buffer
 ************************************************************************** */

void	fill_rectangle(t_raydata *raydata, t_color color, t_point top_left,
	t_point bottom_right)
{
	t_int_point	coord;

	coord.y = (int)(top_left.y);
	while (coord.y <= (int)(bottom_right.y))
	{
		coord.x = (int)(top_left.x);
		while (coord.x <= (int)(bottom_right.x))
		{
			my_mlx_pixel_put(raydata->img_buffer, color, coord);
			coord.x++;
		}
		coord.y++;
	}
}

/* **************************************************************************
 * clear_buffer:
 * - fill the image buffer with black
 ************************************************************************** */

void	clear_buffer(t_raydata *raydata)
{
	t_color		black;
	t_int_point	coord;
	int			y;
	int			x;

	black.color = 0;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			coord.x = x;
			coord.y = y;
			my_mlx_pixel_put(raydata->img_buffer, black, coord);
			x++;
		}
		y++;
	}
}
