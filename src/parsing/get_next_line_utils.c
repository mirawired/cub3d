/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 23:04:04 by mira              #+#    #+#             */
/*   Updated: 2023/08/16 16:01:38 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/cub3d.h"

void	ft_left(t_stash **stash, t_stash *new, char *p1, char *p2)
{
	new->str = malloc(sizeof(char) * ((p2 - p1) + 1));
	if (!new->str)
		return ;
	p2 = new->str;
	while (*p1)
		*p2++ = *p1++;
	*p2 = '\0';
	ft_unleash(*stash);
	*stash = new;
}

int	ft_scanner(t_stash *stash)
{
	t_stash	*id;
	char	*p;

	if (!stash)
		return (0);
	id = ft_lst_get_last(stash);
	p = id->str;
	while (*p)
	{
		if (*p == '\n')
			return (1);
		p++;
	}
	return (0);
}

t_stash	*ft_lst_get_last(t_stash *stash)
{
	t_stash	*get;

	get = stash;
	while (get && get->next)
		get = get->next;
	return (get);
}

void	ft_unleash(t_stash *stash)
{
	t_stash	*hold;
	t_stash	*next;

	hold = stash;
	while (hold)
	{
		free(hold->str);
		next = hold->next;
		free(hold);
		hold = next;
	}
}

int	ft_linkbrows(t_stash *stash)
{
	char	*p1;
	int		i;

	i = 1;
	while (stash)
	{
		p1 = stash->str;
		while (*p1)
		{
			if (*p1 == '\n')
				return (i);
			i++;
			p1++;
		}
		stash = stash->next;
	}
	return (i);
}
