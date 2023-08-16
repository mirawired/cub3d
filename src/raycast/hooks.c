//
// Created by corecaps on 17/02/23.
//

#include "./../../inc/raycast.h"

void clamp_player(t_raydata *raydata);

int key_pressed(int keycode, t_raydata *raydata)
{
	if (keycode == 65307)
	{
		mlx_destroy_image(raydata->mlx,raydata->img_buffer->img);
		free(raydata->img_buffer);
		mlx_destroy_window(raydata->mlx,raydata->mlx_win);
		mlx_destroy_display(raydata->mlx);
		free(raydata->mlx);
		free(raydata);
		exit(0);
	}
	if (keycode == 97 || keycode == 65361)
	{
        raydata->player->angle -= 3;
        if (raydata->player->angle < 0)
            raydata->player->angle = 359;
	}
	if (keycode == 100 || keycode == 65363)
	{
        raydata->player->angle += 3;
        if (raydata->player->angle > 359)
            raydata->player->angle = 0;
	}
    if (keycode == 119 || keycode == 65362)
    {
        raydata->player->pos.x +=	10 * cos(raydata->player->angle * RADIAN);
        raydata->player->pos.y +=  10 * (sin(raydata->player->angle * RADIAN));
        clamp_player(raydata);
    }
    if (keycode == 115 || keycode == 65364)
    {
        raydata->player->pos.x -=	cos(raydata->player->angle * RADIAN) * 10;
        raydata->player->pos.y -= sin(raydata->player->angle * RADIAN) * 10;
        clamp_player(raydata);
    }
	return (0);
}

void clamp_player(t_raydata *raydata) {
    if (raydata->player->pos.x < 0 + (raydata->player->size * 2))
        raydata->player->pos.x =(double) (0 + (raydata->player->size * 2));
    if (raydata->player->pos.y < 0 + (raydata->player->size * 2))
        raydata->player->pos.y = (double)(0 + (raydata->player->size * 2));
    if (raydata->player->pos.x > (double)(WIDTH - (raydata->player->size * 2)))
        raydata->player->pos.x =(double)( WIDTH - (raydata->player->size * 2));
    if (raydata->player->pos.y >(double)( HEIGHT - (raydata->player->size * 2)))
        raydata->player->pos.y = (double)(HEIGHT - (raydata->player->size * 2));
}
