/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 10:05:10 by corecaps          #+#    #+#             */
/*   Updated: 2023/10/04 11:05:34 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"
#include "../../../inc/bfs.h"

/* **************************************************************************
 * bfs:
 * - determine the shortest path from start to end
 * - return the first point of the path
 ************************************************************************** */

t_int_point	bfs(t_raydata *data, t_int_point start, t_int_point end)
{
	int				i;
	t_bfs			*bfs;
	t_int_point		*dir;

	dir = alloc_dir();
	bfs = init_bfs_structs(data);
	i = 0;
	while (i < bfs->map_width)
		bfs->visited[i++] = gc_alloc(bfs->map_height + 1, sizeof(int));
	enqueue(bfs->queue, (t_queue_node){start, 0});
	bfs->visited[start.x][start.y] = 1;
	while (bfs->queue->front < bfs->queue->rear)
	{
		bfs->node = dequeue(bfs->queue);
		if (bfs->node.point.x == end.x && bfs->node.point.y == end.y)
			return (fill_node_end(bfs, start));
		fill_node(bfs, dir);
	}
	gc_del(bfs->queue);
	return ((t_int_point){0, 0});
}

/* **************************************************************************
 * fill_node_end:
 * - return the first point of the path
 ************************************************************************** */

t_int_point	fill_node_end(t_bfs *bfs, t_int_point start)
{
	t_int_point		tmp;

	while (bfs->node.point.x != start.x || bfs->node.point.y != start.y)
	{
		tmp = bfs->parent[bfs->node.point.x][bfs->node.point.y];
		if (tmp.x == start.x && tmp.y == start.y)
			break ;
		bfs->node.point = tmp;
	}
	gc_del(bfs->queue);
	return (bfs->node.point);
}

/* **************************************************************************
 * fill_node:
 * - fill the queue with the next nodes
 ************************************************************************** */

void	fill_node(t_bfs *bfs, t_int_point *dir)
{
	int				i;
	int				x;
	int				y;

	i = 0;
	while (i < 4)
	{
		x = bfs->node.point.x + dir[i].x;
		y = bfs->node.point.y + dir[i].y;
		if (x >= 0 && x < bfs->map_width && y >= 0 && y < bfs->map_height
			&& bfs->map[y][x] == 0 && bfs->visited[x][y] == 0)
		{
			enqueue(bfs->queue, (t_queue_node){{x, y}, bfs->node.distance + 1});
			bfs->visited[x][y] = 1;
			bfs->parent[x][y] = bfs->node.point;
		}
		i++;
	}
}
