/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:55:17 by jgarcia           #+#    #+#             */
/*   Updated: 2023/09/30 13:19:54 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/raycast.h"

/* **************************************************************************
 * clean_exit :
 * - Free all allocated memory
 * - Exit the program
 ************************************************************************** */
void	clean_exit(t_raydata *raydata)
{
	mlx_destroy_image(raydata->mlx, raydata->img_buffer->img);
	if (raydata->img_menu)
		mlx_destroy_image(raydata->mlx, raydata->img_menu->img);
	mlx_destroy_window(raydata->mlx, raydata->mlx_win);
	mlx_destroy_display(raydata->mlx);
	free(raydata->mlx);
	gc_free();
	exit(0);
}

/* **************************************************************************
 * key_menu :
 * - Handle key pressed in MENU state
 ************************************************************************** */

void	key_menu(int keycode, t_raydata *raydata)
{
	if (keycode == 65307)
		clean_exit(raydata);
	if (keycode == 32)
		raydata->game_state = PLAYING;
}

/* **************************************************************************
 * key_playing :
 * - Handle key pressed in PLAYING state
 ************************************************************************** */

void	key_playing(int keycode, t_raydata *raydata)
{
	if (keycode == 65307)
		clean_exit(raydata);
	if (keycode == 97 || keycode == 65361)
		turn_left(raydata);
	if (keycode == 100 || keycode == 65363)
		turn_right(raydata);
	if (keycode == 101)
		strafe_right(raydata);
	if (keycode == 113)
		strafe_left(raydata);
	if (keycode == 119 || keycode == 65362)
		move_forward(raydata);
	if (keycode == 115 || keycode == 65364)
		move_backward(raydata);
	if (keycode == 32)
		raydata->game_state = MENU;
}

/* **************************************************************************
 * key_end :
 * - Handle key pressed in GAME_OVER or WIN state
 ************************************************************************** */

void	key_end(int keycode, t_raydata *raydata)
{
	if (keycode == 65307)
		clean_exit(raydata);
	if (keycode == 32)
		raydata->game_state = MENU;
}

/* **************************************************************************
 * key_pressed :
 * - call the right keypressed handling function depending on the game state
 ************************************************************************** */

int	key_pressed(int keycode, t_raydata *raydata)
{
	void	(*hook_state[4])(int keycode, t_raydata *raydata);

	hook_state[MENU] = key_menu;
	hook_state[PLAYING] = key_playing;
	hook_state[GAME_OVER] = key_end;
	hook_state[WIN] = key_end;
	hook_state[raydata->game_state](keycode, raydata);
	return (0);
}
