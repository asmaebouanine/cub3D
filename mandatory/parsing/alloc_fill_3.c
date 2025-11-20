/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_fill_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 11:19:54 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/11/13 19:09:15 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	color_filler(char *colors, t_config **config, char *ident)
{
	char	**splitted;
	int		color;
	int		i;

	i = 0;
	splitted = custom_split(colors, ',', 1);
	if (!splitted[0] || !splitted[1] || !splitted[2])
		return ;
	color = (ft_atoi(splitted[0]) << 16
			| ft_atoi(splitted[1]) << 8 | ft_atoi(splitted[2]));
	if (!ft_strcmp(ident, "F"))
		(*config)->color->f_color = color;
	else if (!ft_strcmp(ident, "C"))
		(*config)->color->c_color = color;
}
