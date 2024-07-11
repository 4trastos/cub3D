/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartridge.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:33:16 by davgalle          #+#    #+#             */
/*   Updated: 2024/07/09 10:55:40 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cube3d.h"

int	ft_colours(char *str, t_design *cartridge)
{
	char	**number;
	int		i;

	i = 0;
	skip_whitespace(&str);
	if (*str == 'F' && (*(str + 1) == ' ' || *(str + 1) == '\t')
		&& cartridge->floor_set == false)
	{
		str++;
		skip_whitespace(&str);
		number = ft_split(str, ',');
		if (!number)
			return (0);
		while (i < 3 && number[i] != NULL)
		{
			cartridge->floor[i] = ft_atoi(number[i]);
			i++;
		}
		cartridge->floor_set = true;
		free_map(number);
		return (1);
	}
	else if (*str == 'C' && (*(str + 1) == ' '
			|| *(str + 1) == '\t') && cartridge->ceiling_set == false)
	{
		str++;
		skip_whitespace(&str);
		number = ft_split(str, ',');
		if (!number)
			return (0);
		while (i < 3 && number[i] != NULL)
		{
			cartridge->ceiling[i] = ft_atoi(number[i]);
			i++;
		}
		cartridge->ceiling_set = true;
		free_map(number);
		return (1);
	}
	return (0);
}

int	coordinates(char *str, t_design *cartridge)
{
	if (!str || ft_strlen(str) < 2)
		return (0);
	if (str[0] == 'N' && str[1] == 'O' && cartridge->no == NULL)
	{
		str += 2;
		skip_whitespace(&str);
		cartridge->no = ft_strdup(str);
	}
	else if (str[0] == 'S' && str[1] == 'O' && cartridge->so == NULL)
	{
		str += 2;
		skip_whitespace(&str);
		cartridge->so = ft_strdup(str);
	}
	else if (str[0] == 'W' && str[1] == 'E' && cartridge->we == NULL)
	{
		str += 2;
		skip_whitespace(&str);
		cartridge->we = ft_strdup(str);
	}
	else if (str[0] == 'E' && str[1] == 'A' && cartridge->ea == NULL)
	{
		str += 2;
		skip_whitespace(&str);
		cartridge->ea = ft_strdup(str);
	}
	else
		return (0);
	return (1);
}

void	create_cartridge(char **data, t_design *cartridge, size_t y)
{
	y = 0;
	while (*data != NULL)
	{
		if (y <= 3)
		{
			if (coordinates(*data, cartridge) == 0)
				error_msg("🚨 Map error - wrong coordinates! 🚨", 0);
		}
		else if (y == 4 || y == 5)
		{
			if (ft_colours(*data, cartridge) == 0)
				error_msg("🚨 Map error - wrong colors! 🚨", 0);
		}
		else if (y == 6)
			cartridge->map = dupmatrix(data);
		y++;
		if (*data == NULL)
			return ;
		data++;
	}
}
