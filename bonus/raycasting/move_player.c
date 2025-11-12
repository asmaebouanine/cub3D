/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:08:57 by asbouani          #+#    #+#             */
/*   Updated: 2025/11/11 20:22:42 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void first_check(t_game *game, char **map,double new_x, t_player *p)
{
	int	row_map;
	int new_col;
	int i;

	if(!p)
		return;
	row_map = (int)(p->y / SIZE);
	new_col = (int)(new_x / SIZE);
	if (row_map >= 0 && row_map < game->map->height &&
		new_col >= 0 && new_col < game->map->width)
	{
		if (map[row_map][new_col] != '1')
		{
			if (map[row_map][new_col] == 'D')
			{
				i = find_cooresp_dr(game, row_map, new_col);
				if (i >= 0 && game->doors[i]->state != 'c')
					p->x = new_x;
			}
			else
				p->x = new_x;
		}
	}
}
void second_check(t_game *game, char **map, double new_y, t_player *p)
{
	int	col_map;
	int	new_row;
	int i;

	col_map = (int)(p->x / SIZE);
	new_row = (int)(new_y / SIZE);
	if(!p)
		return;
	if (new_row >= 0 && new_row < game->map->height &&
		col_map >= 0 && col_map < game->map->width)
	{
		if (map[new_row][col_map] != '1')
		{
			if (map[new_row][col_map] == 'D')
			{
				i = find_cooresp_dr(game, new_row, col_map);
				if (i >= 0 && game->doors[i]->state != 'c')
					p->y = new_y;
			}
			else
				p->y = new_y;
		}
	}
}	
void	check_and_move(t_game *game, char **map, double new_x, double new_y)
{
	t_player *p;

	if (!game || !map || !game->map )
		return;
	p = &(game->player);
	first_check(game, map, new_x, p);
	second_check(game, map, new_y,p);
}

void	handle_movement(t_game *game, char **map, double speed)
{
	double	new_x;
	double	new_y;
	t_player *p;
	
	if(!game)
		return;
	p = &(game->player);
	new_x = p->x;
	new_y = p->y;
	if (p->key_up)
		check_and_move(game, map, new_x + p->dx * speed, new_y + p->dy * speed);
	if (p->key_down)
		check_and_move(game, map, new_x - p->dx * speed, new_y - p->dy * speed);
	if (p->key_left)
		check_and_move(game, map, new_x + p->dy * speed, new_y - p->dx * speed);
	if (p->key_right)
		check_and_move(game, map, new_x - p->dy * speed, new_y + p->dx * speed);
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
	// Rotate direction vector
	p->dx = p->dx * cos_r - p->dy * sin_r;
	p->dy = old_dx * sin_r + p->dy * cos_r;
	// Rotate camera plane
	p->plane_x = p->plane_x * cos_r - p->plane_y * sin_r;
	p->plane_y = old_plane_x * sin_r + p->plane_y * cos_r;
}

void	move_player(t_game *game, char **map)
{
	double	speed;
	t_player *p;

	if(!game)
		return;
	speed = 10;
	p =&(game->player);
	if (p->key_rot_left)
		rotate_player(p, p->rot_step);
	if (p->key_rot_right)
		rotate_player(p, -p->rot_step);
	handle_movement(game, map, speed);
}