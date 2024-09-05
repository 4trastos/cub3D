/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartridge.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:33:16 by davgalle          #+#    #+#             */
/*   Updated: 2024/08/08 13:08:13 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cube3d.h"

int	ft_colours(char *str, t_design *cartridge)
{
	char	**number;

	skip_whitespace(&str);
	if (*str == 'F' && (*(str + 1) == ' ' || *(str + 1) == '\t')
		&& cartridge->floor_set == false)
	{
		str++;
		skip_whitespace(&str);
		number = ft_split(str, ',');
		upcolour_f(number, cartridge);
		free_map(number);
		return (1);
	}
	else if (*str == 'C' && (*(str + 1) == ' '
			|| *(str + 1) == '\t') && cartridge->ceiling_set == false)
	{
		str++;
		skip_whitespace(&str);
		number = ft_split(str, ',');
		upcolour_c(number, cartridge);
		free_map(number);
		return (1);
	}
	return (0);
}

int	get_coordinates(char *str, t_design *cartridge, int flag)
{
	str += 2;
	skip_whitespace(&str);
	if (*str != '.')
		return (0);
	if (flag == NO)
		cartridge->no = ft_strdup(str);
	else if (flag == SO)
		cartridge->so = ft_strdup(str);
	else if (flag == WE)
		cartridge->we = ft_strdup(str);
	else if (flag == EA)
		cartridge->ea = ft_strdup(str);
	if (open(str, O_RDONLY) == -1)
		return (0);
	return (1);
}

int	coordinates(char *str, t_design *cartridge)
{
	int	flag;
	int	value;

	if (!str || ft_strlen(str) < 2)
		return (0);
	flag = 0;
	skip_whitespace(&str);
	value = (str[0] << 8 | str[1]);
	if (value == NO && cartridge->no == NULL)
		flag = NO;
	else if (value == SO && cartridge->so == NULL)
		flag = SO;
	else if (value == WE && cartridge->we == NULL)
		flag = WE;
	else if (value == EA && cartridge->ea == NULL)
		flag = EA;
	if (flag != 0)
	{
		if (get_coordinates(str, cartridge, flag) == 0)
			return (0);
		return (1);
	}
	return (0);
}

void	create_cartridge(char **data, t_design *cartridge, size_t y)
{
	y = 0;
	while (*data != NULL)
	{
		if (y <= 3)
		{
			if (coordinates(*data, cartridge) == 0)
				error_msg("🚨 Map error - wrong textures! 🚨", 0);
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
