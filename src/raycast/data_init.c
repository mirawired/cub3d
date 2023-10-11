/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 10:03:41 by corecaps          #+#    #+#             */
/*   Updated: 2023/10/10 21:13:25 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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
			found = 1;
			raydata->arg->fmap[i][j] = 0;
		}
		j++;
	}
	return (found);
}

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
	raydata->texture = (t_texture **)gc_alloc(4, sizeof(t_raydata));
	raydata->texture[NO] = load_texture(raydata, arg->no);
	raydata->texture[SO] = load_texture(raydata, arg->so);
	raydata->texture[WE] = load_texture(raydata, arg->we);
	raydata->texture[EA] = load_texture(raydata, arg->ea);
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
	raydata->ceil_color.s_rgb.r = arg->c_color[0];
	raydata->ceil_color.s_rgb.g = arg->c_color[1];
	raydata->ceil_color.s_rgb.b = arg->c_color[2];
	raydata->floor_color.s_rgb.r = arg->f_color[0];
	raydata->floor_color.s_rgb.g = arg->f_color[1];
	raydata->floor_color.s_rgb.b = arg->f_color[2];
}
