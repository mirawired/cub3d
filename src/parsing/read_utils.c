/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 18:34:28 by avassor           #+#    #+#             */
/*   Updated: 2023/08/16 11:30:08 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/cub3d.h"

_Bool	copy_line(t_data *data, char *line)
{
	data->raw[data->lines] = (char *)malloc(sizeof(char)
			* (ft_strlen(line) + 1));
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
	new = (char **)malloc(sizeof(char *) * (data->lines + 1));
	if (!new)
		return (data->err = MLLOC, 1);
	while (count < data->lines)
	{
		new[count] = (char *)malloc(sizeof(char)
				* (ft_strlen(data->raw[count]) + 1));
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

_Bool	is_origin(char id)
{
	if (id == 'N' || id == 'S' || id == 'E' || id == 'W')
		return (1);
	return (0);
}
