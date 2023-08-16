//
// Created by corecaps on 27/07/23.
//
#include "./../../inc/raycast.h"

t_point calc_point(t_point from, double angle, double distance)
{
    t_point result;
    result.x = from.x + cos(angle) * distance;
    result.y = from.y + sin(angle) * distance;
    return (result);
}

t_point clamp(t_point point)
{
    t_point result;
    result.x = point.x;
    result.y = point.y;
    if (result.x < 0)
        result.x = 0;
    if (result.x > WIDTH)
        result.x = WIDTH;
    if (result.y < 0)
        result.y = 0;
    if (result.y > HEIGHT)
        result.y = HEIGHT;
    return (result);
}
void draw_player(t_raydata *raydata)
{
    t_color player_color = {0xFF0000};
    t_point player_pos = {raydata->player->pos.x, raydata->player->pos.y};
    double player_angle = raydata->player->angle * RADIAN;
    t_point front = calc_point(player_pos, player_angle, raydata->player->size * 2);
    t_point left = calc_point(player_pos, player_angle + 90 * RADIAN, raydata->player->size);
    t_point right = calc_point(player_pos, player_angle - 90 * RADIAN, raydata->player->size);

//    front = clamp(front);
//    left = clamp(left);
//    right = clamp(right);
    draw_line(raydata, player_color, left, front);
    draw_line(raydata, player_color, right, front);
    draw_line(raydata, player_color, left, right);
}
