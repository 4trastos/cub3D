/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brain_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 08:30:35 by davgalle          #+#    #+#             */
/*   Updated: 2024/07/18 12:50:51 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cube3d.h"

void	first_line(t_brain *brain, char **map, int *y, int *x)
{
	int	aux;
	int	len;

	len = ft_strlencust(map[*y]) - 1;
	aux = ft_strlencust(map[*y + 1]) - 1;
	if (*x == len && map[*y + 1][*x] == '1')
		brain->down = true;
	else if (*x <= aux)
	{
		if (*x < aux && map[*y][*x + 1] == '1')
			brain->right = true;
		else if ((*x == aux) && map[*y + 1][*x] == '1')
			brain->down = true;
	}
}

void	last_line(t_brain *brain, char **map, int *y, int *x)
{
	int	len;

	len = ft_strlencust(map[*y]) - 1;
	if (*x == len && map[*y][*x - 1] == '1')
		brain->left = true;
	else if (*x > 0 && map[*y][*x - 1] == '1')
		brain->left = true;
	else if (*x < len && map[*y - 1][*x] == '1')
		brain->up = true;
}

void	intermediate_lines(t_brain *brain, char **map, int *y, int *x)
{
	int	aux;
	int	len;

	len = ft_strlencust(map[*y]) - 1;
	aux = ft_strlencust(map[*y + 1]) - 1;
	printf("************** LINEAS INTERMEDIAS ********\n");
	printf("LINEA:  %d    FILA:   %d\n", *y, *x);
	if (*x == len)
	{
		if (len > aux && map[*y][*x - 1] == '1')
			brain->left = true;
		else if (map[*y + 1][*x] == '1')
			brain->down = true;
	}
	else if (map[*y - 1][*x] == 'F' &&
		(*y - 1 == brain->init_y && *x == brain->init_x))
		brain->up = true;
	else if (map[*y][*x + 1] == '1' && map[*y - 1][*x + 1] == ' ')
		brain->right = true;
	else if (map[*y - 1][*x] == ' ' && map[*y][*x + 1] == '1' &&
		map[*y - 1][*x + 1] == '1')
		brain->right = true;
	else if (map[*y][*x + 1] == '1' && map[*y - 1][*x + 1] == 'F')
	{
		if (*y - 1 == brain->init_y && *x + 1 == brain->init_x)
			brain->right = true;
	}
	else if (len >= aux)
	{
		if (*x < aux && *x > 0)
		{
			if (map[*y + 1][*x] == '1')
				brain->down = true;
			else if (map[*y][*x - 1] == ' ' && map[*y - 1][*x] == '1')
				brain->up = true;
			else if (map[*y][*x - 1] == '1')
				brain->left = true;
			else if (map[*y - 1][*x] == '1' && map[*y - 1][*x - 1] == ' ')
				brain->up = true;
		}
		else if (*x == aux && *x > 0)
		{
			if (map[*y + 1][*x] == '1')
				brain->down = true;
			else if (map[*y - 1][*x] == '1')
				brain->up = true;
			else if (map[*y][*x - 1] == '1')
				brain->left = true;
		}
		else if (*x > aux)
		{
			if (map[*y][*x - 1] == '1')
				brain->left = true;
		}
		else if (*x == 0 && map[*y - 1][*x] == '1')
			brain->up = true;
		else if (map[*y][*x + 1] == '1')
			brain->right = true;
	}
	else if (len < aux && *x == 0 && map[*y - 1][*x] == '1')
		brain->up = true;
}
