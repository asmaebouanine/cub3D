/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturing_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:20:22 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/11/13 18:45:56 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

unsigned int	apply_shading(unsigned int color)
{
	double	darkness;
	int		r;
	int		g;
	int		b;

	darkness = 1.0 / (1.0 + save_distance(-1) * 0.1);
	r = (int)(((color >> 16) & 0xFF) * darkness);
	g = (int)(((color >> 8) & 0xFF) * darkness);
	b = (int)((color & 0xFF) * darkness);
	return ((r << 16) | (g << 8) | b);
}

unsigned int	get_texture_color(t_texture *tex, int x, int y)
{
	char	*dst;

	dst = tex->addr + (y * tex->line_size + x * (tex->bpp / 8));
	return (*(unsigned int *)dst);
}
