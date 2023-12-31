/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 18:43:37 by avassor           #+#    #+#             */
/*   Updated: 2023/10/11 16:10:04 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/cub3d.h"

_Bool	copy_id(t_data *data, char **fill, char *raw)
{
	int		i;
	int		fd;

	i = 0;
	fd = 0;
	*fill = (char *)gc_alloc((ft_strlen(&raw[3 + find_id(&raw[3])]) + 1),
			sizeof(char));
	if (!*fill)
		return (data->err = MLLOC, 1);
	ft_strcpy(&raw[3 + find_id(&raw[3])], *fill);
	i = ft_strlen(*fill);
	ft_strcpy("\0", *fill + i - 1);
	i = 0;
	raw[i++] = '\n';
	while (raw[i])
		raw[i++] = '\0';
	fd = open(*fill, O_RDONLY);
	if (fd == -1)
		return (data->err = RFD, 1);
	if (is_dir(*fill) || ko_ext(*fill))
		return (close(fd), data->err = EXT2, 1);
	else
		close(fd);
	return (0);
}

_Bool	copy_nbr(t_data *data, int *arr, char *raw)
{
	int		i;
	int		j;

	j = find_id(raw);
	data->k = 0;
	while (raw[j] && raw[j] != '\n')
	{
		if (data->k >= 3)
			return (data->err = ARGRR, 1);
		while (raw[j] == ' ' || raw[j] == ',')
			j++;
		i = j;
		if (!(raw[j] >= '0' && raw[j] <= '9'))
			return (data->err = ARGRR, 1);
		while (raw[j] && raw[j] >= '0' && raw[j] <= '9')
			j++;
		if (convert_nbr(data, arr, &raw[i], j - i))
			return (1);
	}
	if (data->k != 3)
		return (data->err = ARGRR, 1);
	clear_line(raw - 2);
	return (0);
}

_Bool	search_id(t_data *data, char **fill, char *id)
{
	int		i;

	i = 0;
	while (i <= data->lines)
	{
		if (!ft_strncmp(data, id, data->raw[i], 3))
		{
			if (data->last_index < i)
				data->last_index = i;
			return (copy_id(data, fill, data->raw[i]));
		}
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
		if (!ft_strncmp(data, id, data->raw[i], 2))
		{
			if (data->last_index < i)
				data->last_index = i;
			return (copy_nbr(data, arr, &data->raw[i][2]));
		}
		i++;
	}
	return (data->err = ARGRR, 1);
}

_Bool	pars_map(t_data *data)
{
	data->last_index = 0;
	if (search_id(data, &data->arg->no, "NO "))
		return (1);
	if (search_id(data, &data->arg->so, "SO "))
		return (1);
	if (search_id(data, &data->arg->we, "WE "))
		return (1);
	if (search_id(data, &data->arg->ea, "EA "))
		return (1);
	if (search_id_nbr(data, data->arg->f_color, "F "))
		return (1);
	if (search_id_nbr(data, data->arg->c_color, "C "))
		return (1);
	if (search_map(data, data->raw))
		return (1);
	return (0);
}
