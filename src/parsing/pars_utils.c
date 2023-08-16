/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:33:29 by avassor           #+#    #+#             */
/*   Updated: 2023/08/16 12:28:58 by avassor          ###   ########.fr       */
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
	// while (line[i] && line[i] != '\n')
	// {
	// 	if (line[i] != ' ')
	// 		return (data->err = MAPERROR, 1);
	// 	i++;
	// }
	return (chk_line(data, line, j));
}

_Bool	chk_line(t_data *data, char *line, int j)
{
	int	i;

	i = 0;
	data->arg->map[j] = (char *)malloc(sizeof(char) * ft_strlen(line));
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
	while (raw[i][0] == '\n')
		i++;
	data->arg->map = (char **)malloc(sizeof(char) * (data->lines - i));
	if (!data->arg->map)
		return (data->err = MLLOC, 1);
	while (i <= data->lines)
	{
		if ((!j || i == data->lines) && chk_bottop(data, raw[i], j))
			return (1);
		else
			if (chk_line(data, raw[i], j))
				return (1);
		i++;
		j++;
	}
	if (!data->pars.N && !data->pars.S && !data->pars.E && !data->pars.W)
		return (data->err = MAPERROR, 1);
	return (0);
}

_Bool	convert_nbr(t_data *data, int *arr, char *raw, int l, int k)
{
	char	*tmp;

	tmp = NULL;
	tmp = (char *)malloc(sizeof(char) * (l + 1));
	if (!tmp)
		return (data->err = MLLOC, 1);
	ft_strncpy(raw, tmp, l);
	arr[k] = ft_atoi(tmp);
	free(tmp);
	if (arr[k] < 0 || arr[k] > 255)
		return (data->err = ARGRR, 1);
	return (0);
}

_Bool	chk_origin(t_data *data, char *line, char id, int i)
{
	if (!i || i == ft_strlen(line) - 1)
		return (data->err = MAPERROR, 1);
	if (data->pars.N || data->pars.S || data->pars.E || data->pars.W)
		return (data->err = MAPERROR, 1);
	if (id == 'N')
		return (data->pars.N = 1, 0);
	else if (id == 'S')
		return (data->pars.S = 1, 0);
	else if (id == 'E')
		return (data->pars.E = 1, 0);
	else if (id == 'W')
		return (data->pars.W = 1, 0);
	else
		return (data->err = MAPERROR, 1);
}
