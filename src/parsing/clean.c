/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 18:40:28 by avassor           #+#    #+#             */
/*   Updated: 2023/10/10 15:48:24 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/cub3d.h"

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

_Bool	init_alloc(t_data *data)
{
	data->arg = (t_arg *)gc_alloc(1, sizeof(t_arg));
	data->arg->rgbc = (t_color *)gc_alloc(1, sizeof(t_color));
	if (!data->arg)
		return (data->err = MLLOC, 1);
	if (!data->arg->rgbc)
		return (data->err = MLLOC, 1);
	data->arg->rgbf = (t_color *)gc_alloc(1, sizeof(t_color));
	if (!data->arg->rgbf)
		return (free(data->arg->rgbf), data->err = MLLOC, 1);
	return (0);
}

_Bool	map_op(t_data *data, char **raw, int i, int j)
{
	if ((!j || i == data->lines))
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
