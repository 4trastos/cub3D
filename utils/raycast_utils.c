/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicgonza <nicgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 07:36:44 by davgalle          #+#    #+#             */
/*   Updated: 2024/09/04 12:01:52 by nicgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cube3d.h"

static void	vec_east(t_p *p, char pos)
{
	p->vec_x = -1.0f;
	p->vec_y = 0;
	p->dir = pos;
}

static void	vec_west(t_p *p, char pos)
{
	p->vec_x = 1.0f;
	p->vec_y = 0;
	p->dir = pos;
}

static void	vec_north(t_p *p, char pos)
{
	p->vec_x = 0;
	p->vec_y = -1.0f;
	p->dir = pos;
}

static void	vec_south(t_p *p, char pos)
{
	p->vec_x = 0;
	p->vec_y = 1.0f;
	p->dir = pos;
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
		vec_north(p, map[y][x]);
	else if (map[y][x] == 'S')
		vec_south(p, map[y][x]);
	else if (map[y][x] == 'E')
		vec_east(p, map[y][x]);
	else if (map[y][x] == 'W')
		vec_west(p, map[y][x]);
	p->x = x;
	p->y = y;
}
