/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asbouani <asbouani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:45:17 by asbouani          #+#    #+#             */
/*   Updated: 2025/11/03 14:05:21 by asbouani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int mouse_move(int x, int y, t_game *game)
{
    (void)y;
    static int last_x = -1;
    int diff_x;
    double speed;
    double rot_speed;

    speed = 0.001;
    if (last_x == -1)
        last_x = x;  // first call, set initial mouse position

    diff_x = x - last_x;
    last_x = x;  // update last_x for next movement

    rot_speed = diff_x * speed;
    rotate_player(&game->player, -rot_speed);
    return (0);
}
