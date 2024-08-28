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

unsigned int rgb_to_hex(int r, int g, int b, int a) 
{
    r = (r < 0) ? 0 : (r > 255) ? 255 : r;
    g = (g < 0) ? 0 : (g > 255) ? 255 : g;
    b = (b < 0) ? 0 : (b > 255) ? 255 : b;
	a = (a < 0) ? 0 : (a > 255) ? 255 : a;
    unsigned int hex_color = (r << 24) | (g << 16) | (b << 8) | a;
	
    return (hex_color);
}

void    draw_ceiling(mlx_image_t *background, int *color_c, int *color_f)
{
    int y;
    int x;

    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
			if (y < HEIGHT / 2)
            	mlx_put_pixel(background, x, y, rgb_to_hex(color_c[0], color_c[1], color_c[2], 255));
			else
				mlx_put_pixel(background, x, y, rgb_to_hex(color_f[0], color_f[1], color_f[2], 255));
            x++;
        }
        y++;
    }
}

void	hook(void *param)
{
	t_g *game;

	game = param;
	rays(game);
}

void    init_window(t_design *catridge)
{
	t_g		game;
	t_p		player;

	catridge->height = ft_countlines(catridge->map) * SIZE;
	catridge->width = get_width(catridge->map) * SIZE;
	game.tex_1 = mlx_load_png("textures/aux.png");
	game.tex_2 = mlx_load_png("textures/texture.png");
	game.tex_3 = mlx_load_png("textures/treko.png");
	game.tex_4 = mlx_load_png ("textures/elden.png");
    game.mlx = mlx_init(WIDTH, HEIGHT, "The Game", false);
	game.ceiling = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	draw_ceiling(game.ceiling, catridge->ceiling, catridge->floor);
	mlx_image_to_window(game.mlx, game.ceiling, 0, 0);
	get_player(&player, catridge->map);
	game.color_c[0] = catridge->ceiling[0];
	game.color_c[1] = catridge->ceiling[1];
	game.color_c[2] = catridge->ceiling[2];
	game.color_f[0] = catridge->floor[0];
	game.color_f[1] = catridge->floor[1];
	game.color_f[2] = catridge->floor[2];
	game.p.x = player.x;
	game.p.y = player.y;
	game.p.vec_x = player.vec_x;
	game.p.vec_y = player.vec_y;
	if (game.p.vec_x != 0){
		if (game.p.vec_x < 0) {game.plane_x = 0; game.plane_y = 0.66;}
		else{game.plane_x = 0; game.plane_y = -0.66;}
	}
	else{
		if (game.p.vec_y < 0){game.plane_x = 0.66; game.plane_y = 0;}
		else{game.plane_x = -0.66; game.plane_y = 0;}		
	}
	game.p.px = game.p.x + 0.5;
	game.p.py = game.p.y + 0.5;
	game.p.map = dupmatrix(catridge->map);
	game.flag = 0;
	rays(&game);
	mlx_key_hook(game.mlx, key_press, (void *)&game);
	mlx_loop_hook(game.mlx, hook, &game);
    mlx_loop(game.mlx);
	mlx_delete_texture(game.tex_1);
	mlx_delete_texture(game.tex_2);
	mlx_delete_texture(game.tex_3);
	mlx_delete_texture(game.tex_4);
	free_map(game.p.map);
}

