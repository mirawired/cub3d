/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rror.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 12:30:04 by avassor           #+#    #+#             */
/*   Updated: 2023/08/16 16:14:13 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/cub3d.h"

int	rror(int err, t_data *data)
{
	(void)data;
	(void)err;
	write(STDERR_FILENO, "Error\n", 7);
	return (EXIT_FAILURE);
}
