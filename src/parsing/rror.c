/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rror.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 12:30:04 by avassor           #+#    #+#             */
/*   Updated: 2023/10/11 14:30:38 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/cub3d.h"

int	rror(int err, t_data *data)
{
	(void)data;
	write(STDERR_FILENO, "Error\n", 7);
	if (err == MLLOC)
		write(STDERR_FILENO, "Memory Allocation failed\n", 26);
	else if (err == NOARG)
		write(STDERR_FILENO, "Program needs one argument: 'file.cub'\n", 40);
	else if (err == ARGRR)
		write(STDERR_FILENO, "Invalid RGB value: 3x [0-255]\n", 31);
	else if (err == EMPT)
		write(STDERR_FILENO, "Empty configuration file\n", 26);
	else if (err == DIR)
		write(STDERR_FILENO, "Argument is a directory\n", 25);
	else if (err == EXT)
		write(STDERR_FILENO, "Argument is not in the form: 'file.cub'\n", 41);
	else if (err == RFD)
		write(STDERR_FILENO, "File opening failed\n", 21);
	else if (err == NOID)
		write(STDERR_FILENO, "Missing texture\n", 17);
	else if (err == MAPERROR)
	{
		write(STDERR_FILENO, "Invalid MAP, valid characters: {0,1,' '}", 41);
		write(STDERR_FILENO, " and one starting position {n,s,e,w}\n", 38);
		write(STDERR_FILENO, "MAP must be closed by walls {1}\n", 33);
	}
	return (gc_free(), EXIT_FAILURE);
}

int	find_id(char *raw)
{
	int	i;

	i = 0;
	while (raw[i] && raw[i] == ' ')
		i++;
	return (i);
}

int	find_end_map(t_data *data, char **raw, int i)
{
	int	j;

	j = 0;
	while ((i + j <= data->lines) && raw[i + j])
	{
		if (!raw[i + j] || raw[i + j][0] != '1')
			break ;
		j++;
	}
	return (j);
}
