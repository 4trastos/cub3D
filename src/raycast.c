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

void	draw_wall(float wall_height, int nr, unsigned int color, t_g *game)
{
	float		wall_offset;
	int	y;

	if (wall_height > HEIGHT)
		wall_height = HEIGHT;
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
	t_ray	rays;
	float	camera_x;
	float	perp_wall_dist;
	int		hit;
	int		step_x;
	int		step_y;
	int		side;
	int		nr;

	nr = -1;
	if (game->flag != 0)
	{
		mlx_delete_image(game->mlx, game->ceiling);
		game->ceiling = mlx_new_image(game->mlx, WIDTH, HEIGHT);
		draw_ceiling(game->ceiling, game->color_c, game->color_f);
		mlx_image_to_window(game->mlx, game->ceiling, 0, 0);	
	}
	else
		game->flag = 1;
	while (++nr < WIDTH){
		camera_x = 2 * nr / (double)WIDTH - 1;
		rays.ray_dir_x = game->p.vec_x + game->plane_x * camera_x;
		rays.ray_dir_y = game->p.vec_y + game->plane_y * camera_x;
		rays.delta_dist_x = sqrt((rays.ray_dir_y * rays.ray_dir_y) / (rays.ray_dir_x * rays.ray_dir_x));
		rays.delta_dist_y = sqrt((rays.ray_dir_x * rays.ray_dir_x) / (rays.ray_dir_y * rays.ray_dir_y));
		rays.mx = (int)game->p.px;
		rays.my = (int)game->p.py;
		if (rays.ray_dir_x < 0)
		{
			step_x = -1;
			rays.side_dist_x = (game->p.px - (float)rays.mx) * rays.delta_dist_x;
		}
		else
		{
			step_x = 1;
			rays.side_dist_x = ((float)rays.mx + 1.0f - game->p.px) * rays.delta_dist_x;
		}
		if (rays.ray_dir_y < 0)
		{
			step_y = -1;
			rays.side_dist_y = (game->p.py - (float)rays.my) * rays.delta_dist_y;
		}
		else
		{
			step_y = 1;
			rays.side_dist_y = ((float)rays.my + 1.0f - game->p.py) * rays.delta_dist_y;
		}
		hit = 0;
		while (hit == 0)
		{
			if (rays.side_dist_x < rays.side_dist_y)
			{
				rays.side_dist_x += rays.delta_dist_x;
				rays.mx += step_x;
				side = 0;
			}
			else
			{
				rays.side_dist_y += rays.delta_dist_x;
				rays.my += step_y;
				side = 1;
			}
			if (game->p.map[rays.my][rays.mx] == '1')
				hit = 1;
		}
		if (side == 0)
		{
			perp_wall_dist = (rays.side_dist_x - rays.delta_dist_x);
			draw_wall(((float)HEIGHT / perp_wall_dist), nr, 0xFFAA9900, game);
		}
		else
		{
			perp_wall_dist = (rays.side_dist_y - rays.delta_dist_y);
			draw_wall(((float)HEIGHT / perp_wall_dist), nr, 0x99AAFF00, game);
		}
	}
}

void	key_press(mlx_key_data_t key, void *param)
{
	t_g	*game;
	float speed_x;
	float speed_y;
	float old_vec_x;
	float old_vec_y;

	game = param;
	speed_x = game->p.vec_x / 10.0f;
	speed_y = game->p.vec_y / 10.0f;
	if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
		mlx_close_window((void *)game->mlx);
	if (key.key == MLX_KEY_W && key.action != MLX_RELEASE)
	{
		game->p.player->instances[0].x = game->p.px + (float)speed_x;
		game->p.player->instances[0].y = game->p.py + (float)speed_y;
		game->p.px += speed_x;
		game->p.py += speed_y;
		rays(game);
	}
	if (key.key == MLX_KEY_S && key.action != MLX_RELEASE)
	{
		game->p.player->instances[0].x = game->p.px - (float)speed_x;
		game->p.player->instances[0].y = game->p.py - (float)speed_y;
		game->p.px += -speed_x;
		game->p.py += -speed_y;
		rays(game);
	}
	if (key.key == MLX_KEY_RIGHT && key.action != MLX_RELEASE)
	{
		old_vec_x = game->p.vec_x;
		old_vec_y = game->p.vec_y;
		game->p.vec_x = old_vec_x * cos(-RADIAN)- old_vec_y * sin(-RADIAN);
		game->p.vec_y = old_vec_x * sin(-RADIAN)+ old_vec_y * cos(-RADIAN);
		rays(game);
	}
	if (key.key == MLX_KEY_LEFT && key.action != MLX_RELEASE)
	{
		old_vec_x = game->p.vec_x;
		old_vec_y = game->p.vec_y;
		game->p.vec_x = old_vec_x * cos(RADIAN)- old_vec_y * sin(RADIAN);
		game->p.vec_y = old_vec_x* sin(RADIAN)+ old_vec_y * cos(RADIAN);
		rays(game);
	}
}

void    init_window(t_design *catridge)
{
	t_g		game;
	t_p		player;

	catridge->height = ft_countlines(catridge->map) * SIZE;
	catridge->width = get_width(catridge->map) * SIZE;
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
	game.p.player = mlx_new_image(game.mlx, 20, 20);
	if (game.p.vec_x != 0){
		if (game.p.vec_x < 0) {game.plane_x = 0; game.plane_y = 0.66;}
		else{game.plane_x = 0; game.plane_y = -0.66;}
	}
	else{
		if (game.p.vec_y < 0){game.plane_x = 0.66; game.plane_y = 0;}
		else{game.plane_x = -0.66; game.plane_y = 0;}		
	}
	//printf("dir X: %f dir Y: %f\n plane X: %f plane Y: %f\n", game.p.vec_x, game.p.vec_y, game.plane_x, game.plane_y);
	ft_memset(game.p.player->pixels, 255, game.p.player->width * game.p.player->height * sizeof(int32_t));
	mlx_image_to_window(game.mlx, game.p.player, (game.p.x + 0.5), (game.p.y + 0.5));
	game.p.px = game.p.x + 0.5;
	game.p.py = game.p.y + 0.5;
	game.p.map = dupmatrix(catridge->map);
	game.flag = 0;
	rays(&game);
	mlx_key_hook(game.mlx, key_press, (void *)&game);
    mlx_loop(game.mlx);
	free_map(game.p.map);
}

