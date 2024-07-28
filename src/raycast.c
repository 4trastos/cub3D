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

void    draw_background(mlx_image_t *background, t_design *catridge)
{
    int y;
    int x;

    y = 0;
    while (y < catridge->height)
    {
        x = 0;
        while (x < catridge->width)
        {
            mlx_put_pixel(background, x, y, 0x00010101);
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

void	rays(t_p *p, float dx, float dy)
{
	int	nr;
	int dof;
	float a_tan;
	float ra;
	float ry;
	float rx;
	float xo;
	float yo;
	int mx;
	int my;
	int	mp;

	ra = p->angle;
	nr = -1;
	while (++nr < 1)
	{
		//check de lineas horizontales
		dof = 0;
		a_tan = -1 / tan(ra);
		if (ra > PI) // looking down
		{
			ry = (((int)p->player->instances[0].y >> 6) << 6) - 0.00001;
			rx = (p->player->instances[0].y - ry) * a_tan + p->player->instances[0].x;
			yo -= 64;
			xo -= yo * a_tan;
		}
		if (ra < PI) // looking up
		{
			ry = (((int)p->player->instances[0].y >> 6) << 6) + 64;
			rx = (p->player->instances[0].y - ry) * a_tan + p->player->instances[0].x;
			yo = 64;
			xo -= yo * a_tan;
		}
		if (ra == 0 || ra == PI) // angulos horizontales
		{
			rx = p->player->instances[0].x;
			ry = p->player->instances[0].y;
			dof = 8;
		}
		while (dof < 8)
		{

		}
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
	rays(p, dx, dy);
	if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
		mlx_close_window(param);
	if (key.key == MLX_KEY_W && key.action != MLX_RELEASE)
	{
		p->player->instances[0].x -= dx;
		p->player->instances[0].y -= dy;
	}
	if (key.key == MLX_KEY_S && key.action != MLX_RELEASE)
	{
		p->player->instances[0].x += dx;
		p->player->instances[0].y += dy;
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
    mlx_image_t *background;
	t_p			p;

	catridge->height = ft_countlines(catridge->map) * 64;
	catridge->width = get_width(catridge->map) * 64;
    mlx = mlx_init(catridge->width, catridge->height, "duckvid the rancher", false);
    background = mlx_new_image(mlx, catridge->width, catridge->height);
    draw_background(background, catridge);
    draw_map(mlx, catridge);
	get_player(&p, catridge->map);
	p.player = mlx_new_image(mlx, 20, 20);
	ft_memset(p.player->pixels, 255, p.player->width * p.player->height * sizeof(int32_t));
	mlx_image_to_window(mlx, p.player, (p.x * 64) + 16, (p.y *64) + 16);
	p.map = dupmatrix(catridge->map);
	mlx_key_hook(mlx, key_press, (void *)&p);
    mlx_loop(mlx);
}

