/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 12:36:22 by avassor           #+#    #+#             */
/*   Updated: 2023/10/03 16:11:51 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/raycast.h"

void	sort_sprites(t_spr	*spr, t_point pos)
{
	int	i;

	i = 0;
	while (i < SPRITENBR)
	{
		spr->sprite_order[i] = i;
		spr->sprite_dist[i] = ((pos.x - spr->sprite[i].x)
				* (pos.x - spr->sprite[i].x) + (pos.y - spr->sprite[i].y)
				* (pos.y - spr->sprite[i].y));
		i++;
	}
	i = 0;
	while (i < SPRITENBR)
	{
		if (spr->sprite_dist[i] < spr->sprite_dist[i + 1])
		{
			spr->sprite_order[i] = i + 1;
			spr->sprite_order[i + 1] = i;
			break ;
		}
		i++;
	}
}

void	comp_long(t_raydata *data, t_cs *cs)
{
	cs->invDet = 1.0 / (data->player->plane_vector.x
			* data->player->dir_vector.y - data->player->dir_vector.x
			* data->player->plane_vector.y);
	cs->transX = cs->invDet * (data->player->dir_vector.y * cs->spriteX
			- data->player->dir_vector.x * cs->spriteY);
	cs->transY = cs->invDet * (-data->player->plane_vector.y * cs->spriteX
			+ data->player->plane_vector.x + data->player->plane_vector.x
			* cs->spriteY);
}

void	comp_sprites(t_raydata *data, t_sprite *curr, t_point pos)
{
	t_cs	*cs;

	cs = &data->spr->cs;
	cs->spriteX = curr->x - pos.x;
	cs->spriteY = curr->y - pos.y;
	comp_long(data, cs);
	cs->spriteScreenX = (int)((WIDTH / 2) * (1 + cs->transX / cs->transY));
	cs->vMoveScreen = (int)(0.0 / cs->transY);
	cs->spriteHeight = ft_abs((int)(HEIGHT / cs->transY)) / 1;
	cs->drawStartY = -cs->spriteHeight / 2 + HEIGHT / 2 + cs->vMoveScreen;
	if (cs->drawStartY < 0)
		cs->drawStartY = 0;
	cs->drawEndY = cs->spriteHeight / 2 + HEIGHT / 2 + cs->vMoveScreen;
	if (cs->drawEndY >= HEIGHT)
		cs->drawEndY = HEIGHT - 1;
	cs->spriteWidth = ft_abs((int)(HEIGHT / cs->transY)) / 1;
	cs->drawStartX = -cs->spriteWidth / 2 + cs->spriteScreenX;
	if (cs->drawStartX < 0)
		cs->drawStartX = 0;
	cs->drawEndX = cs->spriteWidth / 2 + cs->spriteScreenX;
	if (cs->drawEndX >= WIDTH)
		cs->drawEndX = WIDTH;
	cs->stripe = cs->drawStartX;
}

void	sprite_pxl(t_raydata *data, t_cs *cs, t_sprite *curr)
{
	t_color	color;
	int		texx;
	int		texy;
	int		y;
	int		d;

	texx = (int)(256 * (cs->stripe - (-cs->spriteWidth / 2
					+ cs->spriteScreenX)) * 64 / cs->spriteWidth) / 256;
	y = cs->drawStartY;
	if (cs->transY > 0 && cs->transY < data->spr->Zbuffer[cs->stripe])
	{
		while (y < cs->drawEndY)
		{
			d = (y - cs->vMoveScreen) * 256 - HEIGHT * 128
				+ cs->spriteHeight * 128;
			texy = ((d * 64) / cs->spriteHeight) / 256;
			color = curr->texture->texture[64 * texy + texx];
			if (color.color != BLACK)
				my_mlx_pixel_put(data->img_buffer, color,
					(t_int_point){cs->stripe, y});
			y++;
		}
	}
}

void	draw_sprites(t_raydata *data, t_point pos)
{
	t_sprite	curr;
	t_spr		*spr;
	t_cs		*cs;
	int			i;

	i = 0;
	spr = data->spr;
	sort_sprites(spr, pos);
	while (i < SPRITENBR)
	{
		curr = spr->sprite[spr->sprite_order[i]];
		comp_sprites(data, &curr, pos);
		cs = &spr->cs;
		while (cs->stripe < cs->drawEndX)
		{
			sprite_pxl(data, cs, &curr);
			cs->stripe++;
		}
		i++;
	}
}
