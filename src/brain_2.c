/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brain_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usuario <usuario@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 08:30:35 by davgalle          #+#    #+#             */
/*   Updated: 2024/07/14 13:19:49 by usuario          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cube3d.h"

void	updgrade_current(unsigned int *current, char **map, int *y, int *x)
{
	if (map[*y][*x + 1] != '\0' && map[*y][*x + 1] != 'F' && map[*y][*x + 1] != '0')
	{
		if (map[*y][*x + 1] == '1')
		{
			map[*y][*x] = 'F';
			(*x)++;
		}
	}
	else if (map[*y + 1] != NULL && map[*y + 1][*x] != 'F')
	{
		if (map[*y + 1][*x] == '1')
		{
			map[*y][*x] = 'F';
			(*y)++;
		}
	}
	else if (*x > 0)
	{
		if (map[*y][*x - 1] == '1')
		{
			map[*y][*x] = 'F';
			(*x)--;
		}	
	}
	else if (*y > 0)
	{
		if (map[*y - 1][*x] == '1')
		{
			map[*y][*x] = 'F';
			(*y)--;
		}
	}
	else
	{
        printf("No se puede mover desde la posición (%d, %d)\n", *y, *x);
        return ;
	}
	*current = pack_coordinates(*y, *x);
}
