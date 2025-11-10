/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_to_img_anim.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 18:57:41 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/11/10 01:15:18 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void draw_weapon(t_game *game)
{
    int frame;
    t_w_texture *weapon_tex;
    
    frame = game->curr_weap;
    weapon_tex = &game->weapons.weapons[frame];

    if (weapon_tex->img)
    {
        int x = (game->win_width / 2) - (weapon_tex->width / 2);
        int y = game->win_height - weapon_tex->height;
        mlx_put_image_to_window(game->mlx, game->win, weapon_tex->img, x, y);
    }
}
t_w_texture *lst_new_weapon(char *path, void *mlx_ptr)
{
    t_w_texture *texture;
    
    texture = gcmalloc(sizeof(t_w_texture),0);
    if(!path || !texture)
        return(NULL);
    texture->img = mlx_xpm_file_to_image(mlx_ptr, path, &(texture->width), &(texture->height));
    if(!(texture->img))
        return(NULL);
    return(texture);
}

t_weapon *xmp_t_img_wpn(char **weapons, void *mlx_ptr)
{
    t_weapon *weapon;
    t_w_texture *tmp_tex;
    int i;

    i = 0;
    weapon = gcmalloc(sizeof(t_weapon), 0);
    if(!weapons || !weapon)
        return(NULL);   
    while(i < 24)
    {
       tmp_tex = lst_new_weapon(weapons[i], mlx_ptr);
       if(tmp_tex == NULL)
            return(NULL);
        weapon->weapons[i]= *tmp_tex;
        i++;
    }
    return(weapon);
}