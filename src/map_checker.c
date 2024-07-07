/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usuario <usuario@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 10:17:52 by davgalle          #+#    #+#             */
/*   Updated: 2024/07/07 11:08:55 by usuario          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cube3d.h"

int	ft_strmapcmp(char *str, char *dst, int len)
{
	int	i;
	int	j;

	j = 0;
	while (str[j] != '/')
		j++;
	j++;
	if (str[j] == '.')
		return (2);
	i = 0;
	while (str[i] != '\0')
		i++;
	while (len >= 0)
	{
		if (dst[len] != str[i])
			return (0);
		len--;
		i--;
	}
	return (1);
}

char	*read_file(int fd, char *str)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
		{
			free(line);
			break ;
		}
		str = ft_strjoin(str, line);
		free(line);
	}
	close(fd);
	if (ft_strlen(str) == 0)
		error_msg("🚨 map is empty - upload a valid map! 🚨", NULL);
	if (char_validator(str) == 0)
		error_msg("🚨 The loaded map contains invalid characters! 🚨", NULL);
	return (str);
}

char	**map_check(int fd, t_design *cartridge, char **map)
{
	char	**copy;
	char	**data;
	char	*str;
	size_t	y;

	y = 0;
	str = NULL;
	copy = NULL;
	str = malloc(1);
	if (!str)
		return (NULL);
	str[0] = '\0';
	str = read_file(fd, str);
	data = ft_split(str, '\n');
	create_cartridge(data, cartridge, y);
	map = dupmatrix(cartridge->map);
	copy = dupmatrix(cartridge->map);
	if (walls_validator(copy) == 0)
		error_msg("🚨 Map error - It is not completely enclosed by walls! 🚨", data);
	free(str);
	free_map(copy);
	return (map);
}
