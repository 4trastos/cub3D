/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usuario <usuario@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 07:59:25 by davgalle          #+#    #+#             */
/*   Updated: 2024/07/07 11:06:27 by usuario          ###   ########.fr       */
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
	new->floor = (int *)malloc(3 * (sizeof(int)));
	new->ceiling = (int *)malloc(3 * (sizeof(int)));
	if (!new->ceiling || new->floor)
		return (free(new), NULL);
	while (i < 3)
	{
		new->ceiling[i] = 0;
		new->floor[i] = 0;
		i++;
	}
	new->floor_set = false;
	new->ceiling_set = false;
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
