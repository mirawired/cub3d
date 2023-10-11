/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 10:05:19 by corecaps          #+#    #+#             */
/*   Updated: 2023/10/10 19:09:48 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

/* **************************************************************************
 * player_init_position:
 * - find the player position in the map
 * - if not found, set the player position to the center of the map
 ************************************************************************** */

void	player_init_position(t_arg *arg, t_raydata *raydata)
{
	int		found;
	double	grid_size_x;
	double	grid_size_y;
	int		i;

	found = 0;
	grid_size_x = (double) WIDTH / arg->width;
	grid_size_y = (double) HEIGHT / arg->height;
	i = 0;
	while (i < arg->height)
	{
		if (find_player(raydata, i, grid_size_x, grid_size_y))
			found = 1;
		i++;
	}
	if (found == 0)
	{
		raydata->player->pos.x = (double) HEIGHT / 2;
		raydata->player->pos.y = (double) WIDTH / 2;
	}
}

/* **************************************************************************
 * wall_textures_init:
 * - allocate memory for the textures
 * - load the textures for the walls
 ************************************************************************** */

void	wall_textures_init(t_arg *arg, t_raydata *raydata)
{
	raydata->texture = (t_texture **)gc_alloc(6, sizeof(t_raydata));
	raydata->texture[NO] = load_texture(raydata, arg->no);
	raydata->texture[SO] = load_texture(raydata, arg->so);
	raydata->texture[WE] = load_texture(raydata, arg->we);
	raydata->texture[EA] = load_texture(raydata, arg->ea);
	raydata->texture[CEIL] = load_texture(raydata, "bluestone.xpm");
	raydata->texture[FLOOR] = load_texture(raydata, "purplestone.xpm");
	raydata->texture[NO] = load_texture(raydata, arg->no);
	raydata->texture[SO] = load_texture(raydata, arg->so);
	raydata->texture[WE] = load_texture(raydata, arg->we);
	raydata->texture[EA] = load_texture(raydata, arg->ea);
	raydata->texture[CEIL] = load_texture(raydata, "steel.xpm");
	raydata->texture[FLOOR] = load_texture(raydata, "floor.xpm");
}

/* **************************************************************************
 * enemies_textures_init:
 * - allocate memory for the textures
 * - load the textures for the ennemies
 * - set the position of the ennemies
 ************************************************************************** */

void	ennemies_textures_init(t_raydata *raydata)
{
	t_spr	*spr;

	raydata->spr = (t_spr *)gc_alloc(1, sizeof(t_spr));
	spr = raydata->spr;
	spr->sprite[0].texture = gc_alloc(2, sizeof(t_texture *));
	spr->sprite[1].texture = gc_alloc(2, sizeof(t_texture *));
	spr->sprite[2].texture = gc_alloc(2, sizeof(t_texture *));
	spr->sprite[3].texture = gc_alloc(2, sizeof(t_texture *));
	spr->sprite[0].texture[0] = load_texture(raydata, "ghost.xpm");
	spr->sprite[0].texture[1] = load_texture(raydata, "ghost2.xpm");
	spr->sprite[1].texture[0] = load_texture(raydata, "ghost2.xpm");
	spr->sprite[1].texture[1] = load_texture(raydata, "ghost.xpm");
	spr->sprite[2].texture[0] = load_texture(raydata, "ghost.xpm");
	spr->sprite[2].texture[1] = load_texture(raydata, "ghost2.xpm");
	spr->sprite[3].texture[0] = load_texture(raydata, "ghost2.xpm");
	spr->sprite[3].texture[1] = load_texture(raydata, "ghost.xpm");
	spr->sprite[0].x = 1.0;
	spr->sprite[0].y = 1.0;
	spr->sprite[1].x = raydata->map_width - 2;
	spr->sprite[1].y = 1.0;
	spr->sprite[2].x = 1.0;
	spr->sprite[2].y = raydata->map_height - 2;
	spr->sprite[3].x = raydata->map_width - 2;
	spr->sprite[3].y = raydata->map_height - 2;
	raydata->spr->spr_i = 0;
}
/* **************************************************************************
 * find_player:
 * - find the player in the map and set its position
 * - set the player's initial position
 * - return 1 if found, 0 if not
 ************************************************************************** */

int	find_player(t_raydata *raydata, int i, double gs_x, double gs_y)
{
	int	j;
	int	found;

	j = 0;
	found = 0;
	while (j < raydata->arg->width)
	{
		if (raydata->arg->fmap[i][j] < 0)
		{
			raydata->player->pos.x = (double) j * gs_x + gs_x / 2;
			raydata->player->pos.y = (double) i * gs_y + gs_y / 2;
			raydata->player->init_angle = -(raydata->arg->fmap[i][j] + 1) * 90;
			found = 1;
			raydata->arg->fmap[i][j] = 0;
		}
		j++;
	}
	return (found);
}

/* **************************************************************************
 * starting_data_init:
 * - initialize the data for the game
 ************************************************************************** */

void	starting_data_init(t_arg *arg, t_raydata *raydata)
{
	raydata->player->angle = raydata->player->init_angle;
	raydata->player->size = 5;
	raydata->player->dir_vector.x = 1;
	raydata->player->dir_vector.y = 0;
	raydata->player->plane_vector.x = 0;
	raydata->player->plane_vector.y = 0.66;
	rotate_player(raydata, raydata->player->init_angle);
	raydata->map = arg->fmap;
	raydata->map_height = arg->height;
	raydata->map_width = arg->width;
	raydata->ceil_color.s_rgb.r = arg->c_color[0];
	raydata->ceil_color.s_rgb.g = arg->c_color[1];
	raydata->ceil_color.s_rgb.b = arg->c_color[2];
	raydata->floor_color.s_rgb.r = arg->f_color[0];
	raydata->floor_color.s_rgb.g = arg->f_color[1];
	raydata->floor_color.s_rgb.b = arg->f_color[2];
	raydata->game_state = MENU;
	raydata->img_menu = NULL;
}
