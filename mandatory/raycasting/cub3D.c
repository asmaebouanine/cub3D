/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asbouani <asbouani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:58:20 by asbouani          #+#    #+#             */
/*   Updated: 2025/11/17 20:45:19 by asbouani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	init_game(t_game *game)
{
	game->win_width = 1280;
	game->win_height = 720;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->win_width, game->win_height,
			"cub3D");
	game->img = mlx_new_image(game->mlx, game->win_width, game->win_height);
	game->date = mlx_get_data_addr(game->img, &game->bits_per_pixel,
			&game->size_line, &game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

void	clear_image(t_game *game)
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

int	game_loop(t_game *game)
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
	return (0);
}

int	close_window(void *param)
{
	t_game	*game;
	int		i;

	game = (t_game *)param;
	i = 0;
	while (i < 4)
	{
		if (game->convas.textures[i].img)
			mlx_destroy_image(game->mlx, game->convas.textures[i].img);
		i++;
	}
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	gcmalloc(0, 0);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_game		game;
	t_config	*config;
	t_convas	*convas;

	config = parsser(argc, argv);
	if (!config)
		gcmalloc(0, 0);
	game.config = config;
	game.map = config->map;
	game.player = *(config->player);
	init_game(&game);
	convas = xmp_to_image(game.config->texture, game.mlx);
	if (!convas)
		gcmalloc(0, 0);
	game.convas = *convas;
	init_player(&game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game.player);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game.player);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	gcmalloc(0, 0);
	return (0);
}
