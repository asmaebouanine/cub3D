/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_fill_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 10:46:36 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/11/13 13:06:02 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

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

void	anims(char **anim)
{
	anim[0] = custom_strdup("./weapons/weapon_0.xpm", 0);
	anim[1] = custom_strdup("./weapons/weapon_1.xpm", 0);
	anim[2] = custom_strdup("./weapons/weapon_2.xpm", 0);
	anim[3] = custom_strdup("./weapons/weapon_3.xpm", 0);
	anim[4] = custom_strdup("./weapons/weapon_4.xpm", 0);
	anim[5] = custom_strdup("./weapons/weapon_5.xpm", 0);
	anim[6] = custom_strdup("./weapons/weapon_6.xpm", 0);
	anim[7] = custom_strdup("./weapons/weapon_7.xpm", 0);
	
}

char	**anim_alloc(void)
{
	char	**anim;
	int		i;

	anim = gcmalloc(25 *(sizeof(char *)), 0);
	if (!anim)
		return (NULL);
	anims(anim);
	i = 0;
	while (i < 7)
	{
		if (!anim[i])
			return (NULL);
		i++;
	}
	anim[7] = NULL;
	return (anim);
}
