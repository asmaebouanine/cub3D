/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asbouani <asbouani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 22:05:53 by asbouani          #+#    #+#             */
/*   Updated: 2025/10/07 12:10:27 by asbouani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void init_direction(t_player *p, char dir)
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
	{
		p->dx = -1;
		p->dy = 0;
		p->plane_x = 0;
		p->plane_y = -0.66;
	}
}

void init_position(t_player *p, char **map)
{
	int y;
	int x;
	
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
				init_direction(p, map[y][x]);
				return;
			}
			x++;
		}
		y++;
	}
}

void init_player(t_game *g)
{
	init_position(&g->player, g->map->line);
	g->player.key_up = false;
	g->player.key_down = false;
	g->player.key_left = false;
	g->player.key_right = false;
	g->player.key_rot_left = false;
	g->player.key_rot_right = false;
	g->player.rot_step = 0.05;
}

int key_press(int keycode, t_player *player)
{
	if (keycode == LEFT_ARROW)
		player->key_rot_left = true;
	if (keycode == RIGHT_ARROW)
		player->key_rot_right = true;
	if (keycode == W)
		player->key_up = true;
	if (keycode == S)
		player->key_down = true;
	if (keycode == A)
		player->key_left = true;
	if (keycode == D)
		player->key_right = true;
	if (keycode == ESC || keycode == X)
		exit (1);
	return (0);
}

int key_release(int keycode, t_player *player)
{
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
