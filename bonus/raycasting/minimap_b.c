/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asbouani <asbouani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:31:05 by asbouani          #+#    #+#             */
/*   Updated: 2025/11/10 18:52:12 by asbouani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../cub3D_bonus.h"

void	draw_player(t_game *game)
{
	int	player_draw_x;
	int	player_draw_y;
	int	radius;
	int	x;
	int	y;
    int i;
    
    i = 0;
	player_draw_x = (VIEW_SIZE / 2) * TILE_SIZE + TILE_SIZE / 2;
	player_draw_y = (VIEW_SIZE / 2) * TILE_SIZE + TILE_SIZE / 2;
	radius = 4;
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
				put_pixel(player_draw_x + x, player_draw_y + y, 0x00FF00, game);
			x++;
		}
		y++;
	}
	while (i < 20)
	{
		put_pixel(player_draw_x + game->player.dx * i,
			player_draw_y + game->player.dy * i, 0x00FF00, game);
		i++;
	}
}

void	draw_one_tile(t_game *game, int screen_x, int screen_y, int color)
{
	int	x_offset;
	int	y_offset;

	y_offset = 0;
	while (y_offset < TILE_SIZE)
	{
		x_offset = 0;
		while (x_offset < TILE_SIZE)
		{
			put_pixel(screen_x + x_offset, screen_y + y_offset, color, game);
			x_offset++;
		}
		y_offset++;
	}
}

void	minimap(t_game *game)
{
	int	row;
	int	col;
	int	color;
	int	p_row;
	int	p_col;

	p_row = (int)(game->player.y / SIZE);
	p_col = (int)(game->player.x / SIZE);
	row = p_row - VIEW_SIZE / 2;
	while (row <= p_row + VIEW_SIZE / 2)
	{
		if (row >= 0 && row < game->map->height)
		{
			col = p_col - VIEW_SIZE / 2;
			while (col <= p_col + VIEW_SIZE / 2)
			{
				if (col >= 0 && col < (int)ft_strlen(game->map->line[row]))
				{
					if (game->map->line[row][col] == '1')
						color = 0xFF0000;
					else if (game->map->line[row][col] == 'D')
						color = 0x0000FF;
					else if (game->map->line[row][col] == '0')
						color = 0x000000;
					draw_one_tile(game, (col - (p_col - VIEW_SIZE / 2)) * TILE_SIZE, \
					(row - (p_row - VIEW_SIZE / 2)) * TILE_SIZE, color);
				}
				col++;
			}
		}
		row++;
	}
	draw_player(game);
}