/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:49:31 by corecaps          #+#    #+#             */
/*   Updated: 2023/10/10 16:38:17 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/cub3d.h"

void	ray_inc_v(t_r *r)
{
	r->sideDist.y += r->deltaDist.y;
	r->mapy += r->stepY;
	r->side = 1;
}

void	ray_inc_h(t_r *r)
{
	r->sideDist.x += r->deltaDist.x;
	r->mapx += r->stepX;
	r->side = 0;
}
