/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brain_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 08:30:35 by davgalle          #+#    #+#             */
/*   Updated: 2024/07/17 09:32:39 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cube3d.h"

void	reset_move(t_brain *brain)
{
	brain->up = false;
	brain->down = false;
	brain->left = false;
	brain->right = false;
}
