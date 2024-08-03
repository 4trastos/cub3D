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
    unsigned int hex_color = (a << 24) | (r << 16) | (g << 8) | b;

    return (hex_color);
}

void	draw_wall(float dist, int nr, int color)
{
	mlx_image_t	wall;

	//dibujar una linea de la pared por rayo.
	// - Necesitaremos saber en que parte de la pantalla tiene que estar
	// - La distancia
	// - El colot varia segun si es vertical o horizontal
	// - Tamaño depende de la distancia
	// -luego hay que ver las coords de la pantalla
	// Work in progress
}

void    draw_floor(mlx_image_t *background, int *color)
{
    int y;
    int x;

    y = 0;
    while (y < (HEIGHT / 2))
    {
        x = 0;
        while (x < WIDTH)
        {
            mlx_put_pixel(background, x, y, rgb_to_hex(color[0], color[1], color[2], 0));
            x++;
        }
        y++;
    }
}

void    draw_ceiling(mlx_image_t *background, int *color)
{
    int y;
    int x;

    y = 0;
    while (y < (HEIGHT / 2))
    {
        x = 0;
        while (x < WIDTH)
        {
            mlx_put_pixel(background, x, y, rgb_to_hex(color[0], color[1], color[2], 0));
            x++;
        }
        y++;
    }
}

void    draw_map(mlx_t *mlx, t_design *catridge)
{
    int y;
    int x;
    mlx_image_t *wall;
	mlx_image_t *floor;

    wall = mlx_new_image(mlx, 60, 60);
	floor = mlx_new_image(mlx, 60, 60);
	ft_memset(wall->pixels, 200, wall->width * wall->height * sizeof(int32_t));
	ft_memset(floor->pixels, 120, floor->width * floor->height * sizeof(int32_t));
    y = 0;
	while (catridge->map[y] != NULL)
	{
		x = 0;
		while (catridge->map[y][x] != '\0')
		{
			if (catridge->map[y][x] == '1')
				mlx_image_to_window(mlx, wall, x * 64, y * 64);
			else if (catridge->map[y][x] == '0')
			mlx_image_to_window(mlx, floor, x * 64, y * 64);
			x++;
		}
		y++;
	}
}

float	get_dist(float px, float py, float rx, float ry)
{
	return (sqrt((rx - px) * (rx - px) + (ry - py) * (ry - py)));
}

void	rays(t_p *p)
{
	int	nr;
	int dof;
	float a_tan;
	float n_tan;
	float ra;
	float ry;
	float rx;
	float xo;
	float yo;
	float d_vert;
	float d_horiz;
	float t_pared;
	int mx;
	int my;

	ra = p->angle - RADIAN * 30;
	if (ra < 0)
		ra += 2 * PI;
	if (ra > 2 * PI)
		ra -= 2 * PI;
	nr = -1;
	while (++nr < 60)
	{
		//check de lineas horizontales
		dof = 0;
		a_tan = -1 / tan(ra);
		if (ra > PI) // looking down
		{
			ry = (((int)p->player->instances[0].y >> 6) << 6) - 0.00001;
			rx = (p->player->instances[0].y - ry) * a_tan + p->player->instances[0].x;
			yo = -64;
			xo = -yo * a_tan;
		}
		if (ra < PI) // looking up
		{
			ry = (((int)p->player->instances[0].y >> 6) << 6) + 64;
			rx = (p->player->instances[0].y - ry) * a_tan + p->player->instances[0].x;
			yo = 64;
			xo = -yo * a_tan;
		}
		if (ra == 0 || ra == PI) // angulos horizontales
		{
			rx = p->player->instances[0].x;
			ry = p->player->instances[0].y;
			dof = 8;
		}
		while (dof < get_width(p->map))
		{
			mx = (int) rx >> 6;
			my = (int) ry >> 6;
			if (my >= 0 && mx >= 0 && my < ft_countlines(p->map) && mx < (int)ft_strlen(p->map[my]) && p->map[my][mx] == '1')
				dof = get_width(p->map);
			else 
			{
				rx += xo;
				ry += yo;
				dof++;
			}
		}
		d_horiz = get_dist(p->player->instances[0].x, p->player->instances[0].y, rx, ry);
		// check de lineas verticales
		dof = 0;
		n_tan = -tan(ra);
		if (ra == P2 || ra == P3) // angulos vertical
		{
			rx = p->player->instances[0].x;
			ry = p->player->instances[0].y;
			dof = 8;
		}
		else if (ra > P2 && ra < P3) // looking left
		{
			rx = (((int)p->player->instances[0].x >> 6) << 6) - 0.00001;
			ry = (p->player->instances[0].x - rx) / n_tan + p->player->instances[0].y;
			xo = -64;
			yo = -xo / n_tan;
		}
		else if (ra < P2 || ra > P3) // looking right
		{
			rx = (((int)p->player->instances[0].x >> 6) << 6) + 64;
			ry = (p->player->instances[0].x - rx) / n_tan + p->player->instances[0].y;
			xo = 64;
			yo = -xo / n_tan;
		}
		while (dof < ft_countlines(p->map))
		{
			mx = (int) rx >> 6;
			my = (int) ry >> 6;
			if (my >= 0 && mx >= 0 && my < ft_countlines(p->map) && mx < (int)ft_strlen(p->map[my]) && p->map[my][mx] == '1')
				dof = ft_countlines(p->map);
			else 
			{
				rx += xo;
				ry += yo;
				dof++;
			}
		}
		d_vert = get_dist(p->player->instances[0].x, p->player->instances[0].y, rx, ry);
		if (d_vert < d_horiz)
		{
			t_pared = HEIGHT * 320 / d_vert;
			if (t_pared > 320)
				t_pared = 320;
			draw_wall(t_pared, 0x00202080);
		}
		else
		{
			t_pared = HEIGHT / d_horiz;
			if (t_pared > 320)
				t_pared = 320;
			draw_wall(t_pared, nr, 0x00802020);
		}
		ra += RADIAN;
		if (ra < 0)
			ra += 2 * PI;
		if (ra > 2 * PI)
			ra -= 2 * PI;
	}
}

void	key_press(mlx_key_data_t key, void *param)
{
	t_p		*p;
	float	dx;
	float	dy;

	p = param;
	dx = cos(p->angle) * 5.0f;
	dy = sin(p->angle) * 5.0f;
	rays(p);
	if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
		mlx_close_window(param);
	if (key.key == MLX_KEY_W && key.action != MLX_RELEASE)
	{
		p->player->instances[0].x -= dx;
		p->player->instances[0].y -= dy;
	}
	if (key.key == MLX_KEY_S && key.action != MLX_RELEASE)
	{
		p->player->instances[0].x -= -dx;
		p->player->instances[0].y -= -dy;
	}
	if (key.key == MLX_KEY_D && key.action != MLX_RELEASE)
	{
		p->angle += 0.25;
		if (p->angle > (RADIAN * 360))
			p->angle -= (RADIAN * 360);
	}
	if (key.key == MLX_KEY_A && key.action != MLX_RELEASE)
	{
		p->angle -= 0.25;
		if (p->angle < 0)
			p->angle += (RADIAN * 360);
	}
}

void    init_window(t_design *catridge)
{
    mlx_t       *mlx;
	mlx_image_t *floor;
	mlx_image_t *ceiling;
	t_p			p;

	catridge->height = ft_countlines(catridge->map) * 64;
	catridge->width = get_width(catridge->map) * 64;
    mlx = mlx_init(WIDTH, HEIGHT, "The Game", false);
	ceiling = mlx_new_image(mlx, WIDTH, HEIGHT / 2);
	draw_ceiling(ceiling, catridge->ceiling);
	mlx_image_to_window(mlx, ceiling, 0, 0);
	floor = mlx_new_image(mlx, WIDTH, HEIGHT / 2);
	draw_floor(floor, catridge->floor);
	mlx_image_to_window(mlx, floor, 0, HEIGHT / 2 + 1);
	get_player(&p, catridge->map);
	p.player = mlx_new_image(mlx, 20, 20);
	ft_memset(p.player->pixels, 0, p.player->width * p.player->height * sizeof(int32_t));
	mlx_image_to_window(mlx, p.player, (p.x * 64) + 16, (p.y *64) + 16);
	p.map = dupmatrix(catridge->map);
	rays(&p);
	mlx_key_hook(mlx, key_press, (void *)&p);
    mlx_loop(mlx);
}

