//
// Created by corecaps on 12/03/23.
//
#include "./../../inc/raycast.h"

int my_mlx_pixel_put(t_buffer *data, t_color color, t_int_point coord)
{
	char	*dst;
    if (coord.x < 0 || coord.x > WIDTH || coord.y < 0 || coord.y > HEIGHT) {
        printf("error : %d %d\n",coord.x,coord.y);
        return (-1); }
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
//    printf("drawing in color %x from (%f, %f) to (%f, %f)\n", color.color, top_left.x, top_left.y, bottom_right.x, bottom_right.y);
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
