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

void    draw_rays(int nr, int side, t_ray *rays, t_g *game)
{
	float	wall_x;
	int		tex_x;
	int		tex_y;
	float	line_hight;
	float	step;
	int		draw_start;
	int		draw_end;
	float	tex_pos;
	int		y;
	mlx_texture_t *tex;

	tex = mlx_load_png("../tetxures/texture.png");
    if (side == 0)
	{
		rays->perp_wall_dist = (rays->side_dist_x - rays->delta_dist_x);
		//draw_wall(((float)HEIGHT / rays->perp_wall_dist), nr, rgb_to_hex(0, 255, 255, 255), game);
		wall_x = game->p.py + rays->perp_wall_dist * rays->ray_dir_y;
	}
	else
	{
		rays->perp_wall_dist = (rays->side_dist_y - rays->delta_dist_y);
		//draw_wall(((float)HEIGHT / rays->perp_wall_dist), nr, rgb_to_hex(170, 255, 255, 255), game);
		wall_x = game->p.px + rays->perp_wall_dist * rays->ray_dir_x;
	}
	line_hight = (float)HEIGHT / rays->perp_wall_dist;
	draw_start = -line_hight / 2.0f + (float)HEIGHT / 2.0f;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_hight / 2.0f + (float)HEIGHT / 2.0f;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	tex_x = (int)(wall_x * (float)TEX_WIDTH);
	if (side == 0 && rays->ray_dir_x > 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	if (side == 0 && rays->ray_dir_y < 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	step = 1.0f * (float)TEX_HEIGHT / line_hight;
	tex_pos = (draw_start - h / 2 + line_hight / 2) * step;
	y = draw_start - 1;
	while (++y < draw_end)
	{
		tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
		tex_pos += step;
	}
}

int ray_hit(t_ray *rays, t_g *game)
{
    int hit;
    int side;

    hit = 0;
	while (hit == 0)
	{
		if (rays->side_dist_x < rays->side_dist_y)
		{
			rays->side_dist_x += rays->delta_dist_x;
			rays->mx += rays->step_x;
			side = 0;
		}
		else
		{
			rays->side_dist_y += rays->delta_dist_y;
			rays->my += rays->step_y;
			side = 1;
		}
		if (game->p.map[rays->my][rays->mx] == '1')
			hit = 1;
	}
    return (side);
}

void    side_dist(t_ray *rays, t_g *game)
{
    if (rays->ray_dir_x < 0)
	{
		rays->step_x = -1;
		rays->side_dist_x = (game->p.px - (float)rays->mx) * rays->delta_dist_x;
	}
	else
	{
		rays->step_x = 1;
		rays->side_dist_x = ((float)rays->mx + 1.0f - game->p.px) * rays->delta_dist_x;
	}
	if (rays->ray_dir_y < 0)
	{
		rays->step_y = -1;
		rays->side_dist_y = (game->p.py - (float)rays->my) * rays->delta_dist_y;
	}
	else
	{
		rays->step_y = 1;
		rays->side_dist_y = ((float)rays->my + 1.0f - game->p.py) * rays->delta_dist_y;
	}
}

void    redo_background(t_g *game)
{
    mlx_delete_image(game->mlx, game->ceiling);
	game->ceiling = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    draw_ceiling(game->ceiling, game->color_c, game->color_f);
	mlx_image_to_window(game->mlx, game->ceiling, 0, 0);
}

void	rays(t_g *game)
{
	t_ray	rays;
	float	camera_x;
	int		side;
	int		nr;

	nr = -1;
	if (game->flag != 0)
		redo_background(game);
	else
		game->flag = 1;
	while (++nr < WIDTH){
		camera_x = 2 * nr / (double)WIDTH - 1;
		rays.ray_dir_y = game->p.vec_y + game->plane_y * camera_x;
		rays.ray_dir_x = game->p.vec_x + game->plane_x * camera_x;
		rays.delta_dist_y = fabs(1 / rays.ray_dir_y);
		rays.delta_dist_x = fabs(1 / rays.ray_dir_x);
		rays.mx = (int)game->p.px;
		rays.my = (int)game->p.py;
		side_dist(&rays, game);
		side = ray_hit(&rays, game);
		draw_rays(nr, side, &rays, game);
	}
}
