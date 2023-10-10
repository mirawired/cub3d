/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 12:23:01 by avassor           #+#    #+#             */
/*   Updated: 2023/10/10 16:00:03 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/cub3d.h"

/* **************************************************************************
 * init_data:
 * - allocate the data structure
 * - initialize the data structure
 ************************************************************************** */

t_data	*init_data(void)
{
	t_data	*data;

	data = (t_data *)gc_alloc(1, sizeof(t_data));
	if (!data || init_alloc(data))
		return (NULL);
	data->arg->no = NULL;
	data->arg->so = NULL;
	data->arg->we = NULL;
	data->arg->ea = NULL;
	data->arg->map = NULL;
	data->arg->fmap = NULL;
	data->raw = NULL;
	data->err = 0;
	data->fd = -1;
	data->lines = -1;
	data->pars.n = 0;
	data->pars.s = 0;
	data->pars.e = 0;
	data->pars.w = 0;
	data->arg->height = -1;
	data->arg->width = -1;
	return (data);
}

/* **************************************************************************
 * convert_rgb:
 * - convert the rgb values to an integer
 ************************************************************************** */

_Bool	convert_rgb(t_arg *arg)
{
	arg->rgbc->color = ((arg->c[0] << 16) | (arg->c[1] << 8) | arg->c[2]);
	arg->rgbf->color = ((arg->f[0] << 16) | (arg->f[1] << 8) | arg->f[2]);
	return (0);
}

/* **************************************************************************
 * to_integers:
 * - fill the integer map
 * - fill the integer map with 1 if the map is not closed
 * - convert the rgb values to an integer
 ************************************************************************** */

_Bool	to_integers(t_data *data, t_arg *arg)
{
	int	i;
	int	j;

	i = 0;
	arg->fmap = (int **)gc_alloc(arg->height, sizeof(int *));
	if (!arg->fmap)
		return (data->err = MLLOC, 1);
	while (i < arg->height)
	{
		j = 0;
		arg->fmap[i] = (int *)gc_alloc(arg->width, sizeof(int));
		if (!arg->fmap[i])
			return (data->err = MLLOC, 1);
		while (arg->map[i][j])
			do_conv(arg, i, j++);
		while (j < arg->width)
		{
			arg->fmap[i][j] = 1;
			j++;
		}
		i++;
	}
	return (convert_rgb(arg));
}

/* **************************************************************************
 * convert_map:
 * - convert the map to integers
 ************************************************************************** */

_Bool	convert_map(t_data *data, t_arg *arg)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	arg->height = data->mlines;
	while (i < data->mlines)
	{
		j = 0;
		while (arg->map[i][j])
			j++;
		if (j > k)
			k = j;
		i++;
	}
	arg->width = k;
	return (to_integers(data, arg));
}

/* **************************************************************************
 * main:
 * - initialize the data structure
 * - check the arguments
 * - get the arguments
 * - parse the map
 * - convert the map to integers
 * - start the raycasting engine and launch the game
 ************************************************************************** */

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	if (argc != 2)
		return (rror(NOARG, NULL));
	data = init_data();
	if (!data)
		return (rror(MLLOC, NULL));
	if (chk_arg(data, argv[1]))
		return (rror(data->err, data));
	if (get_arg(data))
		return (rror(data->err, data));
	if (pars_map(data) || convert_map(data, data->arg))
		return (rror(1, data));
	if (raycast(data->arg))
		return (rror(1, data));
	gc_free();
	return (EXIT_SUCCESS);
}
