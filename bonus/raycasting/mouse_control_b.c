/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_control_b.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asbouani <asbouani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:45:17 by asbouani          #+#    #+#             */
/*   Updated: 2025/11/10 18:39:49 by asbouani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

int mouse_move(int x, int y, t_game *game)
{
    (void)y;
    static int last_x = -1;
    int diff_x;
    double speed;
    double rot_speed;

    speed = 0.005;
    if (last_x == -1)
    {
        last_x = x;
        return 0;
    }
    diff_x = x - last_x;
    last_x = x;

    rot_speed = diff_x * speed;
    rotate_player(&game->player, rot_speed);
    return (0);
}
