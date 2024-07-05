/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 07:49:49 by davgalle          #+#    #+#             */
/*   Updated: 2024/07/05 12:43:53 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cube3d.h"

size_t	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_putstr(char *str)
{
	char	*aux;

	aux = str;
	while (*aux)
		write(1, aux++, 1);
}

char	*ft_strdup(char *str)
{
	char	*new;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	new = malloc(ft_strlen(str) + 1);
	if (!new)
		return (NULL);
	while (str[i] != '\0')
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_strjoin(char *board, char *buffer)
{
	size_t	i;
	size_t	z;
	char	*board_dir;

	if (ft_strlen(buffer) == 0)
		return (board);
	board_dir = malloc((ft_strlen(board) + ft_strlen(buffer) + 1));
	if (!board_dir)
	{
		free(board);
		return (NULL);
	}
	i = -1;
	while (board[++i] != '\0')
		board_dir[i] = board[i];
	z = 0;
	while (buffer[z] != '\0')
		board_dir[i++] = buffer[z++];
	board_dir[i] = '\0';
	free(board);
	return (board_dir);
}

char	*ft_strchr(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (unsigned char)c)
			return ((char *)&str[i] + 1);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&str[i]);
	return (NULL);
}
