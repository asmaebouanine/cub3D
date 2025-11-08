/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 22:05:53 by asbouani          #+#    #+#             */
/*   Updated: 2025/11/06 04:28:50 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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
	{
		p->dx = -1;
		p->dy = 0;
		p->plane_x = 0;
		p->plane_y = -0.66;
	}
}

void	init_position(t_game *game, char **map)
{
	int	y;
	int	x;
	t_player *p;
	
	if(!game)
		return;
	y = 0;
	p = &(game->player);
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

int find_cooresp_dr(t_game *game, int map_y, int map_x)
{
	int i;
	
	i = 0;
	if(!game->doors)
		return(0);
	while(game->doors[i])
	{
		if((game->doors[i]->door_x == map_x )&& (game->doors[i]->door_y == map_y))
			return(i);
		i++;
	}
	return(i);
}
void door_handling(t_game *game)
{
	int i;
	int map_y;
	int map_x;
	double	check_x;
	double	check_y;
	double player_map_x;
	double player_map_y;
	
	player_map_x = (double)game->player.x / (double)SIZE;
	player_map_y = (double)game->player.y / (double)SIZE;
	check_x = player_map_x + game->player.dx * 1.5;
	check_y = player_map_y + game->player.dy * 1.5;
	map_x = (int)check_x;
	map_y = (int)check_y;
	if (map_y < 0 || map_y >= game->map->height
		|| map_x < 0 || map_x >= game->map->width)
		return;
	if(game->map->line[map_y][map_x] == 'D')
	{
		i = find_cooresp_dr(game, map_y, map_x);
		if(game->doors[i]->state == 'c')
			game->doors[i]->state = 'o';
		else 
			game->doors[i]->state = 'c';
	}
}
int	key_press(int keycode, t_game *game)
{
	t_player *player;
	
	player = &(game->player);
	if (keycode == LEFT_ARROW)
		player->key_rot_left = true;
	if (keycode == RIGHT_ARROW)
		player->key_rot_right = true;
	if(keycode == 111)
		door_handling(game);
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

int	key_release(int keycode, t_game *game)
{
	t_player *player;
	
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

