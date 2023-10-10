/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 18:43:37 by avassor           #+#    #+#             */
/*   Updated: 2023/10/10 15:56:21 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/cub3d.h"

_Bool	copy_id(t_data *data, char **fill, char *raw)
{
	int	i;

	i = 0;
	*fill = (char *)gc_alloc((ft_strlen(&raw[5]) + 1), sizeof(char));
	if (!*fill)
		return (data->err = MLLOC, 1);
	ft_strcpy(&raw[5], *fill);
	i = ft_strlen(*fill);
	ft_strcpy("\0", *fill + i - 1);
	i = 0;
	raw[i++] = '\n';
	while (raw[i])
		raw[i++] = '\0';
	return (0);
}

_Bool	copy_nbr(t_data *data, int *arr, char *raw)
{
	int		i;
	int		j;

	j = 0;
	data->k = 0;
	while (raw[j] && raw[j] != '\n')
	{
		i = j;
		if (data->k >= 3)
			return (data->err = ARGRR, 1);
		while (raw[j] && raw[j] != ',' && raw[j] != '\n')
		{
			if (!(raw[j] >= '0' && raw[j] <= '9'))
				return (data->err = ARGRR, 1);
			j++;
		}
		if (convert_nbr(data, arr, &raw[i], j - i))
			return (1);
		if (raw[j] == ',')
			j++;
	}
	clear_line(raw - 2);
	return (0);
}

_Bool	search_id(t_data *data, char **fill, char *id)
{
	int		i;

	i = 0;
	while (i <= data->lines)
	{
		if (!ft_strncmp(id, data->raw[i], 5))
			return (copy_id(data, fill, data->raw[i]));
		i++;
	}
	data->err = NOID;
	return (1);
}

_Bool	search_id_nbr(t_data *data, int *arr, char *id)
{
	int		i;

	i = 0;
	while (i <= data->lines)
	{
		if (!ft_strncmp(id, data->raw[i], 2))
			return (copy_nbr(data, arr, &data->raw[i][2]));
		i++;
	}
	return (1);
}

_Bool	pars_map(t_data *data)
{
	if (search_id(data, &data->arg->no, "NO ./"))
		return (1);
	if (search_id(data, &data->arg->so, "SO ./"))
		return (1);
	if (search_id(data, &data->arg->we, "WE ./"))
		return (1);
	if (search_id(data, &data->arg->ea, "EA ./"))
		return (1);
	if (search_id_nbr(data, data->arg->f, "F "))
		return (1);
	if (search_id_nbr(data, data->arg->c, "C "))
		return (1);
	if (search_map(data, data->raw))
		return (1);
	return (0);
}
