//
// Created by corecaps on 9/22/23.
//
#include "../../inc/cub3d.h"

void nmi_ai(t_raydata *raydata) {
	int grid_size_x = WIDTH / (raydata->map_width);
	int grid_size_y = HEIGHT / (raydata->map_height);
	for (int i = 0;i < SPRITENBR; i ++) {
		t_int_point dest = bfs(raydata,(t_int_point){(int)(raydata->spr->sprite[i].x) , (int )(raydata->spr->sprite[i].y)},(t_int_point) {(int)(raydata->player->pos.x / grid_size_x),(int)(raydata->player->pos.y/grid_size_y)} );
		if (dest.x == 0 && dest.y == 0)
			continue;
		raydata->spr->sprite[i].x += (dest.x - (int)raydata->spr->sprite[i].x) * 0.05;
		raydata->spr->sprite[i].y += (dest.y - (int)raydata->spr->sprite[i].y) * 0.05;
	}
}
