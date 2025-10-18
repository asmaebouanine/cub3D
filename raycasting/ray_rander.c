/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_rander.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asbouani <asbouani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 20:20:40 by asbouani          #+#    #+#             */
/*   Updated: 2025/10/18 20:25:42 by asbouani         ###   ########.fr       */
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

// draw a verical line (wall)
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
//calcutate the direction of the a ray
void ray_direction(t_game *game, t_ray *ray, int x)
{
    double cameraX;
    
    cameraX = 2.0 * x / (double)game->win_width - 1.0;
    ray->ray_dx = game->player.dx + game->player.plane_x * cameraX;
    ray->ray_dy = game->player.dy + game->player.plane_y * cameraX;
}
// calculate where and how the wall should be draw 
void calc_wall(t_game *game, t_ray *ray, double dist, t_line *line)
{
    line->line_height = (int)(game->win_height / dist);
    line->draw_start = -(line->line_height) / 2 + game->win_height / 2;
    line->draw_end   = (line->line_height) / 2 + game->win_height / 2;
    if (line->draw_start < 0)
        line->draw_start = 0;
    if (line->draw_end >= game->win_height)
        line->draw_end = game->win_height - 1;
    line->color = 0xFFFF00;
    if (ray->side == 1)
        line->color = (line->color >> 1) & 0x7F7F7F;
}

void render_column(t_game *game, int x)
{
    t_ray ray;
    t_line line;
    double dist;

    ray_direction(game, &ray, x);
    dist = cast_ray(game, &game->player, &ray);
    calc_wall(game, &ray, dist, &line);
    draw_wall(x, line.draw_start, line.draw_end, line.color, game);
}
