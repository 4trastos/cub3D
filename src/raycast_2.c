/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 07:36:44 by davgalle          #+#    #+#             */
/*   Updated: 2024/07/11 13:52:59 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cube3d.h"

void	draw_r(int nr, int side, t_ray *r, t_g *game)
{
	t_tex_data		data;
	mlx_texture_t	*tex;

	if (side == 0 && r->ray_dir_x < 0)
		tex = game->tex_1;
	else if (side == 0 && r->ray_dir_x > 0)
		tex = game->tex_2;
	else if (r->ray_dir_y > 0)
		tex = game->tex_3;
	else
		tex = game->tex_4;
	if (!tex)
	{
		printf("Error: No se pudo cargar la textura.\n");
		return ;
	}
	draw_r_aux(&data, r, game, side);
	set_data(&data, side, r);
	while (++data.y <= data.d_end)
	{
		put_texture(&data, tex);
		mlx_put_pixel(game->ceiling, nr, data.y, data.color);
	}
}

int	ray_hit(t_ray *r, t_g *game)
{
	int	hit;
	int	side;

	hit = 0;
	while (hit == 0)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->d_dist_x;
			r->mx += r->step_x;
			side = 0;
		}
		else
		{
			r->side_dist_y += r->d_dist_y;
			r->my += r->step_y;
			side = 1;
		}
		if (game->p.map[r->my][r->mx] == '1')
			hit = 1;
	}
	return (side);
}

void	side_dist(t_ray *r, t_g *game)
{
	if (r->ray_dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (game->p.px - (float)r->mx) * r->d_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = ((float)r->mx + 1.0f - game->p.px) * r->d_dist_x;
	}
	if (r->ray_dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (game->p.py - (float)r->my) * r->d_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = ((float)r->my + 1.0f - game->p.py) * r->d_dist_y;
	}
}

void	redo_background(t_g *game)
{
	mlx_delete_image(game->mlx, game->ceiling);
	game->ceiling = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	draw_ceiling(game->ceiling, game->color_c, game->color_f);
	mlx_image_to_window(game->mlx, game->ceiling, 0, 0);
}

void	r(t_g *game)
{
	t_ray	r;
	float	camera_x;
	int		side;
	int		nr;

	nr = -1;
	if (game->flag != 0)
		redo_background(game);
	else
		game->flag = 1;
	while (++nr < WIDTH)
	{
		camera_x = 2 * nr / (double)WIDTH - 1;
		r.ray_dir_y = game->p.vec_y + game->plane_y * camera_x;
		r.ray_dir_x = game->p.vec_x + game->plane_x * camera_x;
		r.d_dist_y = fabs(1 / r.ray_dir_y);
		r.d_dist_x = fabs(1 / r.ray_dir_x);
		r.mx = (int)game->p.px;
		r.my = (int)game->p.py;
		side_dist(&r, game);
		side = ray_hit(&r, game);
		draw_r(nr, side, &r, game);
	}
}
