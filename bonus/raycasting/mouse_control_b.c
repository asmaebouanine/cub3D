/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_control_b.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asbouani <asbouani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:45:17 by asbouani          #+#    #+#             */
/*   Updated: 2025/11/15 15:03:16 by asbouani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

int	mouse_control(int x, int y, t_game *game)
{
	static int	last_x = -1;
	int			diff_x;
	double		speed;
	double		rot_speed;

	(void)y;
	speed = 0.005;
	if (last_x == -1)
	{
		last_x = x;
		return (0);
	}
	diff_x = x - last_x;
	last_x = x;
	rot_speed = diff_x * speed;
	rotate_player(&game->player, rot_speed);
	return (0);
}

void	draw_player_icon(t_game *game, int px, int py)
{
	int	x;
	int	y;
	int	i;
	int	radius;

	radius = 4;
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
				put_pixel(px + x, py + y, 0xFF99CC, game);
			x++;
		}
		y++;
	}
	i = 0;
	while (i < 20)
	{
		put_pixel(px + game->player.dx * i,
			py + game->player.dy * i, 0xFF99CC, game);
		i++;
	}
}

void	draw_player(t_game *game)
{
	int	px;
	int	py;

	px = (VIEW_SIZE / 2) * TILE_SIZE + TILE_SIZE / 2;
	py = (VIEW_SIZE / 2) * TILE_SIZE + TILE_SIZE / 2;
	draw_player_icon(game, px, py);
}
