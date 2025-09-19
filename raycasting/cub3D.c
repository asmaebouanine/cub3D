/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asbouani <asbouani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:58:20 by asbouani          #+#    #+#             */
/*   Updated: 2025/09/19 14:28:24 by asbouani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"
//draw one pixel at the position (x, y)
void    put_pixel(int x, int y, int color, t_game *game)
{
    int index;
    
    if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
        return ;
    index = y * game->size_line + x * game->bits_per_pixel / 8;
    game->date[index] = color & 0xFF;
    game->date[index+1] = (color >> 8) & 0xFF;
    game->date[index+2] = (color >> 16) & 0xFF; 
}
//draw a square based in the function put_pixel0
void    draw_square(int x, int y, int color, t_game *game)
{
    int i;
    
    i = 0;
    while (i < SIZE)
    {
        put_pixel(x+i, y, color, game);
        put_pixel(x, y+i, color, game);
        put_pixel(x+SIZE, y+i, color, game);
        put_pixel(x+i, y+SIZE, color, game);
        i++;
    }
}
char    **get_map(void)
{
    char **map;
    map = malloc(sizeof(char *) * 9);
    if (!map)
        return NULL;
    map[0] = "111111111111";
    map[1] = "100000000001";
    map[2] = "100000000001";
    map[3] = "100000000001";
    map[4] = "100000000001";
    map[5] = "100000000001";
    map[6] = "100000000001";
    map[7] = "111111111111";
    map[8] = NULL;
    return (map);
}
//initialize the graphics system and create the window
void    init_game(t_game *game)
{
    game->map = get_map();
    game->player= (game->player);
    game->mlx = mlx_init();//connect the program with the graphics system
    game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D"); // create a window and show it in the screen
    game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT); // draw a image in the buffer
    game->date = mlx_get_data_addr(game->img, &game->bits_per_pixel, &game->size_line, &game->endian); //pointer to the butter(can u change pixel)
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);// copy that buffer into the window to see it
}
void    draw_map(t_game *game)
{
    char **map = game->map;
    int color = 0x0000FF;
    int y;
    int x;
    
    y = 0;
    while (map[y])
    {
        x = 0;
        while (map[y][x])
        {
            if (map[y][x] == '1')
                draw_square(x * 80, y * 80, color, game);
            x++;
        }
        y++;
    } 
}
//clear the screen (reset the image to black)
void    clear_image(t_game *game)
{
    int x;
    int y;

    x = 0;
    while (x < WIDTH)
    {
        y = 0;
        while (y < HEIGHT)
        {
            put_pixel(x, y, 0, game);
            y++;
        }
        x++;
    }
}
int draw_loop(t_game *game)
{
    t_player *player;

    player = &game->player;
    move_player(player);
    clear_image(game);
    draw_square(player->x, player->y, 0x00FF00, game);
    draw_map(game);
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    return 0;
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    t_game      game;
    // t_config    *config;

    // config = parsser(argc, argv);
    // if(!config)
    //     return(0);
    init_game(&game);
    init_player(&game.player);
    
    // game.config = config;
    mlx_hook(game.win, 2, 1L<<0, key_press, &game.player);
    mlx_hook(game.win, 3, 1L<<1, key_release, &game.player);
    mlx_loop_hook(game.mlx, draw_loop, &game);
    mlx_loop(game.mlx);       
}