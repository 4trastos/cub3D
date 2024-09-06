/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartridge_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:10:47 by davgalle          #+#    #+#             */
/*   Updated: 2024/09/06 11:09:20 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cube3d.h"

static int	check_float(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (-1);
		i++;
	}
	return (0);
}

void	upcolour_f(char **number, t_design *cartridge)
{
	int	i;
	int	rgb;

	i = 0;
	rgb = ft_countlines(number);
	if (rgb != 3)
		error_msg("🚨 Wrong Colour! 🚨", NULL);
	while (i < 3 && number[i] != NULL)
	{
		if (check_float(number[i]) == -1)
			error_msg("🚨 Wrong Colour! 🚨", NULL);
		cartridge->floor[i] = ft_atoi(number[i]);
		if (cartridge->floor[i] > 256 || cartridge->floor[i] < 0)
			error_msg("🚨 Wrong Colour! 🚨", NULL);
		i++;
	}
	cartridge->floor_set = true;
}

void	upcolour_c(char **number, t_design *cartridge)
{
	int	i;
	int	rgb;

	i = 0;
	rgb = ft_countlines(number);
	if (rgb != 3)
		error_msg("🚨 Wrong Colour! 🚨", NULL);
	while (i < 3 && number[i] != NULL)
	{
		if (check_float(number[i]) == -1)
			error_msg("🚨 Wrong Colour! 🚨", NULL);
		cartridge->ceiling[i] = ft_atoi(number[i]);
		if (cartridge->ceiling[i] > 256 || cartridge->ceiling[i] < 0)
			error_msg("🚨 Wrong Colour! 🚨", NULL);
		i++;
	}
	cartridge->ceiling_set = true;
}
