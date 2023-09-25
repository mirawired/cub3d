/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 10:03:41 by corecaps          #+#    #+#             */
/*   Updated: 2023/09/25 10:03:47 by corecaps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void player_init_position(t_arg *arg, t_raydata *raydata) {
	int		found;
	double	grid_size_x;
	double	grid_size_y;
	int 	i;
	int 	j;

	found  = 0;
	grid_size_x = (double) WIDTH / arg->width;
	grid_size_y = (double) HEIGHT / arg->height;
	i = 0;
	while (i < arg->height) {
		j = 0;
		while (j < arg->width) {
			if (arg->fmap[i][j] < 0) {
				raydata->player->pos.x = (double) j * grid_size_x + grid_size_x / 2;
				raydata->player->pos.y = (double) i * grid_size_y + grid_size_y / 2;
				found = 1;
				arg->fmap[i][j] = 0;
			}
			j ++;
		}
		i ++;
	}
	if (found == 0) {
		raydata->player->pos.x = (double) HEIGHT / 2;
		raydata->player->pos.y = (double) WIDTH / 2;
	}
}

void wall_textures_init(t_arg *arg, t_raydata *raydata) {
	raydata->texture = (t_texture **) gc_alloc(4, sizeof(t_raydata));
	raydata->texture[NO] = load_texture(raydata->mlx,arg->NO);
	raydata->texture[SO] = load_texture(raydata->mlx,arg->SO);
	raydata->texture[WE] = load_texture(raydata->mlx,arg->WE);
	raydata->texture[EA] = load_texture(raydata->mlx,arg->EA);
}

void starting_data_init(t_arg *arg, t_raydata *raydata) {
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
}
