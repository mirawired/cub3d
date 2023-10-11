/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rror.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 12:30:04 by avassor           #+#    #+#             */
/*   Updated: 2023/10/11 16:10:49 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/cub3d.h"

int	rror(int err)
{
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
		write(STDERR_FILENO, "MAP err bad char or position or enclosure\n", 43);
	else if (err == EXT2)
		write(STDERR_FILENO, "Illegal filetype\n", 18);
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
		if (!raw[i + j] || (raw[i + j][0] != '1' && raw[i + j][0] != ' '))
			break ;
		j++;
	}
	return (j);
}

_Bool	ko_ext(char *fill)
{
	int	i;

	i = 0;
	while (fill[i])
		i++;
	if (fill[i - 1] != 'm' || fill[i - 2] != 'p'
		|| fill[i - 3] != 'x' || fill[i - 4] != '.')
		return (1);
	return (0);
}
