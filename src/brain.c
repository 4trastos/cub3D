/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usuario <usuario@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 08:30:35 by davgalle          #+#    #+#             */
/*   Updated: 2024/07/14 13:45:04 by usuario          ###   ########.fr       */
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

void	walking_border(t_brain *brain, char **map, int *y, int *x)
{
	// unpack_coord(*current, x, y);
	if (map[*y][*x + 1] != '\0' && map[*y][*x + 1] != 'F' && map[*y][*x + 1] != '0')
	{
		if (map[*y][*x + 1] == '1')
		{
			map[*y][*x] = 'F';
			(*x)++;
		}
	}
	else if (map[*y + 1] != NULL && map[*y + 1][*x] != 'F' && map[*y + 1][*x] != '0')
	{
		if (map[*y + 1][*x] == '1')
		{
			map[*y][*x] = 'F';
			(*y)++;
		}
	}
	else if (*x > 0 && map[*y][*x - 1] != 'F' && map[*y][*x - 1] != '0')
	{
		if (map[*y][*x - 1] == '1')
		{
			map[*y][*x] = 'F';
			(*x)--;
		}	
	}
	else if (*y > 0 && map[*y - 1][*x] != '0')
	{
		if (map[*y - 1][*x] == '1')
		{
			map[*y][*x] = 'F';
			(*y)--;
		}
		else if (*y - 1 == brain->init_y && *x == brain->init_x)
		{
			map[*y][*x] = 'F';
			(*y)--;
		}
	}
	else
	{
        printf("No se puede mover desde la posición (%d, %d)\n", *y, *x);
		brain->drowned = true;
        return ;
	}
	// *current = pack_coordinates(*y, *x);
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
		updgrade_current(&current, map, &y, &x);
	}
	while (map[y] != NULL && current != init && brain->drowned == false)
	{
		walking_border(brain, map, &y, &x);
		// unpack_coord(current, &y, &x);
		current = pack_coordinates(y, x);
	}
	if (current == init)
		return (1);
	return (0);
}


/* void	walking_border(unsigned int *current, char **map, int *y, int *x)
{
	// unpack_coord(*current, x, y);
	if ((*x < ft_strlencust(map[*y]) - 1) && map[*y][*x + 1] == '1')
	{
		map[*y][*x] = 'F';
		(*x)++;
	}
	else if ((*y < ft_countlines(map) -1) && map[*y + 1][*x] == '1' && map[*y + 1] != NULL)
	{
		map[*y][*x] = 'F';
		(*y)++;
	}
	else if (*x > 0 && (map[*y][*x + 1] == '\0' || map[*y][*x + 1] == '\n') && map[*y][*x - 1] == '1')
	{
		map[*y][*x] = 'F';
		(*x)--;
	}
	else if ((*x < ft_strlencust(map[*y]) - 1) && map[*y][*x - 1] == '1')
	{
		map[*y][*x] = 'F';
		(*x)--;
	}
	else if (*y > 0 && map[*y - 1][*x] == '1')
	{
		map[*y][*x] = 'F';
		(*y)--;
	}
	else
	{
        printf("No se puede mover desde la posición (%d, %d)\n", *y, *x);
        return ;
	}
	*current = pack_coordinates(*y, *x);
} */