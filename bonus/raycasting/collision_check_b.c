/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_check_b.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asbouani <asbouani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 21:03:59 by asbouani          #+#    #+#             */
/*   Updated: 2025/11/12 21:15:33 by asbouani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	first_check(t_game *game, char **map, double new_x, t_player *p)
{
	int	row_map;
	int	new_col;
	int	i;

	if (!p)
		return ;
	row_map = (int)(p->y / SIZE);
	new_col = (int)(new_x / SIZE);
	if (row_map >= 0 && row_map < game->map->height
		&& new_col >= 0 && new_col < game->map->width)
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

void	second_check(t_game *game, char **map, double new_y, t_player *p)
{
	int	col_map;
	int	new_row;
	int	i;

	col_map = (int)(p->x / SIZE);
	new_row = (int)(new_y / SIZE);
	if (!p)
		return ;
	if (new_row >= 0 && new_row < game->map->height
		&& col_map >= 0 && col_map < game->map->width)
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
	t_player	*p;

	if (!game || !map || !game->map)
		return ;
	p = &(game->player);
	first_check(game, map, new_x, p);
	second_check(game, map, new_y, p);
}
