/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usuario <usuario@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:16:51 by davgalle          #+#    #+#             */
/*   Updated: 2024/07/06 10:00:16 by usuario          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cube3d.h"

char	*ft_new_line(char *board)
{
	char	*new_line;

	if (!board)
		return (NULL);
	if (!ft_strchr(board, '\n'))
	{
		free(board);
		return (NULL);
	}
	new_line = ft_strchr(board, '\n');
	new_line = ft_strdup(new_line);
	free(board);
	return (new_line);
}

char	*ft_line(char *board)
{
	char	*ln;
	int		i;

	i = 0;
	if (!board[i])
		return (NULL);
	if (!ft_strchr(board, '\n'))
		ln = ft_strdup(board);
	else
	{
		ln = malloc(ft_strchr(board, '\n') - board + 1);
		if (!ln)
			return (NULL);
		while (board[i] != '\n')
		{
			ln[i] = board[i];
			i++;
		}
		ln[i] = board[i];
		ln[i + 1] = '\0';
	}
	return (ln);
}

char	*ft_read(int fd, char *board)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
	{
		free(board);
		return (NULL);
	}
	bytes_read = 1;
	while (board && !ft_strchr(board, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(board);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		board = ft_strjoin(board, buffer);
	}
	free(buffer);
	return (board);
}

char	*get_next_line(int fd)
{
	static char	*board;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!board)
	{
		board = malloc(1);
		if (!board)
			return (NULL);
		board[0] = '\0';
	}
	board = ft_read(fd, board);
	if (!board)
		return (NULL);
	line = ft_line(board);
	board = ft_new_line(board);
	if (!line)
		return (NULL);
	return (line);
}
