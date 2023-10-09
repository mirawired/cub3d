/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:53:56 by jgarcia           #+#    #+#             */
/*   Updated: 2023/09/11 11:08:09 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/cub3d.h"
#include "./../../inc/gc.h"
#include <limits.h>

/* **************************************************************************
 * gc_check_double:
 * - Check if the pointer is already in the garbage collector.
 ************************************************************************** */

int	gc_check_double(t_garbage *gc, void *ptr)
{
	t_garbage	*tmp;

	tmp = gc;
	while (tmp)
	{
		if (tmp->ptr == ptr)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

/* **************************************************************************
 * gc_add:
 * - add a pointer to the garbage collector.
 ************************************************************************** */

t_garbage	**gc_add(t_garbage *ptr)
{
	static t_garbage	*garbage = NULL;
	t_garbage			*new;

	if (ptr == NULL)
		return (&garbage);
	if (garbage && gc_check_double(garbage, ptr))
		return (&garbage);
	new = malloc(sizeof(t_garbage));
	if (!new)
		return (NULL);
	new->ptr = ptr;
	if (garbage)
		new->next = garbage;
	else
		new->next = NULL;
	garbage = new;
	return (&garbage);
}

/* **************************************************************************
 * gc_free:
 * - free all the pointers in the garbage collector.
 ************************************************************************** */

void	gc_free(void)
{
	t_garbage	*tmp;
	t_garbage	**garbage;
	t_garbage	*cursor;

	garbage = gc_add(NULL);
	if (!(*garbage))
		return ;
	cursor = *garbage;
	while (cursor)
	{
		tmp = cursor;
		cursor = cursor->next;
		free(tmp->ptr);
		free(tmp);
	}
	(*garbage) = NULL;
}

/* **************************************************************************
 * gc_del:
 * - delete a pointer from the garbage collector.
 ************************************************************************** */

int	gc_del(void *ptr)
{
	t_garbage	*cursor;
	t_garbage	**gc;
	t_garbage	*prev;

	gc = gc_add(NULL);
	cursor = *gc;
	if (!cursor)
		return (0);
	prev = NULL;
	while (cursor)
	{
		if (cursor->ptr == ptr)
		{
			if (prev)
				prev->next = cursor->next;
			else
				(*gc) = cursor->next;
			free(cursor->ptr);
			free(cursor);
			return (1);
		}
		prev = cursor;
		cursor = cursor->next;
	}
	return (0);
}

/* **************************************************************************
 * gc_alloc:
 * - allocate memory and add it to the garbage collector.
 * - memory is initialized to 0.
 ************************************************************************** */

void	*gc_alloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = ft_calloc(nmemb, size);
	if (!ptr)
		return (NULL);
	gc_add(ptr);
	return (ptr);
}
