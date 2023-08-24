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
//		free(raydata->img_buffer);
		mlx_destroy_window(raydata->mlx,raydata->mlx_win);
		mlx_destroy_display(raydata->mlx);
		free(raydata->mlx);
//        free(raydata->player);
//        free(raydata->EA->texture);
//        free(raydata->EA);
//        free(raydata->WE->texture);
//        free(raydata->WE);
//        free(raydata->SO->texture);
//        free(raydata->SO);
//        free(raydata->NO->texture);
//        free(raydata->NO);
//		free(raydata);
        gc_free();
		exit(0);
	}
	if (keycode == 97 || keycode == 65361)
	{
        t_point old_dir = raydata->player->dir_vector;
        t_point old_plane = raydata->player->plane_vector;
        raydata->player->dir_vector.x = raydata->player->dir_vector.x * cos(-3 * RADIAN) - raydata->player->dir_vector.y * sin(-3 * RADIAN);
        raydata->player->dir_vector.y = old_dir.x * sin(-3 * RADIAN) + raydata->player->dir_vector.y * cos(-3 * RADIAN);
        raydata->player->plane_vector.x = raydata->player->plane_vector.x * cos(-3 * RADIAN) - raydata->player->plane_vector.y * sin(-3 * RADIAN);
        raydata->player->plane_vector.y = old_plane.x * sin(-3 * RADIAN) + raydata->player->plane_vector.y * cos(-3 * RADIAN);

        raydata->player->angle -= 3;
        if (raydata->player->angle < 0)
            raydata->player->angle = 359;
	}
	if (keycode == 100 || keycode == 65363)
	{
        t_point old_dir = raydata->player->dir_vector;
        t_point old_plane = raydata->player->plane_vector;
        raydata->player->dir_vector.x = raydata->player->dir_vector.x * cos(3 * RADIAN) - raydata->player->dir_vector.y * sin(3 * RADIAN);
        raydata->player->dir_vector.y = old_dir.x * sin(3 * RADIAN) + raydata->player->dir_vector.y * cos(3 * RADIAN);
        raydata->player->plane_vector.x = raydata->player->plane_vector.x * cos(3 * RADIAN) - raydata->player->plane_vector.y * sin(3 * RADIAN);
        raydata->player->plane_vector.y = old_plane.x * sin(3 * RADIAN) + raydata->player->plane_vector.y * cos(3 * RADIAN);
        raydata->player->angle += 3;
        if (raydata->player->angle > 359)
            raydata->player->angle = 0;
	}

    if (keycode == 101)  // Keycode for 'e'
    {
        double stepSize = 10;  // Adjust the step size as needed

        // Calculate the perpendicular vector to the player's direction vector
        t_point perpVector = {-raydata->player->dir_vector.y, raydata->player->dir_vector.x};

        raydata->player->pos.x += perpVector.x * stepSize;
        raydata->player->pos.y += perpVector.y * stepSize;
        clamp_player(raydata);
    }
    if (keycode == 113)  // Keycode for 'q'
    {
        double stepSize = 10;  // Adjust the step size as needed

        // Calculate the perpendicular vector to the player's direction vector
        t_point perpVector = {raydata->player->dir_vector.y, -raydata->player->dir_vector.x};

        raydata->player->pos.x += perpVector.x * stepSize;
        raydata->player->pos.y += perpVector.y * stepSize;
        clamp_player(raydata);
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