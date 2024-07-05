/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 07:36:13 by davgalle          #+#    #+#             */
/*   Updated: 2024/07/05 10:21:55 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cube3d.h"

void	error_msg(char *str, char **map)
{
	if (map)
		free_map(map);
	while (*str)
		write(1, str++, 1);
	write(1, "\n", 1);
	exit (1);
}

void	free_map(char **map)
{
	char	**temp;

	temp = map;
	while (*map)
	{
		free(*map);
		map++;
	}
	free(temp);
}
