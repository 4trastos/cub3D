/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 07:59:25 by davgalle          #+#    #+#             */
/*   Updated: 2024/07/05 12:08:50 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cube3d.h"

t_design	*new_design(void)
{
	t_design	*new;

	new = (t_design *)malloc(sizeof(t_design));
	if (!new)
		return (NULL);
	return (new);
}

t_error	*new_error(void)
{
	t_error	*new;

	new = (t_error *)malloc(sizeof(t_error));
	if (!new)
		return (NULL);
	new->wall = 1;
	new->space = 0;
	new->player = 'N';
	return (new);
}
