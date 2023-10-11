/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corecaps <corecaps@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:20:59 by corecaps          #+#    #+#             */
/*   Updated: 2023/10/10 13:25:50 by corecaps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"
#include "../../../inc/bfs.h"

/* **************************************************************************
 * create_queue:
 * - create a queue with a capacity of capacity
 ************************************************************************** */

t_queue	*create_queue(int capacity)
{
	t_queue	*queue;

	queue = (t_queue *)gc_alloc(1, sizeof(t_queue));
	queue->capacity = capacity;
	queue->front = 0;
	queue->rear = 0;
	queue->nodes = gc_alloc(capacity, sizeof(t_queue_node));
	return (queue);
}

/* **************************************************************************
 * enqueue:
 * - add a node to the queue
 ************************************************************************** */

void	enqueue(t_queue *queue, t_queue_node node)
{
	queue->nodes[queue->rear] = node;
	queue->rear++;
}

/* **************************************************************************
 * dequeue:
 * - remove a node from the queue
 ************************************************************************** */

t_queue_node	dequeue(t_queue *queue)
{
	t_queue_node	node;

	node = queue->nodes[queue->front];
	queue->front++;
	return (node);
}
