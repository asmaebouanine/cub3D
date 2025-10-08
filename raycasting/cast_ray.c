/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asbouani <asbouani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:07:57 by asbouani          #+#    #+#             */
/*   Updated: 2025/10/06 20:38:01 by asbouani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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

// step the ray through the map until cross the wall
int step_DDA(t_game *game, t_ray *ray)
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
//shoots a ray form the player position to hit the wall using DDA algorithm
double cast_ray(t_game *game, t_player *p,t_ray *ray)
{
    double posX;
    double posY;
    double perpDist;
    
    posX = p->x / (double)SIZE;
    posY = p->y / (double)SIZE;
    ray->mapX = (int)posX;
    ray->mapY = (int)posY;
    init_delta(ray);
    init_step(ray, posX, posY);//determines the ray direction and calculate the distance between the player and next grid
    step_DDA(game, ray);
    if (ray->side == 0)
        perpDist = ray->sideDistX - ray->deltaDistX;
    else
        perpDist = ray->sideDistY - ray->deltaDistY;
    if (perpDist < 1e-6)
        perpDist = 1e-6;
    return perpDist;
}
