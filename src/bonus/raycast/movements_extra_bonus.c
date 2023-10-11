/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 10:04:25 by corecaps          #+#    #+#             */
/*   Updated: 2023/09/30 13:30:19 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

void	clamp_player(t_raydata *raydata)
{
	int			grid_size_x;
	int			grid_size_y;
	t_player	*p;

	grid_size_y = HEIGHT / raydata->map_height;
	grid_size_x = WIDTH / raydata->map_width;
	p = raydata->player;
	if (p->pos.x < 0 + grid_size_x + (raydata->player->size * 2))
		p->pos.x = (double)(0 + grid_size_x +(raydata->player->size * 2));
	if (p->pos.y < 0 + grid_size_y +(raydata->player->size * 2))
		p->pos.y = (double)(0 + grid_size_y + (raydata->player->size * 2));
	if (p->pos.x > (double)(WIDTH - grid_size_x - (raydata->player->size * 2)))
		p->pos.x = (double)(WIDTH - grid_size_x - (raydata->player->size * 2));
	if (p->pos.y > (double)(HEIGHT - grid_size_y - (raydata->player->size * 2)))
		p->pos.y = (double)(HEIGHT - grid_size_y - (raydata->player->size * 2));
}

void	strafe_right(t_raydata *raydata)
{
	double	stepsize;
	t_point	perpvector;
	t_point	new_pos;

	stepsize = PLAYERSPEED;
	perpvector.x = -raydata->player->dir_vector.y;
	perpvector.y = raydata->player->dir_vector.x;
	new_pos.x = raydata->player->pos.x + perpvector.x * stepsize;
	new_pos.y = raydata->player->pos.y;
	if (!check_collision(raydata, new_pos))
	{
		raydata->player->pos.x = new_pos.x;
	}
	new_pos.x = raydata->player->pos.x;
	new_pos.y = raydata->player->pos.y + perpvector.y * stepsize;
	if (!check_collision(raydata, new_pos))
		raydata->player->pos.y = new_pos.y;
	clamp_player(raydata);
}

void	strafe_left(t_raydata *raydata)
{
	double	stepsize;
	t_point	perpvector;
	t_point	new_pos;

	stepsize = PLAYERSPEED;
	perpvector.x = raydata->player->dir_vector.y;
	perpvector.y = -raydata->player->dir_vector.x;
	new_pos.x = raydata->player->pos.x + perpvector.x * stepsize;
	if (!check_collision(raydata, new_pos))
	{
		raydata->player->pos.x = new_pos.x;
	}
	new_pos.x = raydata->player->pos.x;
	new_pos.y = raydata->player->pos.y + perpvector.y * stepsize;
	if (!check_collision(raydata, new_pos))
		raydata->player->pos.y = new_pos.y;
	clamp_player(raydata);
}

int	check_collision(t_raydata *raydata, t_point new_pos)
{
	int	grid_size_x;
	int	grid_size_y;
	int	x;
	int	y;

	grid_size_y = HEIGHT / raydata->map_height;
	grid_size_x = WIDTH / raydata->map_width;
	x = (int)(new_pos.x / grid_size_x);
	y = (int)(new_pos.y / grid_size_y);
	if (raydata->map[y][x] == 1)
		return (1);
	return (0);
}
