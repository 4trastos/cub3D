/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usuario <usuario@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 07:49:49 by davgalle          #+#    #+#             */
/*   Updated: 2024/07/06 13:07:52 by usuario          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cube3d.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
}

char	*ft_strdup(char *str)
{
	char	*new;
	int		i;

	i = -1;
	if (!str)
		return (NULL);
	new = malloc(ft_strlen(str) + 1);
	if (!new)
		return (NULL);
	while (str[++i] != '\0')
		new[i] = str[i];
	new[i] = '\0';
	return (new);
}

char	*ft_strjoin(char *board, char *buffer)
{
	char	*new;
	int		i;
	int		j;

	if (ft_strlen(buffer) == 0)
		return (board);
	new = malloc(ft_strlen(board) + ft_strlen(buffer) + 1);
	if (!new)
	{
		free(board);
		return (NULL);
	}
	i = -1;
	j = 0;
	while (board[++i] != '\0')
		new[i] = board[i];
	while (buffer[j] != '\0')
		new[i++] = buffer[j++];
	new[i] = '\0';
	free(board);
	return (new);
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
