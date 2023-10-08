/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:56:05 by jgarcia           #+#    #+#             */
/*   Updated: 2023/10/03 16:11:08 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/raycast.h"

void render_menu(t_raydata *raydata) {
	clear_buffer(raydata);
	draw_menu(raydata);
	return ;
}

void render_game(t_raydata *raydata) {
	clear_buffer(raydata);
	draw_rays(raydata);
	draw_minimap(raydata);
	nmi_ai(raydata);
	draw_player(raydata);
	mlx_put_image_to_window(raydata->mlx,
							raydata->mlx_win,
							raydata->img_buffer->img,
							0, 0);
}
void render_game_over(t_raydata *raydata) {
	return ;
}
void render_win(t_raydata *raydata) {
	return ;
}

int	render(t_raydata *raydata)
{
	void (*render_state[4])(t_raydata *raydata);

	render_state[MENU] = render_menu;
	render_state[PLAYING] = render_game;
	render_state[GAME_OVER] = render_game_over;
	render_state[WIN] = render_win;
	render_state[raydata->game_state](raydata);
	return (0);
}
