/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 23:04:11 by mira              #+#    #+#             */
/*   Updated: 2023/08/16 16:01:00 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/cub3d.h"

size_t	line_chk2(char *a, char *b)
{
	char	*p1;
	char	*p2;

	p1 = a;
	p2 = b;
	while (*p1 && *p1 != '\n')
	{
		if (*p2 && *p1 == *p2)
		{
			p1++;
			p2++;
		}
		else
			return (0);
	}
	return (1);
}

char	*limited(t_stash **stash, char *line, int fd)
{
	if (stash)
		ft_unleash(stash[fd]);
	stash[fd] = NULL;
	free(line);
	return (NULL);
}

_Bool	ft_sprstrncmp(char *s1, char *s2)
{
	while (*s1)
	{
		if (!*s2)
			return (1);
		if (*s1 != *s2)
			return (1);
		s1++;
		s2++;
	}
	if (!*s1 && *s2 && *s2 != '\n')
		return (1);
	return (0);
}
