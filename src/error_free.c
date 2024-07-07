/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usuario <usuario@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 07:36:13 by davgalle          #+#    #+#             */
/*   Updated: 2024/07/07 10:57:27 by usuario          ###   ########.fr       */
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
	char	**temp;

	temp = map;
	while (*map)
	{
		free(*map);
		map++;
	}
	free(temp);
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
	if (!cartridge)
		return ;
	if (cartridge->map != NULL)
		free_map(cartridge->map);
	cartridge->map = NULL;
	free_coordinates(cartridge);
	if (cartridge->ceiling != NULL)
		free(cartridge->ceiling);
	if (cartridge->floor != NULL)
		free(cartridge->floor);
	free(cartridge);
}
