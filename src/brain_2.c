/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brain_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 08:30:35 by davgalle          #+#    #+#             */
/*   Updated: 2024/08/07 09:14:33 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cube3d.h"

void	first_line(t_brain *brain, char **map, int *y, int *x)
{
	int	next;
	int	len;

	printf("LINEA:  %d    COLUMNA:   %d\n", *y, *x);
	len = ft_strlencust(map[*y]) - 1;
	next = ft_strlencust(map[*y + 1]) - 1;
	if (*x == len && map[*y + 1][*x] == '1')
		brain->down = true;
	else if (*x <= next)
	{
		if (*x < next && map[*y][*x + 1] == '1')
			brain->right = true;
		else if ((*x == next) && map[*y + 1][*x] == '1')
			brain->down = true;
	}
}

void	last_line(t_brain *brain, char **map, int *y, int *x)
{
	int	len;

	printf("LINEA:  %d    COLUMNA:   %d\n", *y, *x);
	len = ft_strlencust(map[*y]) - 1;
	if (*x == len && map[*y][*x - 1] == '1')
		brain->left = true;
	else if (*x > 0 && map[*y][*x - 1] == '1')
		brain->left = true;
	else if (*x < len && map[*y - 1][*x] == '1')
		brain->up = true;
}

void	last_position(t_brain *brain, char **map, int *y, int *x)
{
	int	next;
	int	len;

	printf("LINEA:  %d    COLUMNA:   %d\n", *y, *x);
	len = ft_strlencust(map[*y]) - 1;
	next = ft_strlencust(map[*y + 1]) - 1;
	if (len > next && map[*y][*x - 1] == '1')
		brain->left = true;
	else if (len == next && map[*y + 1][*x] == '1')
		brain->down = true;
	else if (len < next && map[*y + 1][*x] == '1')
		brain->down = true;
}

void	first_position(t_brain *brain, char **map, int *y, int *x)
{
	if (map[*y - 1][*x] == '1')
		brain->up = true;
	else if (map[*y - 1][*x] == 'F' &&
		(*y - 1 == brain->init_y && *x == brain->init_x))
		brain->up = true;
	else if (map[*y - 1][*x] == ' ' && map[*y][*x + 1] == '1')
		brain->right = true;
}

void	intermediate_lines(t_brain *brain, char **map, int *y, int *x)
{
	int	next;
	int	len;
	int	prev;
	int	init_prev;

	printf("LINEA:  %d    COLUMNA:   %d\n", *y, *x);
	init_prev = get_prev(map[*y - 1]);
	printf("Inicio de la previa: --->>> %d   ", init_prev);
	len = ft_strlencust(map[*y]) - 1;
	next = ft_strlencust(map[*y + 1]) - 1;
	prev = ft_strlencust(map[*y - 1]) - 1;
	if (*x == 0)
		first_position(brain, map, y, x);
	else if (*x > 0 && *x < len)
	{
		if (len == next)
		{
			if (map[*y][*x + 1] == '1' && *x < init_prev)
				brain->right = true;
			else if (map[*y + 1][*x] == '1')
				brain->down = true;
			else if (len <= prev && map[*y - 1][*x] == '1')
				brain->up = true;
			else if (map[*y][*x + 1] == '1')
				brain->right = true;
			else if (map[*y][*x - 1] == '1')
				brain->left = true;
			else if (map[*y - 1][*x] == '1' && *x == init_prev)
				brain->up = true;
			else if (map[*y - 1][*x] == 'F' &&
				(*y - 1 == brain->init_y && *x == brain->init_x))
				brain->up = true;
		}
		else if (len > next)
		{
			if (*x > next && map[*y][*x - 1] == '1')
				brain->left = true;
			else if (*x == next && map[*y + 1][*x] == '1')
				brain->down = true;
			else if (*x < init_prev && map[*y - 1][*x] == '1')
				brain->up = true;
			else if (*x < init_prev && map[*y][*x + 1] == '1')
				brain->right = true;
			else if (*x > init_prev && map[*y - 1][*x] == '1')
				brain->up = true;
			else if (*x > init_prev && map[*y][*x - 1] == '1')
				brain->left = true;
			else if (*x > init_prev && map[*y + 1][*x] == '1')
				brain->down = true;
			else if (*x == init_prev && map[*y - 1][*x] == '1')
				brain->up = true;
		}
		else if (len < next)
		{
			if (*x == next && map[*y + 1][*x] == '1')
				brain->down = true;
			else if (*x >= init_prev && map[*y - 1][*x] == '1')
				brain->up = true;
			else if (*x >= init_prev && map[*y][*x - 1] == '1')
				brain->left = true;
			else if (*x >= init_prev && map[*y + 1][*x] == '1')
				brain->down = true;
			else if (*x < init_prev && map[*y][*x + 1] == '1')
				brain->right = true;
		}
	}
	else if (*x == len)
		last_position(brain, map, y, x);
}
