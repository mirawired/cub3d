/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 10:05:10 by corecaps          #+#    #+#             */
/*   Updated: 2023/09/25 10:05:13 by corecaps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "bfs.h"
t_queue *create_queue(int capacity) {
	t_queue *queue = gc_alloc(1, sizeof(t_queue));
	queue->capacity = capacity;
	queue->front = 0;
	queue->rear = 0;
	queue->nodes = gc_alloc(capacity, sizeof(t_queue_node));
	return (queue);
}
void enqueue(t_queue *queue, t_queue_node node) {
	queue->nodes[queue->rear] = node;
	queue->rear++;
}
t_queue_node dequeue(t_queue *queue) {
	t_queue_node node = queue->nodes[queue->front];
	queue->front++;
	return (node);
}
t_int_point bfs(t_raydata *data, t_int_point start, t_int_point end) {
	t_int_point dir[4] = {{0, 1},
						  {1, 0},
						  {0, -1},
						  {-1, 0}};
	t_queue *queue = create_queue(1000);
	int **map = data->map;
	int map_width = data->map_width;
	int map_height = data->map_height;
	t_int_point parent[map_width][map_height];
	int **visited = gc_alloc(map_width + 1, sizeof(int *));
	for (int i = 0; i < map_width; i++) {
		visited[i] = gc_alloc(map_height + 1, sizeof(int));
	}
	enqueue(queue, (t_queue_node) {start, 0});
	visited[start.x][start.y] = 1;
	while (queue->front < queue->rear) {
		t_queue_node node = dequeue(queue);
		if (node.point.x == end.x && node.point.y == end.y){
			while (node.point.x != start.x || node.point.y != start.y) {
				t_int_point tmp = parent[node.point.x][node.point.y];
				if (tmp.x == start.x && tmp.y == start.y)
					break;
				node.point = tmp;
			}
			gc_del(queue);
			return (node.point);
		}
		for (int i = 0; i < 4; i++) {
			int x = node.point.x + dir[i].x;
			int y = node.point.y + dir[i].y;
			if (x >= 0 && x < map_width && y >= 0 && y < map_height && map[y][x] == 0 && visited[x][y] == 0) {
				enqueue(queue, (t_queue_node) {{x, y}, node.distance + 1});
				visited[x][y] = 1;
				parent[x][y] = node.point;
			}
		}
	}
	gc_del(queue);
	return ((t_int_point) {0, 0});
}
