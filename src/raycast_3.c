/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 07:36:44 by davgalle          #+#    #+#             */
/*   Updated: 2024/07/11 13:52:59 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cube3d.h"

void	set_data(t_tex_data *d, int side, t_ray *r)
{
	d->lh = (float)HEIGHT / r->perp_wall_dist;
	d->d_start = -(d->lh) / 2.0f + (float)HEIGHT / 2.0f;
	if (d->d_start < 0)
		d->d_start = 0;
	d->d_end = d->lh / 2.0f + (float)HEIGHT / 2.0f;
	if (d->d_end >= HEIGHT)
		d->d_end = HEIGHT - 1;
	d->tex_x = (int)(d->wall_x * (float)TEX_WIDTH);
	if (side == 1 && r->ray_dir_y < 0)
		d->tex_x = TEX_WIDTH - d->tex_x - 1;
	if (side == 0 && r->ray_dir_x > 0)
		d->tex_x = TEX_WIDTH - d->tex_x - 1;
	d->step = 1.0f * (float)TEX_HEIGHT / d->lh;
	d->t_pos = (d->d_start - (float)HEIGHT / 2.0f + d->lh / 2.0f) * d->step;
	d->y = d->d_start - 1;
}

void	put_texture(t_tex_data *data, mlx_texture_t *tex)
{
	int		pixel_index;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	data->tex_y = (int)data->t_pos & (TEX_HEIGHT - 1);
	data->t_pos += data->step;
	pixel_index = (data->tex_y * tex->width + data->tex_x) * 4;
	if (pixel_index < (int)(tex->width * tex->height * 4))
	{
		if (pixel_index < 0)
			pixel_index = 1;
		r = tex->pixels[pixel_index];
		g = tex->pixels[pixel_index + 1];
		b = tex->pixels[pixel_index + 2];
		a = tex->pixels[pixel_index + 3];
		data->color = (r << 24) | (g << 16) | (b << 8) | a;
	}
}

void	draw_r_aux(t_tex_data *data, t_ray *r, t_g *game, int side)
{
	if (side == 0)
	{
		r->perp_wall_dist = (r->side_dist_x - r->d_dist_x);
		data->wall_x = game->p.py + r->perp_wall_dist * r->ray_dir_y;
	}
	else
	{
		r->perp_wall_dist = (r->side_dist_y - r->d_dist_y);
		data->wall_x = game->p.px + r->perp_wall_dist * r->ray_dir_x;
	}
	data->wall_x -= floor(data->wall_x);
}

static void	set_cord_aux(t_g *game)
{
	game->plane_x = -0.66;
	game->plane_y = 0;
}

void	set_cord(t_g *game)
{
	if (game->p.vec_x != 0)
	{
		if (game->p.vec_x < 0)
		{
			game->plane_x = 0;
			game->plane_y = 0.66;
		}
		else
		{
			game->plane_x = 0;
			game->plane_y = -0.66;
		}
	}
	else
	{
		if (game->p.vec_y < 0)
		{
			game->plane_x = 0.66;
			game->plane_y = 0;
		}
		else
		{
			set_cord_aux(game);
		}
	}
}
