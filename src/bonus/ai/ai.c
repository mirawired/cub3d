/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 10:05:02 by corecaps          #+#    #+#             */
/*   Updated: 2023/10/03 14:57:14 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"
void nmi_chase(t_raydata *raydata, int index)
{
	int			grid_size_x;
	int			grid_size_y;
	t_int_point	dest;

	grid_size_x = WIDTH / (raydata->map_width);
	grid_size_y = HEIGHT / (raydata->map_height);
	dest = bfs(raydata, (t_int_point){(int)(raydata->spr->sprite[index].x),
									  (int)(raydata->spr->sprite[index].y)}, (t_int_point)
					   {(int)(raydata->player->pos.x / grid_size_x),
						(int)(raydata->player->pos.y / grid_size_y)});
	if (dest.x == 0 && dest.y == 0)
		return ;
	raydata->spr->sprite[index].x
			+= (dest.x - (int)raydata->spr->sprite[index].x) * 0.05;
	raydata->spr->sprite[index].y
			+= (dest.y - (int)raydata->spr->sprite[index].y) * 0.05;
}

void nmi_idle(t_raydata *raydata,int index) {
	int x;
	int y;
	int k;
	static t_int_point dest[SPRITENBR] = {0};

	x = (int)raydata->spr->sprite[index].x;
	y = (int)raydata->spr->sprite[index].y;
	k = 1;
	if ((dest[index].x == 0 && dest[index].y == 0)
		|| (dest[index].x == x && dest[index].y == y))
	{
		if (x < raydata->map_width - 1 && raydata->map[y][x + 1] == 0)
		{
			while (x + k < raydata->map_width - 1 && raydata->map[y][x + k] == 0)
				k++;
			dest[index].y = y;
			dest[index].x = x + k - 1;
		}
		else if (y < raydata->map_height - 1 && raydata->map[y + 1][x] == 0)
		{
			while (y + k < raydata->map_height - 1 && raydata->map[y + k][x] == 0)
				k++;
			dest[index].y = y + k - 1;
			dest[index].x = x;
		}
		else if (x > 1 && raydata->map[y][x - 1] == 0)
		{
			while (x - k > 1 && raydata->map[y][x - k] == 0)
				k++;
			dest[index].y = y;
			dest[index].x = x - k + 1;
		}
		else if (y > 1 && raydata->map[y - 1][x] == 0)
		{
			while (y - k > 1 && raydata->map[y - k][x] == 0)
				k++;
			dest[index].y = y - k + 1;
			dest[index].x = x;
		}
	}
	k = ((dest[index].x - (int)raydata->spr->sprite[index].x) >> (sizeof(int) * 8 - 1))
		| (!!((dest[index].x - (int)raydata->spr->sprite[index].x)));
	raydata->spr->sprite[index].x
			+= k * 0.05;
	k = ((dest[index].y - (int)raydata->spr->sprite[index].y) >>(sizeof(int) * 8 - 1))
		| (!!((dest[index].y - (int)raydata->spr->sprite[index].y)));
	raydata->spr->sprite[index].y
			+= k * 0.05;
}

void nmi_flee(t_raydata *raydata,int index)
{
	(void) raydata;
	(void) index;
	return ;
}

t_ai_state check_ai_state(t_raydata *raydata, int index)
{
	int			grid_size_x;
	int			grid_size_y;
	int			distance;

	grid_size_x = WIDTH / (raydata->map_width);
	grid_size_y = HEIGHT / (raydata->map_height);
	distance = sqrt(pow(raydata->spr->sprite[index].x - (raydata->player->pos.x / grid_size_x), 2)
					+ pow(raydata->spr->sprite[index].y - (raydata->player->pos.y / grid_size_y), 2));
	if (distance < 11)
		return (AI_CHASE);
	else
		return (AI_IDLE);
}

void	nmi_ai(t_raydata *raydata)
{
	t_ai_state	state;
	int			index;
	void (*ai_state[3])(t_raydata *raydata, int index);

	ai_state[AI_IDLE] = nmi_idle;
	ai_state[AI_CHASE] = nmi_chase;
	ai_state[AI_FLEE] = nmi_flee;
	index = -1;
	while (index ++ < SPRITENBR - 1)
	{
		state = check_ai_state(raydata, index);
		ai_state[state](raydata,index);
	}
}
