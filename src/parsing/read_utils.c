/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 18:34:28 by avassor           #+#    #+#             */
/*   Updated: 2023/09/30 22:22:55 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/cub3d.h"

_Bool	copy_line(t_data *data, char *line)
{
	data->raw[data->lines] = (char *)gc_alloc((ft_strlen(line) + 1),
			sizeof(char));
	if (!data->raw[data->lines])
		return (data->err = MLLOC, clean_raw(data), 1);
	ft_strcpy(line, data->raw[data->lines]);
	return (0);
}

_Bool	upscale_raw(t_data *data)
{
	char	**new;
	int		count;

	count = 0;
	new = (char **)gc_alloc((data->lines + 1), sizeof(char *));
	if (!new)
		return (data->err = MLLOC, 1);
	while (count < data->lines)
	{
		new[count] = (char *)gc_alloc((
					ft_strlen(data->raw[count]) + 1), sizeof(char));
		if (!new[count])
			return (data->err = MLLOC, clean_raw(data), 1);
		ft_strcpy(data->raw[count], new[count]);
		count++;
	}
	new[data->lines] = NULL;
	clean_raw(data);
	data->raw = new;
	return (0);
}

void	clear_line(char *raw)
{
	int	i;

	i = 1;
	raw[0] = '\n';
	while (raw[i])
	{
		raw[i] = '\0';
		i++;
	}
}

int	is_origin(char id)
{
	if (id == 'E')
		return (1);
	else if (id == 'S')
		return (2);
	else if (id == 'W')
		return (3);
	else if (id == 'N')
		return (4);
	return (0);
}

void	do_conv(t_arg *arg, int i, int j)
{
	if (is_origin(arg->map[i][j]))
		arg->fmap[i][j] = -is_origin(arg->map[i][j]);
	else
		arg->fmap[i][j] = arg->map[i][j] - '0';
}
