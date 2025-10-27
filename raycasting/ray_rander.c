/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_rander.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 20:20:40 by asbouani          #+#    #+#             */
/*   Updated: 2025/10/27 19:02:51 by wnid-hsa         ###   ########.fr       */
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

unsigned int apply_shading(unsigned int color, double dist)
{
    double darkness;
    int r;
    int g;
    int b;
    
    darkness = 1.0 / (1.0 + dist * 0.1); 
    r = (int)(((color >> 16) & 0xFF) * darkness);
    g = (int)(((color >> 8) & 0xFF) * darkness);
    b = (int)((color & 0xFF) * darkness);
    
    return (r << 16) | (g << 8) | b;
}
unsigned int get_texture_color(t_texture *tex, int x, int y)
{
    char *dst;
    
    dst = tex->addr + (y * tex->line_size + x * (tex->bpp / 8));

    return (*(unsigned int*)dst);
}
void draw_floor_and_ceiling(t_game *game, int x)
{
    int y;
 
    y = 0;
    while (y < game->win_height)
    {
        
        if (y < game->win_height / 2)
            put_pixel(x, y, 0x808080, game);
        else 
            put_pixel(x, y, 0x404040, game);
        
        y++;
    }
}
void draw_wall(int x, t_line *line, t_game *game, t_ray *ray, double dist)
{
    t_texture *tex;
    int tex_x;
    double step;
    double tex_pos;
    int tex_y;
    int y;
    unsigned int color ;

    tex = &game->convas.textures[ray->tex_id];
    tex_x = (int)(ray->wallX * tex->width);

    step = 1.0 * tex->height / line->line_height;
    tex_pos = (line->draw_start - game->win_height / 2 + line->line_height / 2) * step;

    y = line->draw_start;
    while (y < line->draw_end)
    {
        tex_y = (int)tex_pos & (tex->height - 1);
        tex_pos += step;
        color = get_texture_color(tex, tex_x, tex_y);

        color = apply_shading(color, dist); 
    
        put_pixel(x, y, color, game);
        y++;
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
void calc_wall(t_game *game, t_ray *ray, double dist, t_line *line)
{
    line->line_height = (int)(game->win_height / dist);
    line->draw_start = -(line->line_height) / 2 + game->win_height / 2;
    line->draw_end   = (line->line_height) / 2 + game->win_height / 2;
    if (line->draw_start < 0)
        line->draw_start = 0;
    if (line->draw_end >= game->win_height)
        line->draw_end = game->win_height - 1;
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
    wallx_call(game, ray, dist);
}

void render_column(t_game *game, int x)
{
    t_ray ray;
    t_line line;
    double dist;

    draw_floor_and_ceiling(game, x);
    ray_direction(game, &ray, x);
    dist = cast_ray(game, &game->player, &ray);
    calc_wall(game, &ray, dist, &line);
    draw_wall(x, &line, game, &ray, dist); 
}
