/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:33:16 by davgalle          #+#    #+#             */
/*   Updated: 2024/09/05 10:47:00 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cube3d.h"

void	skip_space(char *str, int *x)
{
	int		i;

	i = 0;
	while (str[i] == ' ' && str[i] != '\0')
		i++;
	*x += i;
}

int	player_validator(char **map)
{
	int	y;
	int	x;
	int	flag;

	y = 0;
	flag = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == 'N' || map[y][x] == 'E'
				|| map[y][x] == 'W' || map[y][x] == 'S')
			{
				if (flag == 1)
					return (0);
				flag = 1;
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	char_validator(char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == '1' || map[y][x] == '0' || map[y][x] == 'N'
				|| map[y][x] == 'E' || map[y][x] == 'W' || map[y][x] == 'S'
				|| map[y][x] == '\n' || map[y][x] == ' ' || map[y][x] == '\t')
				x++;
			else
				return (0);
		}
		y++;
	}
	return (1);
}
