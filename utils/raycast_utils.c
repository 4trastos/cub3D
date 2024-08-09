/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 07:36:44 by davgalle          #+#    #+#             */
/*   Updated: 2024/07/11 13:52:59 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cube3d.h"

int	get_width(char **map)
{
	int		y;
	size_t	max;

	max = ft_strlen(map[0]);
	y = 1;
	while (y < ft_countlines(map))
	{
		if (ft_strlen(map[y]) > max)
			max = ft_strlen(map[y]);
		y++;
	}
	return ((int)max);
}

void	*ft_memset(void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*s;

	i = 0;
	s = str;
	while (i < n)
	{
		s[i] = (unsigned char)c;
		i++;
	}
	s = str;
	return (str);
}

void	get_player(t_p *p, char **map)
{
	int		y;
	int		x;

	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == 'N')
			{
				p->x = x;
				p->y = y;
				p->vec_x = 0;
				p->vec_y = -1.0f;

			}
			else if (map[y][x] == 'S')
			{
				p->x = x;
				p->y = y;
				p->vec_x = 0;
				p->vec_y = 1.0f;
			}
			else if (map[y][x] == 'E')
			{
				p->x = x;
				p->y = y;
				p->vec_x = 1.0f;
				p->vec_y = 0;
			}
			else if (map[y][x] == 'W')
			{
				p->x = x;
				p->y = y;
				p->vec_x = -1.0f;
				p->vec_y = 0;
			}
			x++;
		}
		y++;
	}
}
