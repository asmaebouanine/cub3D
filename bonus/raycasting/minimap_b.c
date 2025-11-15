/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asbouani <asbouani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 20:49:13 by asbouani          #+#    #+#             */
/*   Updated: 2025/11/15 14:32:12 by asbouani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

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

void	draw_tile(t_game *game, int row, int col, double *offset)
{
	int	color;
	int	p_row;
	int	p_col;

	p_row = (int)(game->player.y / SIZE);
	p_col = (int)(game->player.x / SIZE);
	if (game->map->line[row][col] == '1')
		color = 0x620035;
	else if (game->map->line[row][col] == 'D')
		color = 0xFF69B4;
	else
		color = 0x000000;
	draw_one_tile(
		game,
		(int)((col - (p_col - VIEW_SIZE / 2)) * TILE_SIZE - offset[0]),
		(int)((row - (p_row - VIEW_SIZE / 2)) * TILE_SIZE - offset[1]),
		color);
}

void	draw_rows(t_game *game, int p_row, int p_col, double *offset)
{
	int	row;
	int	col;

	row = p_row - VIEW_SIZE / 2;
	while (row <= p_row + VIEW_SIZE / 2)
	{
		if (row >= 0 && row < game->map->height)
		{
			col = p_col - VIEW_SIZE / 2;
			while (col <= p_col + VIEW_SIZE / 2)
			{
				if (col >= 0 && col < (int)ft_strlen(game->map->line[row]))
					draw_tile(game, row, col, offset);
				col++;
			}
		}
		row++;
	}
}

void	minimap(t_game *game)
{
	int		p_row;
	int		p_col;
	double	offset[2];

	p_row = (int)(game->player.y / SIZE);
	p_col = (int)(game->player.x / SIZE);
	offset[0] = (game->player.x / SIZE - p_col) * TILE_SIZE - TILE_SIZE / 2;
	offset[1] = (game->player.y / SIZE - p_row) * TILE_SIZE - TILE_SIZE / 2;
	draw_rows(game, p_row, p_col, offset);
	draw_player(game);
}
