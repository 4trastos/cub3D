/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 07:36:44 by davgalle          #+#    #+#             */
/*   Updated: 2024/07/11 13:52:59 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cube3d.h"

unsigned int	r2h(int r, int g, int b, int a)
{
	unsigned int	hex_color;

	if (r < 0)
		r = 0;
	else if (r > 255)
		r = 255;
	if (g < 0)
		g = 0;
	else if (g > 255)
		g = 255;
	if (b < 0)
		b = 0;
	else if (b > 255)
		b = 255;
	if (a < 0)
		a = 0;
	else if (a > 255)
		a = 255;
	hex_color = (r << 24) | (g << 16) | (b << 8) | a;
	return (hex_color);
}

void	draw_ceiling(mlx_image_t *b, int *c_c, int *c_f)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				mlx_put_pixel(b, x, y, r2h(c_c[0], c_c[1], c_c[2], 255));
			else
				mlx_put_pixel(b, x, y, r2h(c_f[0], c_f[1], c_f[2], 255));
			x++;
		}
		y++;
	}
}

void	hook(void *param)
{
	t_g		*game;
	float	speed_x;
	float	speed_y;

	game = param;
	r(game);
	speed_x = game->p.vec_x / 7.0f;
	speed_y = game->p.vec_y / 7.0f;
	if (game->move_w == true)
		move_player(game, speed_x, speed_y);
	else if (game->move_s == true)
		move_player(game, -speed_x, -speed_y);
	else if ((game->move_d == true && (game->p.dir == N || game->p.dir == S))
		|| (game->move_a && (game->p.dir == E || game->p.dir == W)))
		move_player(game, -speed_y, speed_x);
	else if ((game->move_a == true && (game->p.dir == N || game->p.dir == S))
		|| (game->move_d && (game->p.dir == E || game->p.dir == W)))
		move_player(game, speed_y, -speed_x);
	else if ((game->move_r == true && (game->p.dir == N || game->p.dir == S))
		|| (game->move_l && (game->p.dir == E || game->p.dir == W)))
		key_right(game);
	else if ((game->move_l == true && (game->p.dir == N || game->p.dir == S))
		|| (game->move_r && (game->p.dir == E || game->p.dir == W)))
		key_left(game);
}

void	init_game(t_g *game, t_design *cartidge)
{
	game->tex_1 = mlx_load_png(cartidge->no);
	game->tex_2 = mlx_load_png(cartidge->so);
	game->tex_3 = mlx_load_png(cartidge->we);
	game->tex_4 = mlx_load_png(cartidge->ea);
	game->color_c[0] = cartidge->ceiling[0];
	game->color_c[1] = cartidge->ceiling[1];
	game->color_c[2] = cartidge->ceiling[2];
	game->color_f[0] = cartidge->floor[0];
	game->color_f[1] = cartidge->floor[1];
	game->color_f[2] = cartidge->floor[2];
	set_cord(game);
	game->p.px = game->p.x + 0.5;
	game->p.py = game->p.y + 0.5;
	game->flag = 0;
	game->move_w = false;
	game->move_s = false;
	game->move_a = false;
	game->move_d = false;
	game->move_r = false;
	game->move_l = false;
}

void	init_window(t_design *catridge)
{
	t_g		game;
	t_p		player;

	catridge->height = ft_countlines(catridge->map) * SIZE;
	catridge->width = get_width(catridge->map) * SIZE;
	get_player(&player, catridge->map);
	game.p.x = player.x;
	game.p.y = player.y;
	game.p.dir = player.dir;
	game.p.vec_x = player.vec_x;
	game.p.vec_y = player.vec_y;
	init_game(&game, catridge);
	game.mlx = mlx_init(WIDTH, HEIGHT, "The Game", false);
	game.ceiling = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	draw_ceiling(game.ceiling, catridge->ceiling, catridge->floor);
	mlx_image_to_window(game.mlx, game.ceiling, 0, 0);
	game.p.map = dupmatrix(catridge->map);
	mlx_key_hook(game.mlx, key_press, (void *)&game);
	mlx_loop_hook(game.mlx, hook, &game);
	mlx_loop(game.mlx);
	mlx_delete_texture(game.tex_1);
	mlx_delete_texture(game.tex_2);
	mlx_delete_texture(game.tex_3);
	mlx_delete_texture(game.tex_4);
	free_map(game.p.map);
}
