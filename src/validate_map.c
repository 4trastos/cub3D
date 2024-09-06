/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:47:59 by davgalle          #+#    #+#             */
/*   Updated: 2024/09/06 16:46:37 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cube3d.h"

char	**to_bricks(char **paper)
{
	int	y;
	int	x;

	y = 0;
	while (paper[y] != NULL)
	{
		x = 0;
		while (paper[y][x] != '\0')
		{
			if (paper[y][x] == ' ')
				paper[y][x] = '1';
			x++;
		}
		y++;
	}
	return (paper);
}

static int	is_closed(char **map, int y, int x)
{
	size_t	len_prev;

	if (y != 0)
		len_prev = ft_strlen(map[y - 1]);
	if (map[y][x] == '0' || (map[y][x] != '1' && map[y][x] != ' '))
	{
		if (y == 0 || x == 0 || !map[y + 1] || !map[y][x + 1])
			return (1);
		if (len_prev < ft_strlen(map[y]) && map[y][x] == '0'
			&& (size_t)x > (len_prev - 1))
			return (1);
		if (y > 0 && map[y - 1][x] == ' ')
			return (1);
		if (map[y + 1] && map[y + 1][x] == ' ')
			return (1);
		if (x > 0 && map[y][x - 1] == ' ')
			return (1);
		if (map[y][x + 1] && map[y][x + 1] == ' ')
			return (1);
	}
	return (0);
}

int	validate_map(char **map, t_brain *brain)
{
	int	y;
	int	x;

	(void)brain;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (is_closed(map, y, x) == 1)
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}
