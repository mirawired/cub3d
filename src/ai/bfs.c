//
// Created by corecaps on 9/13/23.
//

#include "../../inc/cub3d.h"
#include "../../inc/bfs.h"
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
	t_queue *queue = create_queue(100);
	int **map = data->map;
	int map_width = data->map_width;
	int map_height = data->map_height;
	t_int_point parent[map_height][map_width];
	int **visited = gc_alloc(map_height, sizeof(int *));
	for (int i = 0; i < map_height; i++) {
		visited[i] = gc_alloc(map_width, sizeof(int));
		for (int j = 0; j < map_width; j++)
			visited[i][j] = 0;
	}
	enqueue(queue, (t_queue_node) {start, 0});
	visited[start.y][start.x] = 1;
	while (queue->front < queue->rear) {
		t_queue_node node = dequeue(queue);
		if (node.point.x == end.x && node.point.y == end.y){
			printf("Found path\n");
			while (node.point.x != start.x || node.point.y != start.y) {
				printf("x: %d y: %d\n", node.point.x, node.point.y);
				t_int_point tmp = parent[node.point.y][node.point.x];
				node.point = tmp;
			}
			gc_del(queue);
			return (node.point);
		}
		for (int i = 0; i < 4; i++) {
			int x = node.point.x + dir[i].x;
			int y = node.point.y + dir[i].y;
			if (x >= 0 && x < map_width && y >= 0 && y < map_height && map[x][y] == 0 && visited[y][x] == 0) {
				enqueue(queue, (t_queue_node) {{x, y}, node.distance + 1});
				visited[y][x] = 1;
				parent[y][x] = node.point;
			}
		}
	}
	return ((t_int_point) {0, 0});
}