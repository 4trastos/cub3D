/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 10:17:52 by davgalle          #+#    #+#             */
/*   Updated: 2024/07/09 13:15:07 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cube3d.h"

int	map_validator(char **map)
{
	if (char_validator(map) == 0)
	{
		error_msg("🚨 The loaded map contains invalid characters! 🚨", NULL);
		return (0);
	}
	if (player_validator(map) == 0)
	{
		error_msg("🚨 The loaded map contains an invalid player! 🚨", NULL);
		return (0);
	}
	if (walls_validator(map) == 0)
	{
		error_msg("🚨 The map is not closed by walls! 🚨", NULL);
		return (0);
	}
	return (1);
}

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
	return (str);
}


char	**map_check(int fd, t_design *cartridge, char **map)
{
	char	**data;
	char	*str;
	size_t	y;

	y = 0;
	str = NULL;
	str = malloc(1);
	if (!str)
		return (NULL);
	str[0] = '\0';
	str = read_file(fd, str);
	data = ft_split(str, '\n');
	free(str);
	create_cartridge(data, cartridge, y);
	free_map(data);
	map = dupmatrix(cartridge->map);
	if (map_validator(map) == 0)
		return (map);
	return (map);
}
