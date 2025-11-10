/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asbouani <asbouani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:08:57 by asbouani          #+#    #+#             */
/*   Updated: 2025/11/10 18:16:28 by asbouani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	key_press(int keycode, t_game *game)
{
	t_player	*player;

	player = &(game->player);
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

void	check_and_move(t_player *p, char **map, double new_x, double new_y)
{
	int	row_map;
	int	col_map;
	int	new_col;
	int	new_row;

	row_map = (int)(p->y / SIZE);
	col_map = (int)(p->x / SIZE);
	new_row = (int)(new_y / SIZE);
	new_col = (int)(new_x / SIZE);
	if (map[row_map][new_col] != '1')
		p->x = new_x;
	if (map[new_row][col_map] != '1')
		p->y = new_y;
}

void	handle_movement(t_game *game, char **map, double speed)
{
	double		new_x;
	double		new_y;
	t_player	*p;

	if (!game)
		return ;
	p = &(game->player);
	new_x = p->x;
	new_y = p->y;
	if (p->key_up)
		check_and_move(p, map, new_x + p->dx * speed, new_y + p->dy * speed);
	if (p->key_down)
		check_and_move(p, map, new_x - p->dx * speed, new_y - p->dy * speed);
	if (p->key_left)
		check_and_move(p, map, new_x + p->dy * speed, new_y - p->dx * speed);
	if (p->key_right)
		check_and_move(p, map, new_x - p->dy * speed, new_y + p->dx * speed);
}

void	rotate_player(t_player *p, double rot_speed)
{
	double	old_dx;
	double	old_plane_x;
	double	cos_r;
	double	sin_r;

	cos_r = cos(rot_speed);
	sin_r = sin(rot_speed);
	old_dx = p->dx;
	old_plane_x = p->plane_x;
	p->dx = p->dx * cos_r - p->dy * sin_r;
	p->dy = old_dx * sin_r + p->dy * cos_r;
	p->plane_x = p->plane_x * cos_r - p->plane_y * sin_r;
	p->plane_y = old_plane_x * sin_r + p->plane_y * cos_r;
}

void	move_player(t_game *game, char **map)
{
	t_player	*p;
	double		speed;

	if (!game)
		return ;
	speed = 10;
	p = &(game->player);
	if (p->key_rot_left)
		rotate_player(p, p->rot_step);
	if (p->key_rot_right)
		rotate_player(p, -p->rot_step);
	handle_movement(game, map, speed);
}
