/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 18:40:28 by avassor           #+#    #+#             */
/*   Updated: 2023/10/11 14:09:38 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/cub3d.h"

/* **************************************************************************
 * clean_raw:
 * - free the raw map
 ************************************************************************** */

void	clean_raw(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->lines)
	{
		gc_del(data->raw[i]);
		i++;
	}
	if (i)
	{
		gc_del(data->raw);
		data->raw = NULL;
	}
}

/* **************************************************************************
 * init_alloc:
 * - allocate the data structure
 ************************************************************************** */

_Bool	init_alloc(t_data *data)
{
	data->arg = (t_arg *)gc_alloc(1, sizeof(t_arg));
	data->arg->rgb_c = (t_color *)gc_alloc(1, sizeof(t_color));
	if (!data->arg)
		return (free(data), data->err = MLLOC, 1);
	if (!data->arg->rgb_c)
		return (free(data), data->err = MLLOC, 1);
	data->arg->rgb_f = (t_color *)gc_alloc(1, sizeof(t_color));
	if (!data->arg->rgb_f)
		return (free(data), free(data->arg->rgb_f), data->err = MLLOC, 1);
	return (0);
}

/* **************************************************************************
 * map_op:
 * - check the map
 ************************************************************************** */

_Bool	map_op(t_data *data, char **raw, int i, int j)
{
	if ((!j || (j + 1)  == data->mlines))
	{
		if (chk_bottop(data, raw[i], j))
			return (1);
	}
	else
	{
		if (chk_line(data, raw[i], j))
			return (1);
	}
	return (0);
}
