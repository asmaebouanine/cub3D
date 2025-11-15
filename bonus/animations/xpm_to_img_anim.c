/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_to_img_anim.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 18:57:41 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/11/13 12:32:22 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	weapon_pixels( t_w_texture *weapon_tex,
			int start_x, int start_y, t_game *game)
{
	int				x;
	int				y;
	char			*pixel;
	unsigned int	color;

	y = 0;
	if (!weapon_tex || !weapon_tex->img || !weapon_tex->addr)
		return ;
	while (y < (weapon_tex)->height)
	{
		x = 0;
		while (x < (weapon_tex)->width)
		{
			pixel = weapon_tex->addr
				+ (y *(weapon_tex->line_size) + x *(weapon_tex->bpp) / 8);
			color = *(unsigned int *)pixel;
			if (color != 0xFF000000)
				put_pixel(x + start_x, y + start_y, color, game);
			x++;
		}
		y++;
	}
}




void	attack_handling(t_game *game)
{
	int			x;
	int			y;
	t_w_texture	*weapon_tex;

	weapon_tex = &game->weapons.weapons[game->curr_weap];
	if (!weapon_tex || !weapon_tex->img)
		return ;
	x = (game->win_width / 2) - (weapon_tex->width / 2);
	y = game->win_height - weapon_tex->height;
	weapon_pixels(weapon_tex, x, y, game);
	game->curr_weap++;
	if (game->curr_weap >= 7)
	{
		game->curr_weap = 0;
		game->attacking = 0;
	}
}

void	draw_weapon(t_game *game)
{
	t_w_texture	*weapon_tex;
	int			x;
	int			y;

	if (!game)
		return ;
	if (game->attacking)
	{
		attack_handling(game);
		return ;
	}
	weapon_tex = &game->weapons.weapons[0];
	if (weapon_tex->img)
	{
		x = (game->win_width / 2) - (weapon_tex->width / 2);
		y = game->win_height - weapon_tex->height;
		weapon_pixels(weapon_tex, x, y, game);
	}
}

t_w_texture	*lst_new_weapon(char *path, void *mlx_ptr)
{
	t_w_texture	*texture;

	texture = gcmalloc(sizeof(t_w_texture), 0);
	if (!path || !texture)
		return (NULL);
	texture->img = mlx_xpm_file_to_image(mlx_ptr,
			path, &(texture->width), &(texture->height));
	if (!(texture->img))
		return (NULL);
	texture->addr = mlx_get_data_addr(texture->img,
			&(texture->bpp), &(texture->line_size), &(texture->endian));
	if (!(texture->addr))
		return (NULL);
	return (texture);
}

t_weapon	*xmp_t_img_wpn(char **weapons, void *mlx_ptr)
{
	t_weapon	*weapon;
	t_w_texture	*tmp_tex;
	int			i;

	i = 0;
	weapon = gcmalloc(sizeof(t_weapon), 0);
	if (!weapons || !weapon)
		return (NULL);
	while (i < 7)
	{
		tmp_tex = lst_new_weapon(weapons[i], mlx_ptr);
		if (tmp_tex == NULL)
			return (NULL);
		weapon->weapons[i] = *tmp_tex;
		i++;
	}
	return (weapon);
}
