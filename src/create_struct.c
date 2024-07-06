/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usuario <usuario@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 07:59:25 by davgalle          #+#    #+#             */
/*   Updated: 2024/07/06 21:20:47 by usuario          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cube3d.h"

t_design	*new_design(void)
{
	t_design	*new;
	int			i;

	new = (t_design *)malloc(sizeof(t_design));
	if (!new)
		return (NULL);
	i = 0;
	new->no = NULL;
	new->ea = NULL;
	new->so = NULL;
	new->we = NULL;
	while (i < 3)
	{
		new->ceiling[i] = 0;
		new->floor[i] = 0;
		i++;
	}
	return (new);
}

t_game	*new_game(void)
{
	t_game	*new;

	new = (t_game *)malloc(sizeof(t_game));
	if (!new)
		return (NULL);
	return (new);
}
