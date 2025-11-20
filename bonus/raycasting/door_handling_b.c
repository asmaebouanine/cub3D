/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_handling_b.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:31:44 by asbouani          #+#    #+#             */
/*   Updated: 2025/11/17 22:19:41 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

int	find_cooresp_dr(t_game *game, int map_y, int map_x)
{
	int	i;

	i = 0;
	if (!game->doors)
		return (0);
	while (game->doors[i])
	{
		if (game->doors[i]->door_x == map_x
			&& game->doors[i]->door_y == map_y)
			return (i);
		i++;
	}
	return (i);
}

void	coord_cal(t_game *game, t_coord *coor)
{
	(*coor).player_map_x = (double)game->player.x / (double)SIZE;
	(*coor).player_map_y = (double)game->player.y / (double)SIZE;
	(*coor).check_x = (*coor).player_map_x + game->player.dx * 0.5;
	(*coor).check_y = (*coor).player_map_y + game->player.dy * 0.5;
}

void	door_handling(t_game *game)
{
	int		i;
	int		map_y;
	int		map_x;
	t_coord	coor;

	coord_cal(game, &coor);
	map_x = (int)coor.check_x;
	map_y = (int)coor.check_y;
	if (map_y < 0 || map_y >= game->map->height
		|| map_x < 0 || map_x >= game->map->width)
		return ;
	if (game->map->line[map_y][map_x] == 'D')
	{
		i = find_cooresp_dr(game, map_y, map_x);
		if (game->doors[i]->state == 'c')
			game->doors[i]->state = 'o';
		else
		{
			if ((int)coor.player_map_x != map_x
				|| (int)coor.player_map_y != map_y)
				game->doors[i]->state = 'c';
		}
	}
}
