/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brain_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:57:01 by davgalle          #+#    #+#             */
/*   Updated: 2024/09/06 16:48:34 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cube3d.h"

void	police(char **map, char to_fill, int x, int y)
{
	if (y >= 0 && x >= 0 && y < ft_countlines(map)
		&& x < (int)ft_strlen(map[y]))
	{
		if (map[y][x] != to_fill)
			return ;
		map[y][x] = 'F';
		ft_printmap(map);
		printf("\n");
		police(map, to_fill, x - 1, y);
		police(map, to_fill, x + 1, y);
		police(map, to_fill, x, y - 1);
		police(map, to_fill, x, y + 1);
	}
}

int	border_cop(char **map, t_brain *brain)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (map[y][x] == ' ' && map[y][x] != '\0')
		x++;
	if (map[y][x] == '1')
		save_init(x, y, brain);
	police(map, map[y][x], x, y);
	return (0);
}

void	len_equal_next(t_brain *brain, char **map, int *y, int *x)
{
	int	len;
	int	prev;
	int	init_prev;

	init_prev = get_prev(map[*y - 1]);
	len = ft_strlencust(map[*y]) - 1;
	prev = ft_strlencust(map[*y - 1]) - 1;
	if (map[*y][*x - 1] == '1')
		brain->left = true;
	else if (map[*y][*x - 1] == ' ' && map[*y - 1][*x] == '1')
		brain->up = true;
	else if (map[*y][*x + 1] == '1' && *x < init_prev)
		brain->right = true;
	else if (map[*y][*x + 1] == '1')
		brain->right = true;
	else if (map[*y - 1][*x] == '1' && *x == init_prev)
		brain->up = true;
	else if (map[*y + 1][*x] == '1')
		brain->down = true;
	else if (len <= prev && map[*y - 1][*x] == '1')
		brain->up = true;
	else if (map[*y - 1][*x] == 'F' &&
			(*y - 1 == brain->init_y && *x == brain->init_x))
		brain->up = true;
}

void	len_more_next(t_brain *brain, char **map, int *y, int *x)
{
	int	init_prev;
	int	next;

	init_prev = get_prev(map[*y - 1]);
	next = ft_strlencust(map[*y + 1]) - 1;
	if (*x > next && map[*y][*x - 1] == '1')
		brain->left = true;
	else if (*x == next && map[*y + 1][*x] == '1')
		brain->down = true;
	else if (*x > init_prev && map[*y][*x - 1] == '1')
		brain->left = true;
	else if (map[*y - 1][*x] == 'F' &&
			(*y - 1 == brain->init_y && *x == brain->init_x))
		brain->up = true;
	else if (*x < init_prev && map[*y - 1][*x] == '1')
		brain->up = true;
	else if (*x < init_prev && map[*y][*x + 1] == '1')
		brain->right = true;
	else if (*x >= init_prev && map[*y - 1][*x] == '1')
		brain->up = true;
	else if (*x >= init_prev && map[*y][*x - 1] == '1')
		brain->left = true;
	else if (*x >= init_prev && map[*y + 1][*x] == '1')
		brain->down = true;
}

void	len_less_next(t_brain *brain, char **map, int *y, int *x)
{
	int	init_prev;
	int	next;

	init_prev = get_prev(map[*y - 1]);
	next = ft_strlencust(map[*y + 1]) - 1;
	if (*x == next && map[*y + 1][*x] == '1')
		brain->down = true;
	else if (map[*y - 1][*x] == 'F' &&
			(*y - 1 == brain->init_y && *x == brain->init_x))
		brain->up = true;
	else if (*x >= init_prev && map[*y - 1][*x] == '1')
		brain->up = true;
	else if (*x >= init_prev && map[*y][*x - 1] == '1')
		brain->left = true;
	else if (*x >= init_prev && map[*y + 1][*x] == '1')
		brain->down = true;
	else if (*x < init_prev && map[*y][*x + 1] == '1')
		brain->right = true;
}
