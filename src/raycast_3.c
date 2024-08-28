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

void	set_data(t_tex_data *data, int side, t_ray *rays)
{
	data->line_hight = (float)HEIGHT / rays->perp_wall_dist;
	data->draw_start = -(data->line_hight) / 2.0f + (float)HEIGHT / 2.0f;
	if (data->draw_start < 0)
		data->draw_start = 0;
	data->draw_end = data->line_hight / 2.0f + (float)HEIGHT / 2.0f;
	if (data->draw_end >= HEIGHT)
		data->draw_end = HEIGHT - 1;
	data->tex_x = (int)(data->wall_x * (float)TEX_WIDTH);
	if (side == 1 && rays->ray_dir_y < 0)
		data->tex_x = TEX_WIDTH - data->tex_x - 1;
	if (side == 0 && rays->ray_dir_x > 0)
		data->tex_x = TEX_WIDTH - data->tex_x - 1;
	data->step = 1.0f * (float)TEX_HEIGHT / data->line_hight;
	data->tex_pos = (data->draw_start - (float)HEIGHT/ 2.0f + data->line_hight / 2.0f) * data->step;
	data->y = data->draw_start - 1;
}

void	put_texture(t_tex_data *data, mlx_texture_t *tex)
{
	int pixel_index;

	data->tex_y = (int)data->tex_pos & (TEX_HEIGHT - 1);
	data->tex_pos += data->step;
    pixel_index = (data->tex_y * tex->width + data->tex_x) * 4;
	if (pixel_index < (int)(tex->width * tex->height * 4))
    {
		if (pixel_index < 0)
			pixel_index = 1;
        uint8_t r = tex->pixels[pixel_index];
        uint8_t g = tex->pixels[pixel_index + 1];
        uint8_t b = tex->pixels[pixel_index + 2];
        uint8_t a = tex->pixels[pixel_index + 3];
        data->color = (r << 24) | (g << 16) | (b << 8) | a;
    }
}

void	draw_rays_aux(t_tex_data *data, t_ray *rays, t_g *game, int side)
{
	if (side == 0)
	{
		rays->perp_wall_dist = (rays->side_dist_x - rays->delta_dist_x);
		data->wall_x = game->p.py + rays->perp_wall_dist * rays->ray_dir_y;
	}
	else
	{
		rays->perp_wall_dist = (rays->side_dist_y - rays->delta_dist_y);
		data->wall_x = game->p.px + rays->perp_wall_dist * rays->ray_dir_x;
	}
	data->wall_x -= floor(data->wall_x);
}
