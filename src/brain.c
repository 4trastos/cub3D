/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 08:30:35 by davgalle          #+#    #+#             */
/*   Updated: 2024/07/15 18:56:29 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cube3d.h"

void	wanted_road(t_brain *brain, char **map, int *y, int *x)
{
	int	len;
	int	alt;

	len = ft_strlencust(map[*y]) - 1;
	alt = ft_mtx_len(map) -1;
	if (*y == 0 && *x > 0 && *x < len)
	{
		if (*x < len && map[*y][*x + 1] == '1')
			brain->right = true;
		else if (*x == len && map[*y + 1][*x] == '1')
			brain->down = true;
	}
	if (*y == 0 && *x == len)
	{
		if (map[*y + 1][*x] == '1')
			brain->down = true;
	}
	else if (*y > 0 && *y < alt)
	{
		if (*y - 1 == brain->init_y && *x == brain->init_x)
			brain->up = true;
		else if (map[*y - 1][*x] == ' ' && *x < len)
		{
			if (map[*y][*x + 1] == '1')
				brain->right = true;
		}
		else if (map[*y - 1][*x] == '1')
			brain->up = true;
		else if (map[*y + 1][*x] == '1' && *y < alt)
			brain->down = true;
		else if (*x <= len && map[*y][*x - 1] == '1')
			brain->left = true;
	}
	else if (*y == alt && *x != 0)
	{
		if (*x == len && map[*y][*x - 1] == '1')
			brain->left = true;
		else if (*x < len && map[*y][*x - 1] == '1' && *x != 0)
			brain->left = true;
		else if (*x < len && map[*y][*x - 1] == ' ' && *x != 0)
		{
			if (map[*y - 1][*x] == '1')
				brain->up = true;
			else if (map[*y - 1][*x] == 'F' && (*y - 1 == brain->init_y
				&& *x == brain->init_x))
				brain->up = true;
		}
	}
	else if (*y == alt && *x == 0)
	{
		if (map[*y - 1][*x] == '1')
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
		printf("ACTUAL: --->>>>>>     %c\n", map[*y][*x]);
		printf("%s\n", map[*y]);
		map[*y][*x] = c;
		printf("CAMBIADO:  ---->>>>    %c\n", map[*y][*x]);
		(*x)++;
		printf("%s\n", map[*y]);
	}
	else if (brain->down)
	{
		printf("ACTUAL: --->>>>>>     %c\n", map[*y][*x]);
		printf("%s\n", map[*y]);
		map[*y][*x] = c;
		(*y)++;
		printf("CAMBIADO:  ---->>>>    %c\n", map[*y][*x]);
		printf("%s\n", map[*y]);
	}
	else if (brain->left)
	{
		printf("ACTUAL: --->>>>>>     %c\n", map[*y][*x]);
		printf("%s\n", map[*y]);
		map[*y][*x] = c;
		printf("CAMBIADO:  ---->>>>    %c\n", map[*y][*x]);
		(*x)--;
		printf("%s\n", map[*y]);
	}
	else if (brain->up)
	{
		printf("ACTUAL: --->>>>>>     %c\n", map[*y][*x]);
		printf("%s\n", map[*y]);
		map[*y][*x] = c;
		printf("CAMBIADO:  ---->>>>    %c\n", map[*y][*x]);
		(*y)--;
		printf("%s\n", map[*y]);
	}
	else
		brain->drowned = true;
	reset_move(brain);
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
