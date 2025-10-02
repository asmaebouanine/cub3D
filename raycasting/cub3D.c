/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asbouani <asbouani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:58:20 by asbouani          #+#    #+#             */
/*   Updated: 2025/10/02 16:15:42 by asbouani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"
//draw one pixel at the position (x, y)
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
    t_player    *player;
    return (map);
}

void init_map(t_map *map)
{
    map->line = get_map();
    map->width = 15;
    map->height = 12;
}


void    put_pixel(int x, int y, int color, t_game *game)
{
    int index;
    
    if (x >= game->win_width || y >= game->win_height || x < 0 || y < 0)
        return ;
    index = y * game->size_line + x * game->bits_per_pixel / 8;
    game->date[index] = color & 0xFF;
    game->date[index+1] = (color >> 8) & 0xFF;
    game->date[index+2] = (color >> 16) & 0xFF; 
}
//draw a square based in the function put_pixel0
void    fill_square(int x, int y, int color, t_game *game)
{
    int i;
    int j;
    
    i = 0;
    while (i < SIZE)
    {
        j = 0;
        while (j < SIZE)
        {
            put_pixel(x, y, color, game);
            j++;
        }
        i++;
    }
}
//initialize the graphics system and create the window
void    init_game(t_game *game)
{
    game->map = malloc(sizeof(t_map));
    init_map(game->map);
    game->win_height = game->map->height * SIZE;
    game->win_width = game->map->width * SIZE;
    game->mlx = mlx_init();//connect the program with the graphics system
    game->win = mlx_new_window(game->mlx, game->win_width, game->win_height, "cub3D"); // create a window and show it in the screen
    game->img = mlx_new_image(game->mlx, game->win_width, game->win_height); // draw a image in the buffer
    game->date = mlx_get_data_addr(game->img, &game->bits_per_pixel, &game->size_line, &game->endian); //pointer to the butter(can u change pixel)
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);// copy that buffer into the window to see it
}
void    draw_map(t_game *game)
{
    char **map = game->map->line;
    int height = game->map->height;
    int width = game->map->width;
    int y = 0;
    int x;
    while (map[y])
    {
        x = 0;
        while (map[y][x])
        {
            if (map[y][x] == '1')
                fill_square(y * (game->win_height/height), x *(game->win_width/width) , 0xFF0000, game);
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

void    draw_player(t_game *game)
{
    t_player *p = &game->player;
    int px = (int)(p->x - p->size / 2);
    int py = (int)(p->x - p->size / 2);
    fill_square(px, py, 0x00FF00, game);
}
void draw_(int x, int y0, int y1, int color, t_game *game) 
{
    if (x < 0 || x >= game->win_width)
        return;

    if (y0 < 0)
        y0 = 0;

    if (y1 >= game->win_height)
        y1 = game->win_height - 1;

    for (int y = y0; y <= y1; ++y)
        put_pixel(x, y, color, game);
}

double cast_single_ray(t_game *game, t_player *p,
                       double rayDirX, double rayDirY,
                       int *side_out)
{
    double posX = p->x / (double)SIZE;
    double posY = p->y / (double)SIZE;

    int mapX = (int)posX;
    int mapY = (int)posY;

    double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1.0 / rayDirX);
    double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1.0 / rayDirY);

    int stepX, stepY;
    double sideDistX, sideDistY;

    // Step and initial sideDist for X
    if (rayDirX < 0) {
        stepX = -1;
        sideDistX = (posX - mapX) * deltaDistX;
    } else {
        stepX = 1;
        sideDistX = (mapX + 1.0 - posX) * deltaDistX;
    }

    // Step and initial sideDist for Y
    if (rayDirY < 0) {
        stepY = -1;
        sideDistY = (posY - mapY) * deltaDistY;
    } else {
        stepY = 1;
        sideDistY = (mapY + 1.0 - posY) * deltaDistY;
    }

    int hit = 0;
    int side = 0;

    // Digital Differential Analyzer (DDA) loop
    while (!hit) {
        if (sideDistX < sideDistY) {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;  // hit a vertical wall
        } else {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;  // hit a horizontal wall
        }

        // bounds check (to avoid going outside the map)
        if (mapX < 0 || mapX >= game->map->width ||
            mapY < 0 || mapY >= game->map->height) {
            hit = 1;
            break;
        }

        // check if we hit a wall
        if (game->map->line[mapY][mapX] == '1')
            hit = 1;
    }

    // perpendicular distance correction
    double perpDist;
    if (side == 0)
        perpDist = sideDistX - deltaDistX;
    else
        perpDist = sideDistY - deltaDistY;

    if (perpDist < 1e-6) perpDist = 1e-6;

    if (side_out) *side_out = side;
    return perpDist;
}

// int draw_loop(t_game *game)
// {
//     t_player *player;

//     player = &game->player;
//     move_player(player);
//     clear_image(game);
//     draw_square(player->x, player->y, 0x00FF00, game);
//     draw_map(game);
//     mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
//     return 0;
// }

// int main(int argc, char **argv)
// {
//     (void)argc;
//     (void)argv;
//     t_game      game;
//     // t_config    *config;

//     // config = parsser(argc, argv);
//     // if(!config)
//     //     return(0);
//     init_game(&game);
//     init_player(&game.player);
    
//     // game.config = config;
//     mlx_hook(game.win, 2, 1L<<0, key_press, &game.player);
//     mlx_hook(game.win, 3, 1L<<1, key_release, &game.player);
//     mlx_loop_hook(game.mlx, draw_loop, &game);
//     mlx_loop(game.mlx);       
// }


int draw_loop(t_game *game) {
    clear_image(game);

    /* 1) update player based on input */
    move_player(&game->player, game->map->line);

    /* 2) raycast: one ray per screen column */
    t_player *p = &game->player;
    for (int x = 0; x < game->win_width; ++x) {
        double cameraX = 2.0 * x / (double)game->win_width - 1.0;
        double rayDirX = p->dx + p->plane_x * cameraX;
        double rayDirY = p->dy + p->plane_y * cameraX;

        int side;
        double dist = cast_single_ray(game, p, rayDirX, rayDirY, &side);

        int lineHeight = (int)(game->win_height / dist);
        int drawStart = -lineHeight / 2 + game->win_height / 2;
        int drawEnd = lineHeight / 2 + game->win_height / 2;
        if (drawStart < 0) drawStart = 0;
        if (drawEnd >= game->win_height) drawEnd = game->win_height - 1;

        int color = 0xFF0000;
        if (side == 1) color = (color >> 1) & 0x7F7F7F; // darker shade for sides

        draw_(x, drawStart, drawEnd, color, game);
    }

    /* optional debugging draws */
    // draw_map(game);
    // draw_player(game);
    // draw_ray(game, &game->player, 0x00FFFF);

    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);

    return 0;
}


int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    t_game game;

    // =========================
    // 1. Parse configuration
    // =========================
    /*
    t_config *config = parser(argc, argv);
    if (!config)
        return (0);

    game.map = config->map;
    game.player = *(config->player);
    game.config = config;
    */

    // =========================
    // 2. Initialize game state
    // =========================
    init_game(&game);
    init_player(&game);

    // =========================
    // 3. Set up input hooks
    // =========================
    mlx_hook(game.win, 2, 1L << 0, key_press, &game.player);
    mlx_hook(game.win, 3, 1L << 1, key_release, &game.player);

    // =========================
    // 4. Set main render loop
    // =========================
    mlx_loop_hook(game.mlx, draw_loop, &game);

    // =========================
    // 5. Start main loop
    // =========================
    mlx_loop(game.mlx);

    return (0);
}






// int main(int argc, char **argv)
// {
//     t_config    *config;

//     config = parsser(argc, argv);
//     if(!config)
//         return(0);
//     printf("%s\n", config->texture[0]);
//     printf("%s\n", config->texture[1]);
//     printf("%s\n", config->texture[2]);
//     printf("%s\n", config->texture[3]);
//     printf("%d\n", config->color->c_color);
//     printf("%d\n", config->color->f_color);
//     printf("%d\n", config->player->x);
//     printf("%d\n", config->player->y);
//     printf("%c\n", config->player->direction); 
// }
