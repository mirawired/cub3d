/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:06:19 by jgarcia           #+#    #+#             */
/*   Updated: 2023/10/11 11:00:28 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/cub3d.h"
#include "./../../inc/gc.h"
#include <limits.h>

/* **************************************************************************
 * ft_memset:
 * - Fills the first n bytes of the memory area pointed to by s with the
 * constant byte c.
 ************************************************************************** */

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

/* **************************************************************************
 * ft_calloc:
 * - Allocates memory for an array of nmemb elements of size bytes each and
 * returns a pointer to the allocated memory. The memory is set to zero.
 * - If the multiplication of nmemb and size would result in integer
 * overflow, then calloc() returns an error.
 * - If nmemb or size is equal to zero, then calloc() returns NULL,
 ************************************************************************** */

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

/* **************************************************************************
 * gc_error_exit:
 * - In case of memory error, print an error message free all allocated memory
 * and exit the program.
 ************************************************************************** */

void	gc_error_exit(void)
{
	write(2, "PANIC! Memory error, Exiting ...\n", 34);
	gc_free();
	exit(1);
}
