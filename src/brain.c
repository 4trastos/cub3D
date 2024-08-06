/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 08:30:35 by davgalle          #+#    #+#             */
/*   Updated: 2024/08/05 10:45:41 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cube3d.h"

void	reset_move(t_brain *brain)
{
	brain->up = false;
	brain->down = false;
	brain->left = false;
	brain->right = false;
}

void	save_init(int x, int y, t_brain *brain)
{
	brain->init_y = y;
	brain->init_x = x;
	brain->drowned = false;
}

void	wanted_road(t_brain *brain, char **map, int *y, int *x)
{
	int	alt;

	alt = ft_mtx_len(map) - 1;
	reset_move(brain);
	if (*y == 0)
		first_line(brain, map, y, x);
	else if (*y > 0 && *y < alt)
		intermediate_lines(brain, map, y, x);
	else if (*y == alt)
		last_line(brain, map, y, x);
}

void	walking_border(t_brain *brain, char **map, int *y, int *x)
{
	wanted_road(brain, map, y, x);
	if (brain->right)
	{
		map[*y][*x] = 'F';
		(*x)++;
	}
	else if (brain->down)
	{
		map[*y][*x] = 'F';
		(*y)++;
	}
	else if (brain->left)
	{
		map[*y][*x] = 'F';
		(*x)--;
	}
	else if (brain->up)
	{
		map[*y][*x] = 'F';
		(*y)--;
	}
	else
		brain->drowned = true;
}

int	walking_the_wall(char **map, t_brain *brain)
{
	int		y;
	int		x;

	y = 0;
	x = 0;
	while (map[y][x] == ' ' && map[y][x] != '\0')
		x++;
	if (map[y][x] == '1')
		save_init(x, y, brain);
	while (map[y] != NULL && brain->drowned == false)
		walking_border(brain, map, &y, &x);
	// ft_printmap(map);
	if (y == brain->init_y && x == brain->init_x)
		return (1);
	return (0);
}

