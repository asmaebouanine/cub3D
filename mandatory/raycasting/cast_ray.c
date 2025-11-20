/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asbouani <asbouani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:07:57 by asbouani          #+#    #+#             */
/*   Updated: 2025/11/12 15:28:35 by asbouani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	init_delta(t_ray *ray)
{
	if (ray->ray_dx == 0)
		ray->delta_x = 1e30;
	else
		ray->delta_x = fabs(1.0 / ray->ray_dx);
	if (ray->ray_dy == 0)
		ray->delta_y = 1e30;
	else
		ray->delta_y = fabs(1.0 / ray->ray_dy);
}

void	init_step(t_ray *ray, double pos_x, double pos_y)
{
	if (ray->ray_dx < 0)
	{
		ray->step_x = -1;
		ray->dist_x = (pos_x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->dist_x = (ray->map_x + 1.0 - pos_x) * ray->delta_x;
	}
	if (ray->ray_dy < 0)
	{
		ray->step_y = -1;
		ray->dist_y = (pos_y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->dist_y = (ray->map_y + 1.0 - pos_y) * ray->delta_y;
	}
}

int	step_dda(t_game *game, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (ray->dist_x < ray->dist_y)
		{
			ray->dist_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->dist_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_x < 0 || ray->map_x >= game->map->width
			|| ray->map_y < 0 || ray->map_y >= game->map->height)
			return (1);
		if (game->map->line[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
	return (hit);
}

double	cast_ray(t_game *game, t_player *p, t_ray *ray)
{
	double	posx;
	double	posy;
	double	perp_dist;

	posx = p->x / (double)SIZE;
	posy = p->y / (double)SIZE;
	ray->map_x = (int)posx;
	ray->map_y = (int)posy;
	init_delta(ray);
	init_step(ray, posx, posy);
	step_dda(game, ray);
	if (ray->side == 0)
		perp_dist = ray->dist_x - ray->delta_x;
	else
		perp_dist = ray->dist_y - ray->delta_y;
	if (perp_dist < 1e-6)
		perp_dist = 1e-6;
	return (perp_dist);
}
