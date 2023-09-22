//
// Created by corecaps on 9/22/23.
//
#include "../../inc/cub3d.h"

void clamp_player(t_raydata *raydata) {
	if (raydata->player->pos.x < 0 + (raydata->player->size * 2))
		raydata->player->pos.x = (double) (0 + (raydata->player->size * 2));
	if (raydata->player->pos.y < 0 + (raydata->player->size * 2))
		raydata->player->pos.y = (double) (0 + (raydata->player->size * 2));
	if (raydata->player->pos.x > (double) (WIDTH - (raydata->player->size * 2)))
		raydata->player->pos.x = (double) (WIDTH - (raydata->player->size * 2));
	if (raydata->player->pos.y >
		(double) (HEIGHT - (raydata->player->size * 2)))
		raydata->player->pos.y = (double) (HEIGHT -
										   (raydata->player->size * 2));
}


void stripe_right(t_raydata *raydata) {
	double stepSize = 10;
	t_point perpVector = {-raydata->player->dir_vector.y,
						  raydata->player->dir_vector.x};
	raydata->player->pos.x += perpVector.x * stepSize;
	raydata->player->pos.y += perpVector.y * stepSize;
	clamp_player(raydata);
}

void stripe_left(t_raydata *raydata) {
	double stepSize = 10;
	t_point perpVector = {raydata->player->dir_vector.y,
						  -raydata->player->dir_vector.x};
	raydata->player->pos.x += perpVector.x * stepSize;
	raydata->player->pos.y += perpVector.y * stepSize;
	clamp_player(raydata);
}