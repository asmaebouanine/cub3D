/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asbouani <asbouani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 22:05:53 by asbouani          #+#    #+#             */
/*   Updated: 2025/11/09 14:20:51 by asbouani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	set_west(t_player *p)
{
	p->dx = -1;
	p->dy = 0;
	p->plane_x = 0;
	p->plane_y = -0.6;
}

void	init_direction(t_player *p, char dir)
{
	if (dir == 'N')
	{
		p->dx = 0;
		p->dy = -1;
		p->plane_x = 0.66;
		p->plane_y = 0;
	}
	if (dir == 'S')
	{
		p->dx = 0;
		p->dy = 1;
		p->plane_x = -0.66;
		p->plane_y = 0;
	}
	if (dir == 'E')
	{
		p->dx = 1;
		p->dy = 0;
		p->plane_x = 0;
		p->plane_y = 0.66;
	}
	if (dir == 'W')
		set_west(p);
}

void	init_position(t_game *game, char **map)
{
	t_player	*p;
	int			y;
	int			x;
	
	if (!game)
		return ;
	p = &(game->player);
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' ||
				map[y][x] == 'E' || map[y][x] == 'W')
			{
				p->x = x * SIZE + SIZE / 2;
				p->y = y * SIZE + SIZE / 2;
				init_direction (p, map[y][x]);
				return ;
			}
			x++;
		}
		y++;
	}
}

void	init_player(t_game *g)
{
	init_position(g, g->map->line);
	g->player.key_rot_left = false;
	g->player.key_rot_right = false;
	g->player.key_up = false;
	g->player.key_down = false;
	g->player.key_left = false;
	g->player.key_right = false;
	g->player.rot_step = 0.05;
}

int	key_release(int keycode, t_game *game)
{
	t_player	*player;
	
	player = &(game->player);
	if (keycode == LEFT_ARROW)
		player->key_rot_left = false;
	if (keycode == RIGHT_ARROW)
		player->key_rot_right = false;
	if (keycode == W)
		player->key_up = false;
	if (keycode == S)
		player->key_down = false;
	if (keycode == A)
		player->key_left = false;
	if (keycode == D)
		player->key_right = false;
	return (0);
}
