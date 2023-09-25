/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 23:50:13 by jgarcia           #+#    #+#             */
/*   Updated: 2023/09/11 11:15:49 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/raycast.h"

int	raycast(t_arg *arg)
{
	t_raydata	*raydata;

	raydata = gc_alloc(1,sizeof (t_raydata));
	if (!raydata)
		return (1);
	raydata->img_buffer = gc_alloc(1,sizeof(t_buffer));
	if (!raydata->img_buffer)
		return (1);
	raydata->mlx = NULL;
	init_mlx(raydata);
	wall_textures_init(arg, raydata);
	ennemies_textures_init(raydata);
	raydata->player = gc_alloc(1,sizeof (t_player));
	player_init_position(arg, raydata);
	starting_data_init(arg, raydata);
	launch_game_loop(raydata);
	return (0);
}
