/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:56:05 by jgarcia           #+#    #+#             */
/*   Updated: 2023/09/11 10:56:09 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/raycast.h"

int render(t_raydata *raydata) {
	clear_buffer(raydata);
	draw_rays(raydata);
	draw_minimap(raydata);
	nmi_ai(raydata);
	draw_player(raydata);
	mlx_put_image_to_window(raydata->mlx,
							raydata->mlx_win,
							raydata->img_buffer->img,
							0, 0);
	return (0);
}