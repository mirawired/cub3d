/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_add_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 22:12:06 by avassor           #+#    #+#             */
/*   Updated: 2023/10/11 10:52:29 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/raycast.h"

t_r	*r_init(t_raydata *data)
{
	t_r	*r;

	r = (t_r *)gc_alloc(1, sizeof(t_r));
	r->ray_color.color = 0x0000FF;
	r->grid_size_x = WIDTH / data->map_width;
	r->grid_size_y = HEIGHT / data->map_height;
	r->pos.x = data->player->pos.x / r->grid_size_x;
	r->pos.y = data->player->pos.y / r->grid_size_y;
	return (r);
}

void	set_color(t_color *color, t_texture *texture, float txtr_pos, t_r *r)
{
	*color = texture->texture[(int)txtr_pos * texture->width
		+ (int)r->wall_x];
	color->s_rgb.r -= (int)r->perp_wall_dist;
	color->s_rgb.g -= (int)r->perp_wall_dist;
	color->s_rgb.b -= (int)r->perp_wall_dist;
}
