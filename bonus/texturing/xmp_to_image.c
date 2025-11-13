/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmp_to_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 04:47:26 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/11/13 17:30:27 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

t_texture	*lst_new_convas(char *path, void *mlx_ptr)
{
	t_texture	*texture;

	texture = gcmalloc(sizeof(t_texture), 0);
	if (!path || !texture)
		return (NULL);
	texture->img = mlx_xpm_file_to_image(mlx_ptr, path,
			&(texture->width), &(texture->height));
	if (!(texture->img))
		return (NULL);
	texture->addr = mlx_get_data_addr(texture->img,
			&(texture->bpp), &(texture->line_size), &(texture->endian));
	if (!(texture->addr))
		return (NULL);
	return (texture);
}

t_convas	*xmp_to_image(char **textures, void *mlx_ptr)
{
	t_convas	*convas;
	t_texture	*tmp_tex;
	int			i;

	i = 0;
	convas = gcmalloc(sizeof(t_convas), 0);
	if (!textures || !convas)
		return (NULL);
	while (textures[i])
	{
		tmp_tex = lst_new_convas(textures[i], mlx_ptr);
		if (tmp_tex == NULL)
		{
			return (NULL);
		}
		convas->textures[i] = *tmp_tex;
		i++;
	}
	return (convas);
}
