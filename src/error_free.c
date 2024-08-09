/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 07:36:13 by davgalle          #+#    #+#             */
/*   Updated: 2024/07/09 10:52:32 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cube3d.h"

void	error_msg(char *str, char **map)
{
	if (map)
		free_map(map);
	while (*str)
		write(1, str++, 1);
	write(1, "\n", 1);
	exit (1);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_coordinates(t_design *cartridge)
{
	if (cartridge->no != NULL)
		free(cartridge->no);
	if (cartridge->ea != NULL)
		free(cartridge->ea);
	if (cartridge->so != NULL)
		free(cartridge->so);
	if (cartridge->we != NULL)
		free(cartridge->we);
}

void	free_struct(t_design *cartridge)
{
	if (cartridge->map != NULL)
		free_map(cartridge->map);
	cartridge->map = NULL;
	free_coordinates(cartridge);
}
