/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asbouani <asbouani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:08:57 by asbouani          #+#    #+#             */
/*   Updated: 2025/10/03 17:13:16 by asbouani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void set_player_position(t_player *p, char **map)
{
    int y = 0;
    int x;

    while (map[y])
    {
        x = 0;
        while (map[y][x])
        {
            if (map[y][x] == 'N' || map[y][x] == 'S' ||
                map[y][x] == 'E' || map[y][x] == 'W')
            {
                p->x = x * SIZE + SIZE / 2;
                p->y = y * SIZE + SIZE / 2;

                if (map[y][x] == 'N') { p->dx = 0; p->dy = -1; p->plane_x = 0.66; p->plane_y = 0; }
                if (map[y][x] == 'S') { p->dx = 0; p->dy = 1;  p->plane_x = -0.66; p->plane_y = 0; }
                if (map[y][x] == 'E') { p->dx = 1; p->dy = 0;  p->plane_x = 0; p->plane_y = 0.66; }
                if (map[y][x] == 'W') { p->dx = -1; p->dy = 0; p->plane_x = 0; p->plane_y = -0.66; }

                return;
            }
            x++;
        }
        y++;
    }
}

void init_player(t_game *g)
{
    set_player_position(&g->player, g->map->line);

    g->player.key_up = false;
    g->player.key_down = false;
    g->player.key_left = false;
    g->player.key_right = false;
    g->player.key_rot_left = false;
    g->player.key_rot_right = false;
    g->player.rot_step = 0.05;
}


int key_press(int keycode, t_player *player)
{
    if (keycode == LEFT_ARROW)
        player->key_rot_left = true;
    if (keycode == RIGHT_ARROW)
        player->key_rot_right = true;
    if (keycode == W)
        player->key_up = true;
    if (keycode == S)
        player->key_down = true;
    if (keycode == A)
        player->key_left = true;
    if (keycode == D)
        player->key_right = true;
    if (keycode == ESC || keycode == X)
        exit (1);
    return (0);
}

int key_release(int keycode, t_player *player)
{
     if (keycode == LEFT_ARROW)
        player->key_rot_left = false;
    if (keycode == RIGHT_ARROW)
        player->key_rot_right = false;
    if (keycode == W)
        player->key_up = false;
    if (keycode == S)
        player->key_down = false;
    if (keycode == A)
        player->key_left = false;
    if (keycode == D)
        player->key_right = false;
    return (0);
}
void check_and_move(t_player *p, char **map, double new_x, double new_y)
{
    // Current cell position
    int row_map = (int)(p->y / SIZE);
    int col_map = (int)(p->x / SIZE);

    // Next cell position
    int new_row_y = (int)(new_y / SIZE);
    int new_col_x = (int)(new_x / SIZE);

    // Check X movement (avoid walls)
    if (map[row_map][new_col_x] != '1')
        p->x = new_x;

    // Check Y movement (avoid walls)
    if (map[new_row_y][col_map] != '1')
        p->y = new_y;
}


void rotate_player(t_player *p, double step)
{
    double old_dx = p->dx;
    double old_dy = p->dy;
    double old_plane_x = p->plane_x;
    double old_plane_y = p->plane_y;

    // Simple rotation without trig (approximated for small step)
    p->dx = old_dx + step * -old_dy;
    p->dy = old_dy + step * old_dx;

    p->plane_x = old_plane_x + step * -old_plane_y;
    p->plane_y = old_plane_y + step * old_plane_x;

    // Normalize to keep length ≈ 1
    double length = sqrt(p->dx * p->dx + p->dy * p->dy);
    p->dx /= length;
    p->dy /= length;
    length = sqrt(p->plane_x * p->plane_x + p->plane_y * p->plane_y);
    p->plane_x /= length;
    p->plane_y /= length;
}


void move_player(t_player *p, char **map)
{
    double speed = 5;
    double new_x = p->x;
    double new_y = p->y;

    if (p->key_rot_left)
        rotate_player(p, p->rot_step);
    if (p->key_rot_right)
        rotate_player(p, -p->rot_step);

    if (p->key_up) 
    {
        new_x += p->dx * speed;
        new_y += p->dy * speed;
        check_and_move(p, map, new_x, new_y);
    }
    if (p->key_down) 
    {
        new_x -= p->dx * speed;
        new_y -= p->dy * speed;
        check_and_move(p, map, new_x, new_y);
    }
    if (p->key_left) 
    {
        new_x += p->dy * speed;
        new_y -= p->dx * speed;
        check_and_move(p, map, new_x, new_y);
    }
    if (p->key_right) 
    {
        new_x -= p->dy * speed;
        new_y += p->dx * speed;
        check_and_move(p, map, new_x, new_y);
    }
}