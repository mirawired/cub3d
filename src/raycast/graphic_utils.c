/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:55:05 by jgarcia           #+#    #+#             */
/*   Updated: 2023/09/11 10:55:09 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/raycast.h"

int my_mlx_pixel_put(t_buffer *data, t_color color, t_int_point coord)
{
	char	*dst;
    if (coord.x < 0 || coord.x > WIDTH || coord.y < 0 || coord.y > HEIGHT)
        return (-1);
    if (coord.x > OFFSET_MAP_X && coord.x < OFFSET_MAP_X + MAP_WIDTH &&
        coord.y > OFFSET_MAP_Y && coord.y < OFFSET_MAP_Y + MAP_HEIGHT) {
        color.s_rgb.r /= 2;
        color.s_rgb.g /= 2;
        color.s_rgb.b /= 2;
    }
	dst = data->address + (coord.y * data->line_length + coord.x * (data->bit_per_pixel / 8));
	*(unsigned int*)dst = color.color;
	return (0);
}

int ft_abs(int n)
{
    if (n < 0)
        return (-n);
    return (n);
}

void fill_rectangle(t_raydata *raydata, t_color color, t_point top_left, t_point bottom_right)
{
    t_int_point coord;
    for (coord.y = (int)(top_left.y); coord.y <= (int)(bottom_right.y); coord.y++)
    {
        for (coord.x = (int)(top_left.x); coord.x <= (int)(bottom_right.x); coord.x++)
        {
            my_mlx_pixel_put(raydata->img_buffer, color, coord);
        }
    }
}

void	clear_buffer(t_raydata *raydata)
{
	t_color black;
	black.color = 0;
	for (int y = 0; y < HEIGHT; y ++)
	{
		for (int x = 0;x < WIDTH;x ++)
        {
            t_int_point coord = {x, y};
            my_mlx_pixel_put(raydata->img_buffer, black, coord);
        }
    }
}
