/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asbouani <asbouani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:58:20 by asbouani          #+#    #+#             */
/*   Updated: 2025/10/10 15:54:08 by asbouani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	init_game(t_game *game) // intialize mlx window and image
{
	game->win_width = game->map->width * SIZE;
	game->win_height = game->map->height * SIZE;
	game->mlx = mlx_init();//connect the program with the graphics system
	game->win = mlx_new_window(game->mlx, game->win_width, game->win_height, "cub3D"); // create a window and show it in the screen
	game->img = mlx_new_image(game->mlx, game->win_width, game->win_height); // draw a image in the buffer
	game->date = mlx_get_data_addr(game->img, &game->bits_per_pixel, &game->size_line, &game->endian); //pointer to the image in the buffer
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);// displays the image
}

void	clear_image(t_game *game) //clear the screen (draw black pixels in the screen)
{
	int	x;
	int	y;

	x = 0;
	while (x < game->win_width)
	{
		y = 0;
		while (y < game->win_height)
		{
			put_pixel(x, y, 0, game);
			y++;
		}
		x++;
	}
}

int	draw_loop(t_game *game)
{
	int	x;

	x = 0;
	clear_image(game);
	move_player(&game->player, game->map->line);
	while (x < game->win_width)
	{
		render_column(game, x);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return 0;
}

int	close_window(void *param)
{
	(void)param;
	exit (1);
}

int	main(int argc, char **argv)
{
	t_config    *config;
	t_game      game;
	
	config = parsser(argc, argv);
	if (!config)
		return (0);
	game.config = config;
	game.map = config->map;
	game.player = *(config->player);
	init_game(&game);
	init_player(&game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game.player);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game.player);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
