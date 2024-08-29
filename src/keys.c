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
}

void	key_press(mlx_key_data_t key, void *param)
{
	t_g		*game;
	float	speed_x;
	float	speed_y;

	game = param;
	speed_x = game->p.vec_x / 10.0f;
	speed_y = game->p.vec_y / 10.0f;
	if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
		mlx_close_window((void *)game->mlx);
	if (key.action != MLX_RELEASE)
	{
		if (key.key == MLX_KEY_W)
			move_player(game, speed_x, speed_y);
		else if (key.key == MLX_KEY_S)
			move_player(game, -speed_x, -speed_y);
		else if (key.key == MLX_KEY_D)
			move_player(game, -speed_y, speed_x);
		else if (key.key == MLX_KEY_A)
			move_player(game, -(-speed_y), -(speed_x));
		else if (key.key == MLX_KEY_RIGHT)
			key_right(game);
		else if (key.key == MLX_KEY_LEFT)
			key_left(game);
	}
}
