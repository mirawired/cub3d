/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 18:35:42 by avassor           #+#    #+#             */
/*   Updated: 2023/08/16 16:00:56 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/cub3d.h"

void	ft_strcpy(char *prev, char *new)
{
	int		i;

	i = 0;
	while (prev[i])
	{
			new[i] = prev[i];
			i++;
	}
	new[i] = '\0';
}

void	ft_strncpy(char *prev, char *new, int nbr)
{
	int		i;

	i = 0;
	while (nbr && prev[i])
	{
			new[i] = prev[i];
			nbr--;
			i++;
	}
	new[i] = '\0';
}

int	ft_strlen(const char *s)
{
	const char	*str;

	if (!s)
		return (0);
	str = s;
	while (*str)
		str++;
	return (str - s);
}

_Bool	ft_strncmp(char *needle, char *haystack, int size)
{
	int	i;

	i = 0;
	while (haystack[i] && i < size)
	{
		if (haystack[i] != needle[i])
			return (1);
		i++;
	}
	if (i != size)
		return (1);
	return (0);
}

int	ft_atoi(const char *p)
{
	int		s;
	int		n;

	s = 1;
	n = 0;
	while (*p == ' ' || *p == '\f' || *p == '\n' || *p == '\r' || *p == '\t'
		|| *p == '\v' )
		p++;
	if (*p == '-' || *p == '+')
	{
		if (*p == '-')
			s *= -1;
		++p;
	}
	if (*p < '0' && *p > 9)
		return (0);
	while (*p >= '0' && *p <= '9')
	{
		n *= 10;
		n += *p - 48;
		p++;
	}
	return (n * s);
}
