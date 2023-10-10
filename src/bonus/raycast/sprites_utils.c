//
// Created by corecaps on 10/9/23.
//

#include "../../../inc/cub3d.h"

/* **************************************************************************
 * clamp_idx:
 * - clamps the sprite to the center of the cell if it is surrounded by walls
 ************************************************************************** */

void clamp_idx(t_raydata *raydata, int index)
{
	int x;
	int y;

	x = (int) raydata->spr->sprite[index].x;
	y = (int) raydata->spr->sprite[index].y;
	if (x < raydata->map_width + 1
		&& raydata->map[y][x + 1] == 1
		&& x > 0
		&& raydata->map[y][x - 1] == 1)
			raydata->spr->sprite[index].x = x + 0.5;
	if (y < raydata->map_height + 1
		&& raydata->map[y + 1][x] == 1
		&& y > 0
		&& raydata->map[y - 1][x] == 1)
			raydata->spr->sprite[index].y = y + 0.5;
}

/* **************************************************************************
 * clamp_sprites:
 * - clamps all sprites to the center of the cell if they are surrounded by
 *  walls
 ************************************************************************** */

void clamp_sprites(t_raydata *raydata)
{
	int i;

	i = 0;
	while (i < SPRITENBR)
		clamp_idx(raydata, i ++);
}