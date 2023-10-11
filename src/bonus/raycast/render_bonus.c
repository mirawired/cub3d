/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:56:05 by jgarcia           #+#    #+#             */
/*   Updated: 2023/10/09 12:55:01 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/raycast.h"

/* **************************************************************************
 * render_menu:
 * - Clears the buffer
 * - Draws the menu
 ************************************************************************** */

void	render_menu(t_raydata *raydata)
{
	clear_buffer(raydata);
	draw_menu(raydata);
	return ;
}

/* **************************************************************************
 * render_game:
 * - Clears the buffer
 * - Draws the floor and ceiling
 * - Draws the walls
 * - Draws the minimap
 * - launches the AI
 * - Checks for collision with the AI
 * - Draws the player
 * - Puts the buffer on the screen
 ************************************************************************** */

void	render_game(t_raydata *raydata)
{
	clear_buffer(raydata);
	draw_rays(raydata);
	draw_minimap(raydata);
	nmi_ai(raydata);
	if (check_nmi_collision(raydata))
	{
		raydata->game_state = GAME_OVER;
		data_reset(raydata);
	}
	draw_player(raydata);
	mlx_put_image_to_window(raydata->mlx,
		raydata->mlx_win,
		raydata->img_buffer->img,
		0, 0);
}

/* **************************************************************************
 * render_game_over:
 * - Clears the buffer
 * - Draws the buffer on the screen
 * - Draws the game over message
 ************************************************************************** */

void	render_game_over(t_raydata *raydata)
{
	clear_buffer(raydata);
	draw_loose(raydata);
}

/* **************************************************************************
 * render_win:
 * - Clears the buffer
 * - Draws the win message
 ************************************************************************** */

void	render_win(t_raydata *raydata)
{
	clear_buffer(raydata);
	mlx_put_image_to_window(raydata->mlx,
		raydata->mlx_win,
		raydata->img_buffer->img,
		0, 0);
	mlx_string_put(raydata->mlx, raydata->mlx_win,
		100, 100, 0x00FFFFFF, "YOU WIN");
	return ;
}

/* **************************************************************************
 * render:
 * - Calls the right render function depending on the game state
 ************************************************************************** */

int	render(t_raydata *raydata)
{
	void	(*render_state[4])(t_raydata *raydata);

	render_state[MENU] = render_menu;
	render_state[PLAYING] = render_game;
	render_state[GAME_OVER] = render_game_over;
	render_state[WIN] = render_win;
	render_state[raydata->game_state](raydata);
	return (0);
}
