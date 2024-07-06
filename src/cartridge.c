/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartridge.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usuario <usuario@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:33:16 by davgalle          #+#    #+#             */
/*   Updated: 2024/07/06 21:39:35 by usuario          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cube3d.h"

int	coordinates(char *str, t_design *cartridge, size_t x)
{
	if (str[x] != 'N' || str[x] != 'S' || str[x] != 'W' || str[x] != 'E')
		return (0);
	if (str[x] == 'N' && str[x + 1] == 'O')
	{
		if (cartridge->no != NULL)
			cartridge->no = ft_strdup(str);
		}
	else if (str[x] == 'S' && str[x + 1] == 'O')
	{
		if (cartridge->so != NULL)
			cartridge->so = ft_strdup(str);
	}
	else if (str[x] == 'W' && str[x + 1] == 'E')
	{
		if (cartridge->we != NULL)
			cartridge->we = ft_strdup(str);
	}
	else if (str[x] == 'E' && str[x + 1] == 'A')
	{
		if (cartridge->ea != NULL)
			cartridge->ea = ft_strdup(str);
	}
	return (1);
}

void	create_cartridge(char **data, t_design *cartridge, 	size_t	x, size_t y)
{
	y = 0;
	while (*data != NULL)
	{
		x = 0;
		while (*data[x] != '\0')
		{
			while (*data[x] == ' ' || *data[x] == '\t')
				x++;
			if (y <= 3)
			{
				if (coordinates(*data, cartridge, x) == 0)
					error_msg("🚨 Map error - wrong coordinates! 🚨", data);
			}
			else if (y == 5 || y == 6)
			{
				if (ft_colours(*data, cartridge, x, y) == 0)
					error_msg("🚨 Map error - wrong colors! 🚨", data);
			}
			else if (y == 8)
			{
				if (map_validator(data, cartridge, y) == 0)
					error_msg("🚨 Map error - wrong map! 🚨", data);
			}
		}
		y++;
		data++;
	}
}
