//
// Created by corecaps on 17/02/23.
//
#include "./../../inc/raycast.h"

int render(t_raydata *raydata)
{
	clear_buffer(raydata);
	t_color white = {0xFFFFFF};
    int grid_size_x = WIDTH / GRID_WIDTH;
    int grid_size_y = HEIGHT / GRID_HEIGHT;

    t_color grid_color;
    grid_color.s_rgb.r = (char)40;
    grid_color.s_rgb.g = (char)40;
    grid_color.s_rgb.b = (char)40;
    for (int i = 0; i < GRID_HEIGHT * grid_size_y;i += grid_size_y)
    {
        draw_line(raydata, grid_color,(t_point) {(double)0, (double)i},(t_point) {(double)WIDTH, (double)i});
    }
    for (int i = 0; i < GRID_WIDTH * grid_size_x;i += grid_size_x)
    {
        draw_line(raydata, grid_color,(t_point) {(double)i, (double)0},(t_point) {(double)i, (double)HEIGHT});
    }
    for (int i = 0; i < GRID_WIDTH;i++) {
        for (int j = 0; j < GRID_HEIGHT;j ++) {
            if (raydata->map[j][i] == 1) {
                fill_rectangle(raydata, grid_color,
                               (t_point) {(double)(i * grid_size_x), (double)(j * grid_size_y)},
                               (t_point) {(double)((i + 1) * grid_size_x), (double)((j + 1) * grid_size_y)});
            }
        }
    }
    t_int_point player_in_grid;
    player_in_grid.x = (int)(raydata->player->pos.x / grid_size_x);
    player_in_grid.y = (int)(raydata->player->pos.y / grid_size_y);
//    printf("player in grid: %d, %d\n", player_in_grid.x, player_in_grid.y);
    draw_line(raydata, white,(t_point) {(double)WIDTH, (double)0},(t_point) {(double)WIDTH, (double)HEIGHT});
    draw_player(raydata);
    draw_rays(raydata);
	mlx_put_image_to_window(raydata->mlx,
							raydata->mlx_win,
							raydata->img_buffer->img,
							0 ,0);
	return (0);
}
