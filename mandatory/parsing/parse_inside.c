/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_inside.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 11:27:56 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/11/13 19:55:42 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	parse_inside_2(t_plines *res, int *player, int flag, int *i)
{
	if (res->line[*i] != '1')
		return (-1);
	while (res->line[*i] && res->line[*i] != '\n')
	{
		if (res->line[*i] == ' ')
		{
			if (!space_checking(res, *i))
				return (-1);
		}
		if (res->line[*i] == 'N' || res->line[*i] == 'S'
			|| res->line[*i] == 'E' || res->line[*i] == 'W')
		{
			save_coordin(*i, flag, res->line[*i]);
			(*player)++;
		}
		(*i)++;
	}
	return (1);
}

int	parse_inside(t_plines *res, int *player, int flag)
{
	int		i;
	size_t	len;
	char	*str;

	if (!res)
		return (-1);
	i = 0;
	len = ft_strlen(res->line);
	if (!len || !valid_map_chars(res->line))
		return (-1);
	while (res->line[i] && res->line[i] == ' ' && res->line[i] != '\n')
	{
		if (!space_checking(res, i))
			return (-1);
		i++;
	}
	if (res->line[i] != '1')
		return (-1);
	if (parse_inside_2(res, player, flag, &i) == -1)
		return (-1);
	str = ft_strtrim(res->line, " \n");
	if (!str || (ft_strlen(str) -1 >= 0 && (str[ft_strlen(str) -1] != '1')))
		return (-1);
	return (1);
}
