/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 12:23:01 by avassor           #+#    #+#             */
/*   Updated: 2023/08/25 12:06:21 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/cub3d.h"

t_data	*init_data(void)
{
	t_data	*data;

	data = (t_data *)gc_alloc(1,sizeof(t_data));
	if (!data)
		return (NULL);
	data->arg = (t_arg *) gc_alloc(1,sizeof(t_arg));
	if (!data->arg)
		return (free(data), NULL);
	data->arg->NO = NULL;
	data->arg->SO = NULL;
	data->arg->WE = NULL;
	data->arg->EA = NULL;
	data->arg->EA = NULL;
	data->arg->map = NULL;
	data->arg->fmap = NULL;
	data->raw = NULL;
	data->err = 0;
	data->fd = -1;
	data->lines = -1;
	data->pars.N = 0;
	data->pars.S = 0;
	data->pars.E = 0;
	data->pars.W = 0;
	data->arg->height = -1;
	data->arg->width = -1;
	data->arg->rgbC = (t_color *)malloc(sizeof(t_color));
	data->arg->rgbF = (t_color *)malloc(sizeof(t_color));
	return (data);
}

_Bool	convert_rgb(t_arg *arg)
{
	arg->rgbC->color = ((arg->C[0] << 16) | (arg->C[1] << 8) | arg->C[2]);
	arg->rgbF->color = ((arg->F[0] << 16) | (arg->F[1] << 8) | arg->F[2]);
	return (0);
}

_Bool	to_integers(t_data *data, t_arg *arg)
{
	int	i;
	int	j;

	i = 0;
	arg->fmap = (int **)gc_alloc( arg->height,sizeof(int *));
	if (!arg->fmap)
		return (data->err = MLLOC, 1);
	while (i < arg->height)
	{
		j = 0;
		arg->fmap[i] = (int *) gc_alloc(  arg->width,sizeof(int));
		if (!arg->fmap[i])
			return (data->err = MLLOC, 1);
		while (arg->map[i][j])
		{
            if (is_origin(arg->map[i][j]))
                arg->fmap[i][j] = -2;
            else
                arg->fmap[i][j] = arg->map[i][j] - '0';
			j++;
		}
		while (j < arg->width)
		{
			arg->fmap[i][j] = 1;
			j++;
		}
		i++;
	}
	return (convert_rgb(arg));
}

_Bool	convert_map(t_data *data, t_arg *arg)
{
	(void)data;
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	arg->height = data->mlines;
	i = 0;
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

// PRINT RAW
	// int i = 0;
	// while (data->raw[i] && i < data->lines)
	// {
	// 	printf("%s", data->raw[i]);
	// 	i++;
	// }
	//
