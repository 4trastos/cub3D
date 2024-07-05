/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:33:16 by davgalle          #+#    #+#             */
/*   Updated: 2024/07/05 13:45:46 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cube3d.h"

int	char_validator(char *str)
{
	char	*aux;

	aux = str;
	while (*aux)
	{
		write(1, aux, 1);
		if (*aux == '1' || *aux == '0' || *aux == 'N'
			|| *aux == 'E' || *aux == 'W' || *aux == 'S')
			aux++;
		else
			return (0);
	}
	free(aux);
	return (1);
}
