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

unsigned int	rgb_to_hex(int r, int g, int b, int a)
{
	r = (r < 0) ? 0 : (r > 255) ? 255 : r;
	g = (g < 0) ? 0 : (g > 255) ? 255 : g;
	b = (b < 0) ? 0 : (b > 255) ? 255 : b;
	a = (a < 0) ? 0 : (a > 255) ? 255 : a;
	unsigned int hex_color = (r << 24) | (g << 16) | (b << 8) | a;

	return (hex_color);
}

void	paint_wall(mlx_image_t *wall, int color)
{
	int	y;
	int	x;

	y = 0;
	while (y < (int)wall->height)
	{
		x = 0;
		while (x < (int)wall->width)
		{
			mlx_put_pixel(wall, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_ceiling(mlx_image_t *background, int *color_c, int *color_f)
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

void	draw_wall(float wall_height, int nr, unsigned int color, t_g *game)
{
	float		wall_offset;
	int			y;

	wall_offset = (HEIGHT - wall_height) / 2;
	if (wall_height < 1)
		wall_height = 1;
	y = 0;
	while (y < wall_height)
	{
		if (y + wall_offset < HEIGHT)
			mlx_put_pixel(game->ceiling, nr, y + wall_offset, color);
		y++;
	}
	mlx_image_to_window(game->mlx, game->ceiling, 0, 0);
}



float	get_dist(float px, float py, float rx, float ry)
{
	return (sqrt((rx - px) * (rx - px) + (ry - py) * (ry - py)));
}


void	rays(t_g *game)
{
	t_ray	rays[WIDTH];
	int		nr;

	nr = -1;
	rays[0].ra = game->p.angle + (45 * RADIAN);
	while (++nr < WIDTH)
	{
		if (rays[nr].ra > 0 && rays[nr].ra < PI)
		{
			rays[nr].ry = (game->p.py - (float)game->p.player->instances[0].y) * -1;
			if (rays[nr].ra >= (game->p.angle))
				rays[nr].rx = tan(rays[nr].ra - (game->p.angle)) * (game->p.py - (float)game->p.player->instances[0].y) * -1 ;
			else
				rays[nr].rx = tan((game->p.angle) - rays[nr].ra) * (game->p.py - (float)game->p.player->instances[0].y);
		}
		printf("RX: %f, RY: %f\n", rays[nr].rx, rays[nr].ry);
		if (nr + 1 < WIDTH)
		{
			rays[nr + 1].ra = rays[nr].ra - (((float)FOV / (float)WIDTH) * RADIAN);
			printf("ANGLE %f\n", rays[nr + 1].ra / RADIAN);
			if (rays[nr + 1].ra > (2 * PI))
				rays[nr + 1].ra -= (2 * PI);
			if (rays[nr + 1].ra < 0)
				rays[nr + 1].ra += (2 * PI);
		}
	}
}

void	key_press(mlx_key_data_t key, void *param)
{
	t_g		*game;
	float	dx;
	float	dy;

	game = param;
	dx = cos(game->p.angle) * 1.0f;
	dy = sin(game->p.angle) * 1.0f;
	if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
		mlx_close_window((void *)game->mlx);
	if (key.key == MLX_KEY_W && key.action != MLX_RELEASE)
	{
		game->p.player->instances[0].x -= dx;
		game->p.player->instances[0].y -= dy;
		game->p.px -= dx;
		game->p.py -= dy;
		rays(game);
	}
	if (key.key == MLX_KEY_S && key.action != MLX_RELEASE)
	{
		game->p.player->instances[0].x -= -dx;
		game->p.player->instances[0].y -= -dy;
		game->p.px -= -dx;
		game->p.px -= -dy;
	}
	if (key.key == MLX_KEY_RIGHT && key.action != MLX_RELEASE)
	{
		game->p.angle += 0.5;
		if (game->p.angle > (RADIAN * 360))
			game->p.angle -= (RADIAN * 360);
	}
	if (key.key == MLX_KEY_LEFT && key.action != MLX_RELEASE)
	{
		game->p.angle -= 0.5;
		if (game->p.angle < 0)
			game->p.angle += (RADIAN * 360);
	}
}

void    init_window(t_design *cartridge)
{
	t_g		game;
	t_p		player;

	cartridge->height = ft_countlines(cartridge->map) * SIZE;
	cartridge->width = get_width(cartridge->map) * SIZE;
	game.mlx = mlx_init(WIDTH, HEIGHT, "The Game", false);
	game.ceiling = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	draw_ceiling(game.ceiling, cartridge->ceiling, cartridge->floor);
	mlx_image_to_window(game.mlx, game.ceiling, 0, 0);
	get_player(&player, cartridge->map);
	game.color_c[0] = cartridge->ceiling[0];
	game.color_c[1] = cartridge->ceiling[1];
	game.color_c[2] = cartridge->ceiling[2];
	game.color_f[0] = cartridge->floor[0];
	game.color_f[1] = cartridge->floor[1];
	game.color_f[2] = cartridge->floor[2];
	game.p.angle = player.angle;
	game.p.x = player.x;
	game.p.y = player.y;
	game.p.player = mlx_new_image(game.mlx, 20, 20);
	ft_memset(game.p.player->pixels, 255, game.p.player->width * game.p.player->height * sizeof(int32_t));
	mlx_image_to_window(game.mlx, game.p.player, (game.p.x + 0.5), (game.p.y + 0.5));
	game.p.px = game.p.x + 0.5;
	game.p.py = game.p.y + 0.5;
	game.p.map = dupmatrix(cartridge->map);
	game.flag = 0;
	rays(&game);
	mlx_key_hook(game.mlx, key_press, (void *)&game);
	mlx_loop(game.mlx);
	free_map(game.p.map);
}

