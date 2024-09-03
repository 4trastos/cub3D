/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicgonza <nicgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 07:36:44 by nicgonza          #+#    #+#             */
/*   Updated: 2024/08/08 10:14:29 by nicgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cube3d.h"

void	key_right(t_g *game)
{
	float	old_vec_x;
	float	old_vec_y;

	old_vec_x = game->p.vec_x;
	old_vec_y = game->p.vec_y;
	game->p.vec_x = old_vec_x * cos((2 * RADIAN))- old_vec_y * sin(2 *RADIAN);
	game->p.vec_y = old_vec_x * sin((2 * RADIAN))+ old_vec_y * cos(2 *RADIAN);
	old_vec_x = game->plane_x;
	old_vec_y = game->plane_y;
	game->plane_x = old_vec_x * cos((2 * RADIAN))- old_vec_y * sin(2 *RADIAN);
	game->plane_y = old_vec_x * sin((2 * RADIAN))+ old_vec_y * cos(2 *RADIAN);
}

void	key_left(t_g *game)
{
	float	old_vec_x;
	float	old_vec_y;

	old_vec_x = game->p.vec_x;
	old_vec_y = game->p.vec_y;
	game->p.vec_x = old_vec_x * cos(-(2 * RADIAN))- old_vec_y * sin(-(2 *RADIAN));
	game->p.vec_y = old_vec_x * sin(-(2 * RADIAN))+ old_vec_y * cos(-(2 *RADIAN));
	old_vec_x = game->plane_x;
	old_vec_y = game->plane_y;
	game->plane_x = old_vec_x * cos(-(2 * RADIAN))- old_vec_y * sin(-(2 *RADIAN));
	game->plane_y = old_vec_x * sin(-(2 * RADIAN))+ old_vec_y * cos(-(2 *RADIAN));
}
