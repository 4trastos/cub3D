/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 10:17:52 by davgalle          #+#    #+#             */
/*   Updated: 2024/07/05 13:56:08 by davgalle         ###   ########.fr       */
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

char	*read_file(int fd, char *str, t_design *design)
{
	char	*line;

	(void)design;
	line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		printf("Esto contiene LINE: --->>>> %s\n", line);
		if (!line)
		{
			free(line);
			break ;
		}
		str = ft_strjoin(str, line);
		printf("Esto contiene STR_01: --->>>> %s\n", str);
		free(line);
	}
	close(fd);
	if (ft_strlen(str) == 0)
		error_msg("🚨 map is empty - upload a valid map! 🚨", NULL);
	// if (char_validator(str) == 0)
	// 	error_msg("🚨 The loaded map contains invalid characters! 🚨", NULL);
	return (str);
}

char	**map_check(int fd, t_design *design, char **map)
{
	char	**copy;
	char	*str;

	str = NULL;
	copy = NULL;
	str = malloc(1);
	if (!str)
		return (NULL);
	str[0] = '\0';
	str = read_file(fd, str, design);
	printf("Esto contiene STR: --->>>> %s\n", str);
	map = ft_split(str, '\n');
	copy = ft_split(str, '\n');
	free(str);
	free_map(copy);
	return (map);
}
