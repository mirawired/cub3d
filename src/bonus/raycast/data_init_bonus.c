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
	raydata->texture[NO] = load_texture(raydata->mlx, arg->no);
	raydata->texture[SO] = load_texture(raydata->mlx, arg->so);
	raydata->texture[WE] = load_texture(raydata->mlx, arg->we);
	raydata->texture[EA] = load_texture(raydata->mlx, arg->ea);
	raydata->texture[CEIL] = load_texture(raydata->mlx, "bluestone.xpm");
	raydata->texture[FLOOR] = load_texture(raydata->mlx, "purplestone.xpm");
	raydata->texture[NO] = load_texture(raydata->mlx, arg->no);
	raydata->texture[SO] = load_texture(raydata->mlx, arg->so);
	raydata->texture[WE] = load_texture(raydata->mlx, arg->we);
	raydata->texture[EA] = load_texture(raydata->mlx, arg->ea);
	raydata->texture[CEIL] = load_texture(raydata->mlx, "steel.xpm");
	raydata->texture[FLOOR] = load_texture(raydata->mlx, "floor.xpm");
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
	spr->sprite[0].texture[0] = load_texture(raydata->mlx, "ghost.xpm");
	spr->sprite[0].texture[1] = load_texture(raydata->mlx, "ghost2.xpm");
	spr->sprite[1].texture[0] = load_texture(raydata->mlx, "ghost2.xpm");
	spr->sprite[1].texture[1] = load_texture(raydata->mlx, "ghost.xpm");
	spr->sprite[2].texture[0] = load_texture(raydata->mlx, "ghost.xpm");
	spr->sprite[2].texture[1] = load_texture(raydata->mlx, "ghost2.xpm");
	spr->sprite[3].texture[0] = load_texture(raydata->mlx, "ghost2.xpm");
	spr->sprite[3].texture[1] = load_texture(raydata->mlx, "ghost.xpm");
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
 * starting_data_init:
 * - initialize the data for the game
 ************************************************************************** */

void	starting_data_init(t_arg *arg, t_raydata *raydata)
{
	raydata->player->angle = 0;
	raydata->player->size = 10;
	raydata->player->dir_vector.x = 1;
	raydata->player->dir_vector.y = 0;
	raydata->player->plane_vector.x = 0;
	raydata->player->plane_vector.y = 0.66;
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
