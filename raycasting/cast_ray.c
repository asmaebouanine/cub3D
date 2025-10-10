/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asbouani <asbouani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:07:57 by asbouani          #+#    #+#             */
/*   Updated: 2025/10/10 16:03:53 by asbouani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

//calcute fixed step distance for the ray to cross the nest line x y
void	init_delta(t_ray *ray)
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

void	init_step(t_ray *ray, double posX, double posY) //prepares the ray to start moving in the correct direction across the map grid and tells how far the first wall is along each axis.
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

int	step_dda(t_game *game, t_ray *ray) // step the ray through the map until cross the wall
{
	int	hit;

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
		if (ray->mapX < 0 || ray->mapX >= game->map->width
			|| ray->mapY < 0 || ray->mapY >= game->map->height)
			return (1);
		if (game->map->line[ray->mapY][ray->mapX] == '1')
			hit = 1;
	}
	return (hit);
}

double	cast_ray(t_game *game, t_player *p,t_ray *ray) //shoots a ray form the player position to hit the wall using DDA algorithm
{
	double	posx;
	double	posy;
	double	perp_dist;
	
	posx = p->x / (double)SIZE;
	posy = p->y / (double)SIZE;
	ray->mapX = (int)posx;
	ray->mapY = (int)posy;
	init_delta(ray);
	init_step(ray, posx, posy);//determines the ray direction and calculate the distance between the player and next grid
	step_dda(game, ray);
	if (ray->side == 0)
		perp_dist = ray->sideDistX - ray->deltaDistX;
	else
		perp_dist = ray->sideDistY - ray->deltaDistY;
	if (perp_dist < 1e-6)
		perp_dist = 1e-6;
	return (perp_dist);
}
