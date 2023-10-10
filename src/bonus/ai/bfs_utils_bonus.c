/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corecaps <corecaps@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:19:40 by corecaps          #+#    #+#             */
/*   Updated: 2023/10/10 13:19:42 by corecaps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"
#include "../../../inc/bfs.h"

/* **************************************************************************
 * alloc_dir:
 * - allocate the direction array
 ************************************************************************** */

t_int_point	*alloc_dir(void)
{
	t_int_point	*dir;

	dir = gc_alloc(4, sizeof(t_int_point));
	dir[0].x = 0;
	dir[0].y = 1;
	dir[1].x = 1;
	dir[1].y = 0;
	dir[2].x = 0;
	dir[2].y = -1;
	dir[3].x = -1;
	dir[3].y = 0;
	return (dir);
}

/* **************************************************************************
 * alloc_parent:
 * - allocate the parent array
 ************************************************************************** */

t_int_point	**alloc_parent(int map_width, int map_height)
{
	t_int_point	**parents;
	int			i;

	i = 0;
	parents = gc_alloc(map_width, sizeof(t_int_point *));
	while (i < map_width)
		parents[i++] = gc_alloc(map_height, sizeof(t_int_point));
	return (parents);
}

/* **************************************************************************
 * init_bfs_structs:
 * - initialize the bfs structs
 ************************************************************************** */

t_bfs	*init_bfs_structs(t_raydata *data)
{
	t_bfs	*bfs;

	bfs = (t_bfs *)gc_alloc(1, sizeof(t_bfs));
	bfs->map_width = data->map_width;
	bfs->map_height = data->map_height;
	bfs->parent = alloc_parent(bfs->map_width, bfs->map_height);
	bfs->queue = create_queue(1000);
	bfs->map = data->map;
	bfs->visited = gc_alloc(bfs->map_width + 1, sizeof(int *));
	return (bfs);
}
