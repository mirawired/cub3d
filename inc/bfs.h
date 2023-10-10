/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corecaps <corecaps@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:22:30 by corecaps          #+#    #+#             */
/*   Updated: 2023/10/10 16:22:34 by corecaps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BFS_H
# define BFS_H
# include "cub3d.h"

typedef struct queue_node {
	t_int_point	point;
	int			distance;
}	t_queue_node;
typedef struct queue {
	t_queue_node	*nodes;
	int				front;
	int				rear;
	int				capacity;
}	t_queue;
typedef struct s_bfs
{
	t_queue			*queue;
	t_queue_node	node;
	t_int_point		**parent;
	int				**map;
	int				map_width;
	int				map_height;
	int				**visited;
	int				i;
}	t_bfs;
t_int_point		fill_node_end(t_bfs *bfs, t_int_point start);
void			fill_node(t_bfs *bfs, t_int_point *dir);
t_int_point		*alloc_dir(void);
t_int_point		**alloc_parent(int map_width, int map_height);
t_bfs			*init_bfs_structs(t_raydata *data);
t_queue			*create_queue(int capacity);
void			enqueue(t_queue *queue, t_queue_node node);
t_queue_node	dequeue(t_queue *queue);
#endif
