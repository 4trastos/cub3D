/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usuario <usuario@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:33:16 by davgalle          #+#    #+#             */
/*   Updated: 2024/07/06 19:24:22 by usuario          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cube3d.h"

int	char_validator(char *str)
{
	char	*aux;

	aux = str;
	write(1, "### ENTRA A PARSEAR LETRAS ###\n", 31);
	while (*aux)
	{
		if (*aux == '1' || *aux == '0' || *aux == 'N'
			|| *aux == 'E' || *aux == 'W' || *aux == 'S' || *aux == '\n'
			|| *aux == ' ' || *aux == '\t')
			aux++;
		else
			return (0);
	}
	return (1);
}

int	walls_validator(char **copy)
{
	(void)copy;
	write(1, "### ENTREA A PARSEAR MUROS ###\n", 32);
	return (1);
}
