/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicgonza <nicgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 07:36:44 by nicgonza          #+#    #+#             */
/*   Updated: 2024/08/08 10:14:29 by nicgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cube3d.h"

void	move_player(t_g *game, float move_x, float move_y)
{
	if (game->p.map[(int)(game->p.py + move_y)][(int)(game->p.px + move_x)]
		!= '1')
	{
		game->p.px += move_x;
		game->p.py += move_y;
	}
	game->move_w = false;
	game->move_s = false;
	game->move_d = false;
	game->move_a = false;
}

void	key_press(mlx_key_data_t key, void *param)
{
	t_g		*game;

	game = param;
	if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
		mlx_close_window((void *)game->mlx);
	if (key.action != MLX_RELEASE)
	{
		if (key.key == MLX_KEY_W)
			game->move_w = true;
		else if (key.key == MLX_KEY_S)
			game->move_s = true;
		else if (key.key == MLX_KEY_D)
			game->move_d = true;
		else if (key.key == MLX_KEY_A)
			game->move_a = true;
		else if (key.key == MLX_KEY_RIGHT)
			game->move_r = true;
		else if (key.key == MLX_KEY_LEFT)
			game->move_l = true;
	}
}
