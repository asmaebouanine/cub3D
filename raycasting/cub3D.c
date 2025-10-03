/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asbouani <asbouani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:58:20 by asbouani          #+#    #+#             */
/*   Updated: 2025/10/03 17:13:36 by asbouani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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

void    init_game(t_game *game)
{
    game->win_width = game->map->width * SIZE;
    game->win_height = game->map->height * SIZE;
    game->mlx = mlx_init();//connect the program with the graphics system
    game->win = mlx_new_window(game->mlx, game->win_width, game->win_height, "cub3D"); // create a window and show it in the screen
    game->img = mlx_new_image(game->mlx, game->win_width, game->win_height); // draw a image in the buffer
    game->date = mlx_get_data_addr(game->img, &game->bits_per_pixel, &game->size_line, &game->endian); //pointer to the butter(can u change pixel)
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);// copy that buffer into the window to see it
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



// --- Calculate delta distances ---
static void init_delta(double rayDirX, double rayDirY,
                       double *deltaDistX, double *deltaDistY)
{
    *deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1.0 / rayDirX);
    *deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1.0 / rayDirY);
}

// --- Initialize steps and initial side distances ---
static void init_step(double posX, double posY,
                      double rayDirX, double rayDirY,
                      double deltaDistX, double deltaDistY,
                      int *stepX, int *stepY,
                      double *sideDistX, double *sideDistY,
                      int mapX, int mapY)
{
    if (rayDirX < 0)
    {
        *stepX = -1;
        *sideDistX = (posX - mapX) * deltaDistX;
    }
    else
    {
        *stepX = 1;
        *sideDistX = (mapX + 1.0 - posX) * deltaDistX;
    }
    if (rayDirY < 0)
    {
        *stepY = -1;
        *sideDistY = (posY - mapY) * deltaDistY;
    }
    else
    {
        *stepY = 1;
        *sideDistY = (mapY + 1.0 - posY) * deltaDistY;
    }
}

// --- Perform the DDA loop ---
static int perform_dda(t_game *game, int *mapX, int *mapY,
                       double *sideDistX, double *sideDistY,
                       double deltaDistX, double deltaDistY,
                       int stepX, int stepY, int *side)
{
    int hit = 0;

    while (!hit)
    {
        if (*sideDistX < *sideDistY)
        {
            *sideDistX += deltaDistX;
            *mapX += stepX;
            *side = 0;
        }
        else
        {
            *sideDistY += deltaDistY;
            *mapY += stepY;
            *side = 1;
        }
        if (*mapX < 0 || *mapX >= game->map->width ||
            *mapY < 0 || *mapY >= game->map->height)
            return (1);
        if (game->map->line[*mapY][*mapX] == '1')
            hit = 1;
    }
    return (hit);
}

// --- Main raycasting function ---
double cast_single_ray(t_game *game, t_player *p,
                       double rayDirX, double rayDirY,
                       int *side_out)
{
    double posX = p->x / (double)SIZE;
    double posY = p->y / (double)SIZE;
    int mapX = (int)posX;
    int mapY = (int)posY;

    double deltaDistX, deltaDistY;
    init_delta(rayDirX, rayDirY, &deltaDistX, &deltaDistY);

    int stepX, stepY;
    double sideDistX, sideDistY;
    init_step(posX, posY, rayDirX, rayDirY,
              deltaDistX, deltaDistY,
              &stepX, &stepY, &sideDistX, &sideDistY,
              mapX, mapY);

    int side = 0;
    perform_dda(game, &mapX, &mapY, &sideDistX, &sideDistY,
                deltaDistX, deltaDistY, stepX, stepY, &side);

    double perpDist = (side == 0)
        ? sideDistX - deltaDistX
        : sideDistY - deltaDistY;

    if (perpDist < 1e-6)
        perpDist = 1e-6;
    if (side_out)
        *side_out = side;
    return (perpDist);
}


// --- Compute ray direction from camera plane ---
static void compute_ray(t_player *p, int x, int win_width,
                        double *rayDirX, double *rayDirY)
{
    double cameraX = 2.0 * x / (double)win_width - 1.0;
    *rayDirX = p->dx + p->plane_x * cameraX;
    *rayDirY = p->dy + p->plane_y * cameraX;
}

// --- Compute line params and choose wall color ---
static void prepare_line(int win_height, double dist, int side,
                         int *lineHeight, int *drawStart, int *drawEnd, int *color)
{
    *lineHeight = (int)(win_height / dist);
    *drawStart = -(*lineHeight) / 2 + win_height / 2;
    *drawEnd   = (*lineHeight) / 2 + win_height / 2;

    if (*drawStart < 0) *drawStart = 0;
    if (*drawEnd >= win_height) *drawEnd = win_height - 1;

    *color = 0xFF0000; // base red
    if (side == 1)
        *color = (*color >> 1) & 0x7F7F7F; // darker for sides
}


// New function: render one vertical column (x) of the screen
void render_column(t_game *game, t_player *p, int x)
{
    double rayDirX, rayDirY;
    compute_ray(p, x, game->win_width, &rayDirX, &rayDirY);

    int side;
    double dist = cast_single_ray(game, p, rayDirX, rayDirY, &side);

    int lineHeight, drawStart, drawEnd, color;
    prepare_line(game->win_height, dist, side,
                 &lineHeight, &drawStart, &drawEnd, &color);

    draw_(x, drawStart, drawEnd, color, game);
}

int draw_loop(t_game *game)
{
    clear_image(game);

    /* 1) update player based on input */
    move_player(&game->player, game->map->line);

    /* 2) raycast: one ray per screen column */
    t_player *p = &game->player;
    for (int x = 0; x < game->win_width; ++x)
        render_column(game, p, x);

    /* 3) put image to window */
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);

    return 0;
}
int close_window(void *param)
{
    (void)param;
    exit (1);
}

int main(int argc, char **argv)
{
   t_game game;

    t_config *config = parsser(argc, argv);
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