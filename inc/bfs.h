//
// Created by corecaps on 9/13/23.
//

#ifndef	BFS_H
  #define BFS_H
  #include "cub3d.h"
typedef struct queue_node {
	t_int_point point;
	int distance;
} t_queue_node;
typedef struct queue {
	t_queue_node *nodes;
	int front;
	int rear;
	int capacity;
} t_queue;

#endif