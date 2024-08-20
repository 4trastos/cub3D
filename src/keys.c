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

void    key_w(t_g *game, float speed_x, float speed_y)
{
    if (game->p.map[(int)(game->p.py + speed_y)][(int)(game->p.px + speed_x)] != '1')
	{
		game->p.px += speed_x;
		game->p.py += speed_y;
	}
	rays(game);
}

void    key_s(t_g *game, float speed_x, float speed_y)
{
    if (game->p.map[(int)(game->p.py - speed_y)][(int)(game->p.px - speed_x)] != '1')
	{
		game->p.px += -speed_x;
		game->p.py += -speed_y;
	}
	rays(game);
}

void    key_d(t_g *game, float speed_x, float speed_y)
{
    if (game->p.map[(int)(game->p.py - speed_x)][(int)(game->p.px - speed_y)] != '1')
	{
		game->p.px += -speed_y;
		game->p.py += -speed_x;
	}
	rays(game);
}

void    key_a(t_g *game, float speed_x, float speed_y)
{
    if (game->p.map[(int)(game->p.py + speed_x)][(int)(game->p.px + speed_y)] != '1')
	{
		game->p.px += speed_y;
		game->p.py += speed_x;
	}
	rays(game);
}

void	key_press(mlx_key_data_t key, void *param)
{
	t_g	*game;
	float speed_x;
	float speed_y;

	game = param;
	speed_x = game->p.vec_x / 10.0f;
	speed_y = game->p.vec_y / 10.0f;
	if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
		mlx_close_window((void *)game->mlx);
	if (key.key == MLX_KEY_W && key.action != MLX_RELEASE)
		key_w(game, speed_x, speed_y);
	if (key.key == MLX_KEY_S && key.action != MLX_RELEASE)
		key_s(game, speed_x, speed_y);
	if (key.key == MLX_KEY_D && key.action != MLX_RELEASE)
		key_d(game, speed_x, speed_y);
	if (key.key == MLX_KEY_A && key.action != MLX_RELEASE)
		key_a(game, speed_x, speed_y);
	if (key.key == MLX_KEY_RIGHT && key.action != MLX_RELEASE)
		key_right(game);
	if (key.key == MLX_KEY_LEFT && key.action != MLX_RELEASE)
		key_left(game);
}

