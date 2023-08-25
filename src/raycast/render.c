//
// Created by corecaps on 17/02/23.
//
#include "./../../inc/raycast.h"

int render(t_raydata *raydata)
{
	clear_buffer(raydata);
	t_color white = {0xFFFFFF};
    int grid_size_x = WIDTH / raydata->map_width;
    int grid_size_y = HEIGHT / raydata->map_height;

    t_color grid_color;
    grid_color.s_rgb.r = (char)127;
    grid_color.s_rgb.g = (char)0;
    grid_color.s_rgb.b = (char)0;
    for (int i = 0; i < raydata->map_height * grid_size_y;i += grid_size_y)
    {
        draw_line(raydata, grid_color,(t_point) {(double)0, (double)i},(t_point) {(double)WIDTH, (double)i});
    }
    for (int i = 0; i < raydata->map_width * grid_size_x;i += grid_size_x)
    {
        draw_line(raydata, grid_color,(t_point) {(double)i, (double)0},(t_point) {(double)i, (double)HEIGHT});
    }
    grid_color.s_rgb.r = (char)40;
    grid_color.s_rgb.g = (char)40;
    grid_color.s_rgb.b = (char)40;
    for (int i = 0; i < raydata->map_height;i++) {
        for (int j = 0; j < raydata->map_width;j ++) {
            if (raydata->map[i][j] == 1) {
                fill_rectangle(raydata, grid_color,
                               (t_point) {(double)(j * grid_size_x), (double)(i * grid_size_y)},
                               (t_point) {(double)((j + 1) * grid_size_x), (double)((i + 1) * grid_size_y)});
            }
        }
    }
    draw_line(raydata, white,(t_point) {(double)WIDTH, (double)0},(t_point) {(double)WIDTH, (double)HEIGHT});
    draw_player(raydata);
    draw_rays(raydata);
	mlx_put_image_to_window(raydata->mlx,
							raydata->mlx_win,
							raydata->img_buffer->img,
							0 ,0);
	return (0);
}