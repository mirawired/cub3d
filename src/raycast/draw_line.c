/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:54:54 by jgarcia           #+#    #+#             */
/*   Updated: 2023/09/11 10:54:57 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/raycast.h"

/*******************************************************************************
** Bresenham's line algorithm                                                  *
** https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm                  *
*******************************************************************************/
static void draw_line_low(t_raydata *raydata, t_color color, t_point from, t_point to)
{
    int y_inc;
    int D;
    t_int_point delta_coord;
    t_int_point coord;
    delta_coord.x = (int) (to.x - from.x);
    delta_coord.y = (int) (to.y - from.y);
    y_inc = 1;
    if (delta_coord.y < 0)
    {
        y_inc = -1;
        delta_coord.y = -delta_coord.y;
    }
    D = (2 * delta_coord.y) - delta_coord.x;
    for (coord.x = (int)from.x,coord.y = (int)from.y; coord.x <= (int)(to.x);coord.x++)
    {
        my_mlx_pixel_put(raydata->img_buffer, color, coord);
        if (D > 0)
        {
            coord.y += y_inc;
            D += 2 * (delta_coord.y - delta_coord.x);
        }
        else
            D += 2 * delta_coord.y;
    }
}

static void draw_line_high(t_raydata *raydata, t_color color, t_point from, t_point to)
{
    int x_inc;
    int D;
    t_int_point coord;
    t_int_point delta_coord;
    delta_coord.x = (int)(to.x - from.x);
    delta_coord.y = (int) (to.y- from.y);
    x_inc = 1;
    if (delta_coord.x < 0)
    {
        x_inc = -1;
        delta_coord.x = -delta_coord.x;
    }
    D = (2 * delta_coord.x) - delta_coord.y;
    for (coord.y = (int)(from.y), coord.x = (int)(from.x);coord.y <= (int)(to.y);coord.y ++)
    {
        my_mlx_pixel_put(raydata->img_buffer, color, coord);
        if (D > 0)
        {
            coord.x += x_inc;
            D += 2 * (delta_coord.x - delta_coord.y);
        }
        else
            D += 2 * delta_coord.x;
    }
}

void draw_line(t_raydata *raydata, t_color color, t_point from, t_point to)
{
    if (ft_abs((int)(to.y - from.y)) < ft_abs((int)(to.x - from.x)))
    {
        if (from.x > to.x) {
            draw_line_low(raydata, color, to, from);
        }
        else {
            draw_line_low(raydata, color, from, to);
        }
    }
    else
    {
        if (from.y > to.y) {
            draw_line_high(raydata, color, to, from);
        }        else {
            draw_line_high(raydata, color, from, to);
        }
    }
}
