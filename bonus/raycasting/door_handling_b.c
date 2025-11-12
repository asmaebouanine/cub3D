/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_handling_b.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asbouani <asbouani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:31:44 by asbouani          #+#    #+#             */
/*   Updated: 2025/11/12 18:51:41 by asbouani         ###   ########.fr       */
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
void	door_handling(t_game *game)
{
	int		i;
	int		map_y;
	int		map_x;
	double	check_x;
	double	check_y;
	double	player_map_x;
	double	player_map_y;

	player_map_x = (double)game->player.x / (double)SIZE;
	player_map_y = (double)game->player.y / (double)SIZE;
	check_x = player_map_x + game->player.dx * 0.5;
	check_y = player_map_y + game->player.dy * 0.5;
	map_x = (int)check_x;
	map_y = (int)check_y;
	if (map_y < 0 || map_y >= game->map->height
		|| map_x < 0 || map_x >= game->map->width)
	{
		return ;
	}
	if (game->map->line[map_y][map_x] == 'D')
	{
		i = find_cooresp_dr(game, map_y, map_x);
		if (game->doors[i]->state == 'c')
			game->doors[i]->state = 'o';
		else
		{
			game->doors[i]->state = 'c';
		}
	}
}
