/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_rander.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 20:20:40 by asbouani          #+#    #+#             */
/*   Updated: 2025/11/12 11:19:15 by wnid-hsa         ###   ########.fr       */
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

void ray_direction(t_game *game, t_ray *ray, int x)
{
    double cameraX;
    
    cameraX = 2.0 * x / (double)game->win_width - 1.0;
    ray->ray_dx = game->player.dx + game->player.plane_x * cameraX;
    ray->ray_dy = game->player.dy + game->player.plane_y * cameraX;
}


int save_distance(double dist)
{
    static double dis;
    
    if(dist >=0)
    {
        dis = dist;
    }
    return(dis);
}
void render_column(t_game *game, int x)
{
    t_ray ray;
    t_line line;
    double dist;

    draw_floor_and_ceiling(game, x);
    ray_direction(game, &ray, x);
    dist = cast_ray(game, &game->player, &ray);
    save_distance(dist);
    calc_wall(game, &ray, dist, &line);
    draw_wall(x, &line, game, &ray); 
}
