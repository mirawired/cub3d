/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 23:03:55 by mira              #+#    #+#             */
/*   Updated: 2023/08/16 16:01:00 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/cub3d.h"

/* **************************************************************************
 * ft_recover:
 * - recover the last line of the buffer
 ************************************************************************** */

void	ft_recover(t_stash **stash)
{
	char	*p1;
	char	*p2;
	t_stash	*new;
	t_stash	*end;

	new = malloc(sizeof(t_stash));
	if (!new || !stash)
		return ;
	new->next = NULL;
	end = ft_lst_get_last(*stash);
	p1 = end->str;
	while (*p1 && *p1 != '\n')
		p1++;
	if (*p1 == '\n')
		p1++;
	p2 = p1;
	while (*p2)
		p2++;
	ft_left(stash, new, p1, p2);
}

/* **************************************************************************
 * ft_addbuff:
 * - add a buffer to the stash
 ************************************************************************** */

void	ft_addbuff(char *buf, t_stash **stash, int i)
{
	t_stash	*new;
	t_stash	*current;
	char	*p1;
	int		j;

	new = malloc(sizeof(t_stash));
	if (!new)
		return ;
	new->next = NULL;
	new->str = malloc(sizeof(char) * (i + 1));
	if (!new->str)
		return ;
	p1 = new->str;
	j = 0;
	while (*buf && (j++ < i))
		*p1++ = *buf++;
	*p1 = '\0';
	if (!*stash)
	{
		*stash = new;
		return ;
	}
	current = ft_lst_get_last(*stash);
	current->next = new;
}

/* **************************************************************************
 * ft_reader:
 * - read the file and add the buffer to the stash
 ************************************************************************** */

void	ft_reader(int fd, t_stash **stash)
{
	char	*buf;
	int		i;

	i = 1;
	while (!ft_scanner(*stash) && i != 0)
	{
		buf = malloc(sizeof(char) * (GNL_BUFFER_SIZE + 1));
		if (!buf)
			return ;
		i = (int)read(fd, buf, GNL_BUFFER_SIZE);
		if ((!(*stash) && i == 0) || i < 0)
		{
			free(buf);
			return ;
		}
		buf[i] = '\0';
		ft_addbuff(buf, stash, i);
		free(buf);
	}
}

/* **************************************************************************
 * ft_addline:
 * - add the stash to the line
 ************************************************************************** */

void	ft_addline(t_stash *stash, char **line)
{
	char	*p1;
	char	*p2;

	if (!stash)
		return ;
	*line = malloc(sizeof(char) * (ft_linkbrows(stash) + 1));
	if (!*line)
		return ;
	p1 = *line;
	while (stash)
	{
		p2 = stash->str;
		while (*p2)
		{
			if (*p2 == '\n')
			{
				*p1++ = '\n';
				break ;
			}
			*p1++ = *p2++;
		}
		stash = stash->next;
	}
	*p1 = '\0';
}

/* **************************************************************************
 * get_next_line:
 * - read the file and return the line
 * - return NULL if there is an error
 ************************************************************************** */

char	*get_next_line(int fd)
{
	static t_stash	*stash[1024];
	char			*line;

	if (fd < 0 || fd > 1024 || GNL_BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	line = NULL;
	ft_reader(fd, &stash[fd]);
	if (!stash[fd])
		return (NULL);
	ft_addline(stash[fd], &line);
	ft_recover(&stash[fd]);
	if (!*line)
	{
		ft_unleash(stash[fd]);
		stash[fd] = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}
