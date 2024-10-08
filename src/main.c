/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 07:36:44 by davgalle          #+#    #+#             */
/*   Updated: 2024/09/03 12:14:51 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cube3d.h"

void	ft_printmap(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
	{
		ft_putstr(map[i]);
		write(1, "\n", 1);
		i++;
	}
}

char	**arg_check(int argc, char **argv, t_design *design, char **map)
{
	t_brain	brain;
	int		fd;
	int		file;

	new_brain(&brain);
	if (argc != 2)
		error_msg("🚨 Invalid number of arguments! 🚨", NULL);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("🚨 Error opening file! 🚨");
		exit(EXIT_FAILURE);
	}
	file = ft_strmapcmp(argv[1], ".cub", 4);
	if (file == 0)
		error_msg("🚨 The file is invalid - use a .cub file! 🚨", NULL);
	else if (file == 2)
		error_msg("🚨 The file is invalid - The file has no extension! 🚨", NULL);
	return (map_check(fd, design, map, &brain));
}

int	main(int argc, char **argv)
{
	char		**map;
	t_design	cartridge;

	new_design(&cartridge);
	map = NULL;
	if (argc == 1)
		error_msg("🚨 You have to upload a file to play! 🚨", NULL);
	map = arg_check(argc, argv, &cartridge, map);
	init_window(&cartridge);
	free_map(map);
	free_struct(&cartridge);
	return (0);
}
