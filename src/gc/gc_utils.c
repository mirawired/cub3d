/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:06:19 by jgarcia           #+#    #+#             */
/*   Updated: 2023/09/11 11:08:22 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/cub3d.h"
#include "./../../inc/gc.h"
#include <limits.h>

void	*ft_memset(void *s, int c, size_t n)
{
	char	*ptr;
	size_t	pos;

	ptr = (char *)s;
	pos = 0;
	while (pos < n)
	{
		ptr[pos] = c;
	pos ++;
	}
	return (s);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*r_ptr;

	if ((size == 0) || (nmemb == 0))
		return (malloc(0));
	if ((size >= INT_MAX / nmemb) || (nmemb >= INT_MAX / size))
		return (NULL);
	r_ptr = malloc(size * nmemb);
	if (r_ptr == NULL)
		return (NULL);
	ft_memset(r_ptr, 0, nmemb * size);
	return ((char *)r_ptr);
}
