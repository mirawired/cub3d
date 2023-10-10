/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corecaps <corecaps@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:49:31 by corecaps          #+#    #+#             */
/*   Updated: 2023/10/10 15:49:33 by corecaps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/cub3d.h"

void	ray_inc_v(t_r *r)
{
	r->sideDist.y += r->deltaDist.y;
	r->MapY += r->stepY;
	r->side = 1;
}

void	ray_inc_h(t_r *r)
{
	r->sideDist.x += r->deltaDist.x;
	r->MapX += r->stepX;
	r->side = 0;
}
