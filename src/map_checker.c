/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 10:17:52 by davgalle          #+#    #+#             */
/*   Updated: 2024/09/06 16:37:03 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cube3d.h"

int	ft_findchar(char *str)
{
	int	i;
	int	flag;
	int	space;

	i = 0;
	flag = 0;
	space = 0;
	if (str[0] == ' ' || str[0] == '\n')
	{
		while (str[i] != '\0' && str[i] != '\n')
		{
			if (str[i] == '1' || str[i] == '0')
				flag = 1;
			else if (str[i] == ' ')
				space = 1;
			i++;
		}
		if (flag == 0 && space == 1)
			return (0);
	}
	return (1);
}

int	map_validator(char **map, t_brain *brain)
{
	char	**copy;

	copy = dupmatrix(map);
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
	if (validate_map(map, brain) == 1)
	{
		error_msg("🚨 Wrong map! 🚨", NULL);
		return (0);
	}
	if (ft_flood(copy, brain) == 1)
	{
		error_msg("🚨 The loaded map contains invalid characters! 🚨", NULL);
		return (0);
	}
	free_map (copy);
	return (1);
}

int	ft_strmapcmp(char *str, char *dst, int len)
{
	char	*end;
	int		i;

	end = NULL;
	while (*str != '/')
		str++;
	str++;
	if (*str == '.')
	{
		end = ft_strchr(str + 1, '.');
		if (end != NULL)
			return (1);
		return (2);
	}
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
	int		space;

	space = 0;
	line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] == '\n' || (ft_findchar(line) == 0))
		{
			space++;
			if (space == 3)
			{
				error_msg("🚨 Wrong map! 🚨", NULL);
				return (NULL);
			}
		}
		str = ft_strjoin(str, line);
		free(line);
	}
	free(line);
	return (str);
}

char	**map_check(int fd, t_design *cartridge, char **map, t_brain *brain)
{
	char	**data;
	char	**copy;
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
	copy = dupmatrix(cartridge->map);
	if (map_validator(copy, brain) == 0)
	{
		free_map (copy);
		return (NULL);
	}
	map = dupmatrix(cartridge->map);
	free_map (copy);
	return (map);
}
