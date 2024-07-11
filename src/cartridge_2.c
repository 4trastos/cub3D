/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartridge_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:10:47 by davgalle          #+#    #+#             */
/*   Updated: 2024/07/11 13:22:43 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cube3d.h"

void	upcolour_f(char **number, t_design *cartridge)
{
	int	i;

	i = 0;
	while (i < 3 && number[i] != NULL)
	{
		cartridge->floor[i] = ft_atoi(number[i]);
		i++;
	}
	cartridge->floor_set = true;
}

void	upcolour_c(char **number, t_design *cartridge)
{
	int	i;

	i = 0;
	while (i < 3 && number[i] != NULL)
	{
		cartridge->ceiling[i] = ft_atoi(number[i]);
		i++;
	}
	cartridge->ceiling_set = true;
}
