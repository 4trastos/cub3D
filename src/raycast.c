/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 07:36:44 by davgalle          #+#    #+#             */
/*   Updated: 2024/07/11 13:52:59 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cube3d.h"

void    draw_background(mlx_image_t *background)
{
    int y;
    int x;

    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            mlx_put_pixel(background, x, y, 0x00696969);
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

    wall = mlx_new_image(mlx, 64, 64);
    
}

void    init_window(t_design *catridge)
{
    mlx_t       *mlx;
    mlx_image_t *background;

    mlx = mlx_init(WIDTH, HEIGHT, "duckvid the rancher", false);
    background = mlx_new_image(mlx, WIDTH, HEIGHT);
    draw_background(background);
    draw_map(mlx, catridge);
    mlx_loop(mlx);
}