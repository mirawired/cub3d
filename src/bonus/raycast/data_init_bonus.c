/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 10:05:19 by corecaps          #+#    #+#             */
/*   Updated: 2023/10/03 15:43:46 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

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

void	wall_textures_init(t_arg *arg, t_raydata *raydata)
{
	raydata->texture = (t_texture **) gc_alloc(4, sizeof(t_raydata));
	raydata->texture[NO] = load_texture(raydata->mlx, arg->NO);
	raydata->texture[SO] = load_texture(raydata->mlx, arg->SO);
	raydata->texture[WE] = load_texture(raydata->mlx, arg->WE);
	raydata->texture[EA] = load_texture(raydata->mlx, arg->EA);
}

void	ennemies_textures_init(t_raydata *raydata)
{
	raydata->spr = (t_spr *)gc_alloc(1, sizeof(t_spr));
	raydata->spr->sprite[0].texture = load_texture(raydata->mlx, "ghost.xpm");
	raydata->spr->sprite[1].texture = load_texture(raydata->mlx, "ghost2.xpm");
	raydata->spr->sprite[2].texture = load_texture(raydata->mlx, "ghost.xpm");
	raydata->spr->sprite[3].texture = load_texture(raydata->mlx, "ghost2.xpm");
	raydata->spr->sprite[0].texture[0] = load_texture(raydata->mlx, "ghost.xpm");
	raydata->spr->sprite[0].texture[1] = load_texture(raydata->mlx, "ghost2.xpm");
	raydata->spr->sprite[1].texture[0] = load_texture(raydata->mlx, "ghost2.xpm");
	raydata->spr->sprite[1].texture[1] = load_texture(raydata->mlx, "ghost.xpm");
	raydata->spr->sprite[2].texture[0] = load_texture(raydata->mlx, "ghost.xpm");
	raydata->spr->sprite[2].texture[1] = load_texture(raydata->mlx, "ghost2.xpm");
	raydata->spr->sprite[3].texture[0] = load_texture(raydata->mlx, "ghost2.xpm");
	raydata->spr->sprite[3].texture[1] = load_texture(raydata->mlx, "ghost.xpm");
	raydata->spr->sprite[0].x = 1.0;
	raydata->spr->sprite[0].y = 1.0;
	raydata->spr->sprite[1].x = raydata->map_width - 2;
	raydata->spr->sprite[1].y = 1.0;
	raydata->spr->sprite[2].x = 1.0;
	raydata->spr->sprite[2].y = raydata->map_height - 2;
	raydata->spr->sprite[3].x = raydata->map_width - 2;
	raydata->spr->sprite[3].y = raydata->map_height - 2;
	raydata->spr->spr_i = 0;
}

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
	raydata->ceil_color.s_rgb.r = arg->C[0];
	raydata->ceil_color.s_rgb.g = arg->C[1];
	raydata->ceil_color.s_rgb.b = arg->C[2];
	raydata->floor_color.s_rgb.r = arg->F[0];
	raydata->floor_color.s_rgb.g = arg->F[1];
	raydata->floor_color.s_rgb.b = arg->F[2];
	raydata->game_state = MENU;
	raydata->img_menu = NULL;
}
