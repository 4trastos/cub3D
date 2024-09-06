/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:00:51 by davgalle          #+#    #+#             */
/*   Updated: 2024/09/06 16:48:47 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cube3d.h"

static void	save_player(char **map, t_brain *brain)
{
	int	y;
	int	x;

	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == 'N' || map[y][x] == 'E'
				|| map[y][x] == 'W' || map[y][x] == 'S')
			{
				brain->y = y;
				brain->x = x;
				break ;
			}
			x++;
		}
		y++;
	}
}

static void	fill(char **map, t_brain *brain, char to_fill, int *flag)
{
	t_brain	new_brain;
	int		y;
	int		x;

	y = brain->y;
	x = brain->x;
	if (y < 0 || x < 0 || y >= ft_countlines(map) || x >= (int)ft_strlen(map[y])
		|| map[brain->y][brain->x] != to_fill)
	{
		if (map[brain->y][brain->x] == ' ')
			*flag = 1;
		return ;
	}
	map[y][x] = 'F';
	new_brain = *brain;
	new_brain.x = x - 1;
	fill(map, &new_brain, to_fill, flag);
	new_brain.x = x + 1;
	fill(map, &new_brain, to_fill, flag);
	new_brain.y = y - 1;
	fill(map, &new_brain, to_fill, flag);
	new_brain.y = y + 1;
	fill(map, &new_brain, to_fill, flag);
}


int	ft_flood(char **map, t_brain *brain)
{
	int	flag;

	flag = 0;
	save_player(map, brain);
	map[brain->y][brain->x] = '0';
	fill(map, brain, map[brain->y][brain->x], &flag);
	return (flag);
}
