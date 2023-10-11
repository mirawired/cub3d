/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corecaps <corecaps@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:51:43 by corecaps          #+#    #+#             */
/*   Updated: 2023/10/10 13:51:47 by corecaps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

/* **************************************************************************
 * draw_menu:
 * - if the menu is not loaded, load it
 * - draw the menu
 ************************************************************************** */

void	draw_menu(t_raydata *raydata)
{
	static int	width = 0;
	static int	height = 0;

	if (raydata->img_menu == NULL)
	{
		raydata->img_menu = gc_alloc(1, sizeof(t_buffer));
		raydata->img_menu->img = mlx_xpm_file_to_image(raydata->mlx,
				"menu.xpm", &width, &height);
		raydata->img_menu->address
			= mlx_get_data_addr(raydata->img_menu->img,
				&raydata->img_menu->bit_per_pixel,
				&raydata->img_menu->line_length,
				&raydata->img_menu->endian);
	}
	else
	{
		mlx_put_image_to_window(raydata->mlx,
			raydata->mlx_win,
			raydata->img_menu->img,
			0, 0);
	}
}

void	draw_loose(t_raydata *raydata)
{
	static int	width = 0;
	static int	height = 0;

	if (raydata->img_loose == NULL)
	{
		raydata->img_loose = gc_alloc(1, sizeof(t_buffer));
		raydata->img_loose->img = mlx_xpm_file_to_image(raydata->mlx,
				"gameover.xpm", &width, &height);
		raydata->img_loose->address
			= mlx_get_data_addr(raydata->img_menu->img,
				&raydata->img_menu->bit_per_pixel,
				&raydata->img_menu->line_length,
				&raydata->img_menu->endian);
	}
	else
	{
		mlx_put_image_to_window(raydata->mlx,
			raydata->mlx_win,
			raydata->img_loose->img,
			0, 0);
	}
}
