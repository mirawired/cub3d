/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 18:40:28 by avassor           #+#    #+#             */
/*   Updated: 2023/08/16 11:28:45 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/cub3d.h"

void	clean_raw(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->lines)
	{
		free(data->raw[i]);
		i++;
	}
	if (i)
	{
		free(data->raw);
		data->raw = NULL;
	}
}
