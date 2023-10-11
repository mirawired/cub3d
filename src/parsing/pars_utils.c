/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:33:29 by avassor           #+#    #+#             */
/*   Updated: 2023/10/11 14:48:18 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/cub3d.h"

_Bool	chk_bottop(t_data *data, char *line, int j)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == ' ')
			line[i] = '1';
		else if (line[i] != '1')
			return (data->err = MAPERROR, 1);
		i++;
	}
	return (chk_line(data, line, j));
}

_Bool	chk_line(t_data *data, char *line, int j)
{
	int	i;

	i = 0;
	data->arg->map[j] = (char *)gc_alloc(ft_strlen(line) + 1, sizeof(char));
	if (!data->arg->map[j])
		return (data->err = MLLOC, 1);
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == ' ')
			line[i] = '1';
		else if (is_origin(line[i]))
		{
			if (chk_origin(data, line, line[i], i))
				return (data->err = MAPERROR, 1);
		}
		else
			if (line[i] != '0' && line[i] != '1')
				return (data->err = MAPERROR, 1);
		data->arg->map[j][i] = line[i];
		i++;
	}
	data->arg->map[j][i] = '\0';
	return (chk_edges(data, data->arg->map[j][0], data->arg->map[j][i - 1]));
}

_Bool	search_map(t_data *data, char **raw)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (raw[i] && raw[i][0] == '\n')
		i++;
	data->endmap = i + find_end_map(data, raw, i);
	data->mlines = data->endmap - i;
	data->arg->map = (char **)gc_alloc((data->mlines + 1), sizeof(char *));
	if (!data->arg->map)
		return (data->err = MLLOC, 1);
	data->arg->map[data->mlines] = NULL;
	while (i < data->endmap)
	{
		if (map_op(data, raw, i, j))
			return (data->err = MAPERROR, 1);
		i++;
		j++;
	}
	if (!data->pars.n && !data->pars.s && !data->pars.e && !data->pars.w)
		return (data->err = MAPERROR, 1);
	return (0);
}

_Bool	convert_nbr(t_data *data, int *arr, char *raw, int l)
{
	char	*tmp;

	tmp = NULL;
	tmp = (char *)gc_alloc(l + 1, sizeof(char));
	if (!tmp)
		return (data->err = MLLOC, 1);
	ft_strncpy(raw, tmp, l);
	arr[data->k] = ft_atoi(tmp);
	if (arr[data->k] < 0 || arr[data->k] > 255)
		return (data->err = ARGRR, 1);
	data->k++;
	return (0);
}

_Bool	chk_origin(t_data *data, char *line, char id, int i)
{
	if (!i || i == ft_strlen(line) - 1)
		return (data->err = MAPERROR, 1);
	if (data->pars.n || data->pars.s || data->pars.e || data->pars.w)
		return (data->err = MAPERROR, 1);
	if (id == 'N')
		return (data->pars.n = 1, 0);
	else if (id == 'S')
		return (data->pars.s = 1, 0);
	else if (id == 'E')
		return (data->pars.e = 1, 0);
	else if (id == 'W')
		return (data->pars.w = 1, 0);
	else
		return (data->err = MAPERROR, 1);
}
