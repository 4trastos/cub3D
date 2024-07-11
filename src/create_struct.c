/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 07:59:25 by davgalle          #+#    #+#             */
/*   Updated: 2024/07/09 10:18:26 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cube3d.h"

void	new_design(t_design *new)
{
	new->ceiling_set = false;
	new->floor_set = false;
	new->no = NULL;
	new->so = NULL;
	new->ea = NULL;
	new->we = NULL;
}

t_game	*new_game(void)
{
	t_game	*new;

	new = (t_game *)malloc(sizeof(t_game));
	if (!new)
		return (NULL);
	return (new);
}
