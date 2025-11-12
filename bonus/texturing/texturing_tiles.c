/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturing_tiles.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:12:34 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/11/11 23:55:11 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void wallx_call(t_game *game, t_ray *ray, double dist)
{
    double player_x_unit;
    double player_y_unit;
    double hit_world;

    player_x_unit = game->player.x /(double)SIZE;
    player_y_unit = game->player.y /(double)SIZE;
    
    if (ray->side == 0) 
        hit_world = player_y_unit + ray->ray_dy * dist;
    else 
        hit_world = player_x_unit + ray->ray_dx * dist;
    
    ray->wallX = hit_world - floor(hit_world);
    if (ray->tex_id == WE || ray->tex_id == SO) 
        ray->wallX = 1.0 - ray->wallX;
}

void calc_wall_2(t_ray *ray)
{
    if(ray->side == 1)
    {
        if(ray->step_y < 0)
            ray->tex_id = SO ;
        else
            ray->tex_id = NO;
    }
    else
    {
        if(ray->step_x < 0)
            ray->tex_id = EA;
        else
            ray->tex_id = WE;
    }
}

void calc_wall(t_game *game, t_ray *ray, double dist, t_line *line)
{
    line->line_height = (int)(game->win_height / dist);
    line->draw_start = -(line->line_height) / 2 + game->win_height / 2;
    line->draw_end   = (line->line_height) / 2 + game->win_height / 2;
    if (line->draw_start < 0)
        line->draw_start = 0;
    if (line->draw_end >= game->win_height)
        line->draw_end = game->win_height - 1;
    if(ray->type == 2)
        ray->tex_id = DO;
    else
        calc_wall_2(ray);
    wallx_call(game, ray, dist);
}

void draw_floor_and_ceiling(t_game *game, int x)
{
    int y;
 
    y = 0;
    while (y < game->win_height)
    {
        
        if (y < game->win_height / 2)
            put_pixel(x, y,0x250015, game);
        else 
            put_pixel(x, y,0x000000 ,game);
        
        y++;
    }
}

void draw_wall(int x, t_line *line, t_game *game, t_ray *ray)
{
    t_texture *tex;
    t_tex_cood tex_coor;
    int y;
    unsigned int color ;
    
    tex = &game->convas.textures[ray->tex_id];
    tex_coor.tex_x = (int)(ray->wallX * tex->width);
    tex_coor.step = 1.0 * tex->height / line->line_height;
    tex_coor.tex_pos = (line->draw_start 
                            - game->win_height / 2 
                                    + line->line_height / 2) * tex_coor.step;
    y = line->draw_start;
    while (y < line->draw_end)
    {
        tex_coor.tex_y = (int)tex_coor.tex_pos % (tex->height);
        tex_coor.tex_pos += tex_coor.step;
        color = get_texture_color(tex, tex_coor.tex_x, tex_coor.tex_y);
        color = apply_shading(color); 
        put_pixel(x, y, color, game);
        y++;
    }
}