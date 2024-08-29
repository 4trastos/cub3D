/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils_02.c                                 :+:      :+:    :+:   */
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
