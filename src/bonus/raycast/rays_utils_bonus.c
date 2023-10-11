/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:49:31 by corecaps          #+#    #+#             */
/*   Updated: 2023/10/11 10:53:34 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

void	ray_inc_v(t_r *r)
{
	r->side_dist.y += r->delta_dist.y;
	r->map_y += r->step_y;
	r->side = 1;
}

void	ray_inc_h(t_r *r)
{
	r->side_dist.x += r->delta_dist.x;
	r->map_x += r->step_x;
	r->side = 0;
}
