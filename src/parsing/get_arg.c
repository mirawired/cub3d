/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 13:00:30 by avassor           #+#    #+#             */
/*   Updated: 2023/10/11 14:48:06 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/cub3d.h"

/* **************************************************************************
 * is_dir:
 * - check if the argument is a directory
 ************************************************************************** */

_Bool	is_dir(char *arg)
{
	int	fd;

	fd = open(arg, __O_DIRECTORY);
	if (fd > 0)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

/* **************************************************************************
 * is_cub:
 * - check if the argument is a .cub file
 ************************************************************************** */

_Bool	is_cub(char *arg)
{
	while (*arg)
		arg++;
	if (*(arg - 1) == 'b' && *(arg - 2) == 'u'
		&& *(arg - 3) == 'c' && *(arg - 4) == '.')
		return (0);
	return (1);
}

/* **************************************************************************
 * chk_arg:
 * - check the argument
 ************************************************************************** */

_Bool	chk_arg(t_data *data, char *arg)
{
	if (is_dir(arg))
		return (data->err = DIR, 1);
	if (is_cub(arg))
		return (data->err = EXT, 1);
	data->fd = open(arg, O_RDONLY);
	if (data->fd < 0)
		return (close(data->fd), data->err = RFD, 1);
	return (0);
}

/* **************************************************************************
 * get_arg:
 * - read the .cub file
 ************************************************************************** */

_Bool	get_arg(t_data *data)
{
	char	*line;

	line = NULL;
	line = get_next_line(data->fd);
	while (line)
	{
		data->lines++;
		if (upscale_raw(data) || copy_line(data, line))
			return (clean_raw(data), 1);
		free(line);
		line = get_next_line(data->fd);
	}
	close(data->fd);
	if (data->lines < 0)
		return (data->err = EMPT, 1);
	return (0);
}

/* **************************************************************************
 * chk_edges:
 * - check if the map is effectively closed by walls
 ************************************************************************** */

_Bool	chk_edges(t_data *data, char c, char d)
{
	if (c != '1' || d != '1')
		return (data->err = MAPERROR, 1);
	return (0);
}
