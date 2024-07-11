/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 08:30:35 by davgalle          #+#    #+#             */
/*   Updated: 2024/07/11 12:47:33 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cube3d.h"

void	walking_border(char **map, int y)
{
	(void)map;
	(void)y;
}

int	walking_the_wall(char **map)
{
	write(1, "### CAMINA POR EL MURO ###\n", 27);
	(void)map;
	// while (map[y] != NULL)
	// {
	// 	x = 0;
	// 	if (map[y] == '0')
	// 		walking_border(map, y);
	// 	while (map[y][x] != '\0')
	// 	{
	// 		while (map[y][x] == ' ' || map[y][x] == '\t')
	// 			x++;
	// 	}
	// 	y++;
	// }
	return (1);
}