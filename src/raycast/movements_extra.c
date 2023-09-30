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

#include "../../inc/cub3d.h"

void	clamp_player(t_raydata *raydata)
{
	if (raydata->player->pos.x < 0 + (raydata->player->size * 2))
		raydata->player->pos.x = (double)(0 + (raydata->player->size * 2));
	if (raydata->player->pos.y < 0 + (raydata->player->size * 2))
		raydata->player->pos.y = (double)(0 + (raydata->player->size * 2));
	if (raydata->player->pos.x > (double)(WIDTH - (raydata->player->size * 2)))
		raydata->player->pos.x = (double)(WIDTH - (raydata->player->size * 2));
	if (raydata->player->pos.y > (double)(HEIGHT - (raydata->player->size * 2)))
		raydata->player->pos.y = (double)(HEIGHT - (raydata->player->size * 2));
}

void	strafe_right(t_raydata *raydata)
{
	double	stepsize;
	t_point	perpvector;

	stepsize = 10;
	perpvector.x = -raydata->player->dir_vector.y;
	perpvector.y = raydata->player->dir_vector.x;
	raydata->player->pos.x += perpvector.x * stepsize;
	raydata->player->pos.y += perpvector.y * stepsize;
	clamp_player(raydata);
}

void	strafe_left(t_raydata *raydata)
{
	double	stepsize;
	t_point	perpvector;

	stepsize = 10;
	perpvector.x = raydata->player->dir_vector.y;
	perpvector.y = -raydata->player->dir_vector.x;
	raydata->player->pos.x += perpvector.x * stepsize;
	raydata->player->pos.y += perpvector.y * stepsize;
	clamp_player(raydata);
}
