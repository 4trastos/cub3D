/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 08:30:35 by davgalle          #+#    #+#             */
/*   Updated: 2024/07/17 14:59:30 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cube3d.h"

void	wanted_road(t_brain *brain, char **map, int *y, int *x)
{
	int	len;
	int	alt;
	int	aux;

	len = ft_strlencust(map[*y]) - 1;
	alt = ft_mtx_len(map) - 1;
	aux = 0;
	reset_move(brain);
	if (*y == 0)
	{
		printf("XXXXXXXXXXXXXXX   PRIMERA LINEA   XXXXXXXXXXXXXXXXXXXXX\n\n");
		if (*x == len && map[*y + 1][*x] == '1')
			brain->down = true;
		else if (map[*y][*x + 1] == '1' && map[*y + 1][*x + 1] != ' ')
			brain->right = true;
		else if (map[*y + 1][*x] == '1')
			brain->down = true;
	}
	else if (*y > 0 && *y < alt)
	{
		printf("XXXXXXXXXXXXXXX  LINEAS INTERMEDIAS   XXXXXXXXXXXXXXXXXXXXX\n\n");
		aux = ft_strlencust(map[*y + 1]) - 1;
		if (*x == len && (len == aux) && map[*y + 1][*x] == '1')
			brain->down = true;
		if (*x == len && (len == aux) && map[*y + 1][*x] == '1')
			brain->down = true;
		else if (*x > len && (len < aux) && map[*y][*x - 1] == '1')
			brain->left = true;
		else if (map[*y - 1][*x] == 'F' &&
			(*y - 1 == brain->init_y && *x == brain->init_x))
			brain->up = true;
		else if (map[*y][*x + 1] == '1' && map[*y + 1][*x + 1] == ' ')
			brain->down = true;
		else if (map[*y][*x + 1] == '1' && map[*y - 1][*x + 1] == ' ')
			brain->right = true;
		else if (map[*y][*x + 1] == '1' && map[*y - 1][*x + 1] == 'F')
		{
			if (*y - 1 == brain->init_y && *x + 1 == brain->init_x)
				brain->right = true;
		}
		else if (map[*y + 1][*x] == '1')
			brain->down = true;
		else if (map[*y - 1][*x] == '1')
			brain->up = true;
		else if (*x > 0 && map[*y][*x - 1] == '1')
			brain->left = true;
	}
	else if (*y == alt)
	{
		printf("XXXXXXXXXXXXXXX   ULTIMA LINEA   XXXXXXXXXXXXXXXXXXXXX\n\n");
		if (*x == len && map[*y][*x - 1] == '1')
			brain->left = true;
		else if (*x > 0 && map[*y][*x - 1] == '1')
			brain->left = true;
		else if (*x < len && map[*y - 1][*x] == '1')
			brain->up = true;
	}
}

void	skip_space(char *str, int *x)
{
	int		i;

	i = 0;
	while (str[i] == ' ' && str[i] != '\0')
		i++;
	*x += i;
}

void	save_init(int x, int y, t_brain *brain)
{
	brain->init_y = y;
	brain->init_x = x;
	brain->drowned = false;
}

void	walking_border(t_brain *brain, char **map, int *y, int *x)
{
	char	c;

	wanted_road(brain, map, y, x);
	c = 'F';
	if (brain->right)
	{
		printf("POSICIÓN X:   %d ---->>>>  %c  --->>>  %s\n", *x, map[*y][*x], map[*y]);
		map[*y][*x] = c;
		printf("CAMBIA LETRA:   ---------------->>>  %s\n", map[*y]);
		(*x)++;
		printf("\n");
	}
	else if (brain->down)
	{
		printf("POSICIÓN X:   %d ---->>>>  %c  --->>>  %s\n", *x, map[*y][*x], map[*y]);
		map[*y][*x] = c;
		printf("CAMBIA LETRA:   ---------------->>>  %s\n", map[*y]);
		(*y)++;
		printf("\n");
		printf("        + + + + + + + BAJA LINEA + + + + + + +\n\n");

	}
	else if (brain->left)
	{
		printf("POSICIÓN X:   %d ---->>>>  %c  --->>>  %s\n", *x, map[*y][*x], map[*y]);
		map[*y][*x] = c;
		printf("CAMBIA LETRA:   ---------------->>>  %s\n", map[*y]);
		(*x)--;
		printf("\n");
	}
	else if (brain->up)
	{
		printf("POSICIÓN X:   %d ---->>>>  %c  --->>>  %s\n", *x, map[*y][*x], map[*y]);
		map[*y][*x] = c;
		printf("CAMBIA LETRA:   ---------------->>>  %s\n", map[*y]);
		(*y)--;
		printf("\n");
		printf("        + + + + + + + SUBE LINEA + + + + + + +\n\n");
	}
	else
	{
		brain->drowned = true;
		printf("################ NO SE PUEDE MOVER ##############\n");
	}
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
	if (y == brain->init_y && x == brain->init_x)
		return (1);
	return (0);
}

/* void	wanted_road(t_brain *brain, char **map, int *y, int *x)
{
	int	len;
	int	alt;

	len = ft_strlencust(map[*y]) - 1;
	alt = ft_mtx_len(map) -1;
	reset_move(brain);
	if (*y == 0)
	{
		if (*x == 0)
		{
			if (x == len && map[*y++][*x] == '1')
				brain->down = true;
			else if (map[*y][*x++] == '1' && map[*y++][*x++] == ' '
				&& map[*y++][*x] == '1')
				brain->down = true;
			else if (map[*y][*x++] == '1' && map[*y++][*x++] != ' ')
				brain->right = true;
		}
		else if (*x > 0 && *x < len)
		{
			if (map[*y][*x++] == '1' && map[*y++][*x++] != ' ')
				brain->right = true;
			else if (map[*y][*x++] == '1' && map[*y++][*x++] == ' '
				&& map[*y++][*x] == '1')
				brain->down = true;
		}
		else if (*x == len && map[*y++][*x] == '1')
			brain->down = true;
	}
	else if (*y > 0 && *y < alt)
	{
		if (map[*y--][*x] == ' ' && map[*y][*x++] == '1')
			brain->right = true;
		else if (map[*y--][*x] == '1' && map[*y--][])
			brain->up = true;
	}
	else if (*y == alt)
	{
		
	}
} */