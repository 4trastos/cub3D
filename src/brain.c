/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 08:30:35 by davgalle          #+#    #+#             */
/*   Updated: 2024/07/12 13:52:41 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cube3d.h"

unsigned int	pack_coordinates(int y, int x)
{
	unsigned int	value;

	value = ((y & 0xFFFF) << 16) | (x & 0xFFFF);
	return (value);
}

void	unpack_coord(unsigned int packed, int *y, int *x)
{
	*y = (packed >> 16) & 0xFFFF;
	*x = packed & 0xFFFF;
}

unsigned int	save_init(int y, int x, t_brain *brain)
{
	unsigned int	result;

	result = pack_coordinates(y, x);
	brain->init_x = x;
	brain->init_y = y;
	brain->init_coord = result;
	return (result);
}

void	walking_border(unsigned int *current, char **map, int *y, int *x)
{
	// unpack_coord(*current, x, y);
	if (*x <= 30 && map[*y][*x + 1] == '1')
	{
		map[*y][*x] = 'F';
		if (*x != 30)
			(*x)++;
	}
	else if (*y < ft_mtx_len(map) && map[*y + 1][*x] == '1')
	{
		map[*y][*x] = 'F';
		(*y)++;
	}
	else if (*x > 0 && map[*y][*x - 1] == '1')
	{
		map[*y][*x] = 'F';
		(*x)--;
	}
	else if (*y > 0 && map[*y - 1][*x] == '1')
	{
		map[*y][*x] = 'F';
		(*y)--;
	}
	*current = pack_coordinates(*y, *x);
}

int	walking_the_wall(char **map, t_brain *brain)
{
	int				y;
	int				x;
	unsigned int	init;
	unsigned int	current;

	y = 0;
	x = 0;
	skip_space(map[y], &x);
	if (map[y][x] == '1')
	{
		init = save_init(x, y, brain);
		current = init;
		walking_border(&current, map, &y, &x);
	}
	while (map[y] != NULL && current != init)
	{
		printf("LINEA ANTES DE WALKING: %s\n", map[y]);
		printf("LA Y: %i LA X: %i\n", y, x);
		walking_border(&current, map, &y, &x);
		printf("LINEA DESPUES DE WALKING: %s\n", map[y]);
		printf("LA Y: %i LA X: %i\n", y, x);
		// unpack_coord(current, &y, &x);
	}
	if (current == init)
		return (1);
	return (0);
}
