/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asbouani <asbouani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:58:20 by asbouani          #+#    #+#             */
/*   Updated: 2025/10/06 13:37:22 by asbouani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

// draw one pixel in the image buffer
void    put_pixel(int x, int y, int color, t_game *game)
{
    int index;
    
    if (x >= game->win_width || y >= game->win_height || x < 0 || y < 0)
        return ;
    index = y * game->size_line + x * game->bits_per_pixel / 8; // calculte the memory location for pixel
    game->date[index] = color & 0xFF;
    game->date[index+1] = (color >> 8) & 0xFF;
    game->date[index+2] = (color >> 16) & 0xFF; 
}
// intialize mlx window and image
void    init_game(t_game *game)
{
    game->win_width = game->map->width * SIZE;
    game->win_height = game->map->height * SIZE;
    game->mlx = mlx_init();//connect the program with the graphics system
    game->win = mlx_new_window(game->mlx, game->win_width, game->win_height, "cub3D"); // create a window and show it in the screen
    game->img = mlx_new_image(game->mlx, game->win_width, game->win_height); // draw a image in the buffer
    game->date = mlx_get_data_addr(game->img, &game->bits_per_pixel, &game->size_line, &game->endian); //pointer to the image in the buffer
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);// displays the image
}

//clear the screen (draw black pixels in the screen)
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
//draw a verical line (wall)
void draw_wall(int x, int y0, int y1, int color, t_game *game) 
{
    if (x < 0 || x >= game->win_width)
        return;
    if (y0 < 0)
        y0 = 0;
    if (y1 >= game->win_height)
        y1 = game->win_height - 1;
    while (y0 <= y1)
    {
        put_pixel(x, y0, color, game);
        y0++;
    }
}
//calcute fixed step distance for the ray to cross the nest line x y
void init_delta(t_ray *ray)
{
    if (ray->rayDirX == 0)
        ray->deltaDistX = 1e30;
    else
        ray->deltaDistX = fabs(1.0 / ray->rayDirX);

    if (ray->rayDirY == 0)
        ray->deltaDistY = 1e30;
    else
        ray->deltaDistY = fabs(1.0 / ray->rayDirY);
}
//prepares the ray to start moving in the correct direction 
//across the map grid and tells how far the first wall is along each axis.
void init_step(t_ray *ray, double posX, double posY)
{
    if (ray->rayDirX < 0)
    {
        ray->stepX = -1;
        ray->sideDistX = (posX - ray->mapX) * ray->deltaDistX;
    }
    else
    {
        ray->stepX = 1;
        ray->sideDistX = (ray->mapX + 1.0 - posX) * ray->deltaDistX;
    }

    if (ray->rayDirY < 0)
    {
        ray->stepY = -1;
        ray->sideDistY = (posY - ray->mapY) * ray->deltaDistY;
    }
    else
    {
        ray->stepY = 1;
        ray->sideDistY = (ray->mapY + 1.0 - posY) * ray->deltaDistY;
    }
}


int perform_dda(t_game *game, t_ray *ray)
{
    int hit;
    
    hit = 0;
    while (!hit)
    {
        if (ray->sideDistX < ray->sideDistY)
        {
            ray->sideDistX += ray->deltaDistX;
            ray->mapX += ray->stepX;
            ray->side = 0;
        }
        else
        {
            ray->sideDistY += ray->deltaDistY;
            ray->mapY += ray->stepY;
            ray->side = 1;
        }
        if (ray->mapX < 0 || ray->mapX >= game->map->width ||
            ray->mapY < 0 || ray->mapY >= game->map->height)
            return 1;
        if (game->map->line[ray->mapY][ray->mapX] == '1')
            hit = 1;
    }
    return hit;
}



double cast_single_ray(t_game *game, t_player *p,t_ray *ray)
{
    double posX = p->x / (double)SIZE;
    double posY = p->y / (double)SIZE;

    ray->mapX = (int)posX;
    ray->mapY = (int)posY;

    init_delta(ray);
    init_step(ray, posX, posY);
    perform_dda(game, ray);

    double perpDist = (ray->side == 0)
        ? ray->sideDistX - ray->deltaDistX
        : ray->sideDistY - ray->deltaDistY;

    if (perpDist < 1e-6)
        perpDist = 1e-6;

    return perpDist;
}


void compute_ray(t_player *p, int x, int win_width,
                 double *rayDirX, double *rayDirY)
{
    double cameraX = 2.0 * x / (double)win_width - 1.0;
    *rayDirX = p->dx + p->plane_x * cameraX;
    *rayDirY = p->dy + p->plane_y * cameraX;
}



void prepare_line(int win_height, double dist, int side,
                  int *lineHeight, int *drawStart, int *drawEnd, int *color)
{
    *lineHeight = (int)(win_height / dist);
    *drawStart = -(*lineHeight) / 2 + win_height / 2;
    *drawEnd   = (*lineHeight) / 2 + win_height / 2;

    if (*drawStart < 0) *drawStart = 0;
    if (*drawEnd >= win_height) *drawEnd = win_height - 1;

    *color = 0xFF0000; 
    if (side == 1)
        *color = (*color >> 1) & 0x7F7F7F;
}

void render_column(t_game *game, t_player *p, int x)
{
    t_ray ray;

    compute_ray(p, x, game->win_width, &ray.rayDirX, &ray.rayDirY);

    double dist = cast_single_ray(game, p,&ray);

    int lineHeight, drawStart, drawEnd, color;
    prepare_line(game->win_height, dist, ray.side,
                 &lineHeight, &drawStart, &drawEnd, &color);

    draw_wall(x, drawStart, drawEnd, color, game);
}



int draw_loop(t_game *game)
{
    clear_image(game);

   
    move_player(&game->player, game->map->line);
    t_player *p = &game->player;
    for (int x = 0; x < game->win_width; ++x)
        render_column(game, p, x);
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