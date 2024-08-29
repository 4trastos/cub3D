/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 07:36:44 by davgalle          #+#    #+#             */
/*   Updated: 2024/07/11 13:52:59 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cube3d.h"

static void	vec_east(t_p *p)
{
	p->vec_x = 1.0f;
	p->vec_y = 0;
}

static void	vec_west(t_p *p)
{
	p->vec_x = -1.0f;
	p->vec_y = 0;
}

static void	vec_north(t_p *p)
{
	p->vec_x = 0;
	p->vec_y = -1.0f;
}

static void	vec_south(t_p *p)
{
	p->vec_x = 0;
	p->vec_y = 1.0f;
}

void	get_player(t_p *p, char **map)
{
	int		y;
	int		x;

	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0' && (map[y][x] == '0' || map[y][x] == '1'
			|| map[y][x] == ' ' || map[y][x] == '\t'))
			x++;
		if (map[y][x] != '\0' && map[y][x] != '0' && map[y][x] != '1'
			&& map[y][x] != ' ' && map[y][x] != '\t')
			break ;
		y++;
	}
	if (map[y][x] == 'N')
		vec_north(p);
	else if (map[y][x] == 'S')
		vec_south(p);
	else if (map[y][x] == 'E')
		vec_east(p);
	else if (map[y][x] == 'W')
		vec_west(p);
	p->x = x;
	p->y = y;
}
