/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:39:53 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/09/10 17:00:31 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_strcmp(const char *s1, const char *s2)
{
    int i = 0;

    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}

static	int	sign_atoi(const char *str, int *i)
{
	int	sign ;

	sign = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			sign = sign * (-1);
		(*i)++;
	}
	return (sign);
}

int	ft_atoi(const char *str)
{
	int				i;
	unsigned long	result;
	int				sign;

	i = 0;
	result = 0;
	while ((str[i] > 8 && str[i] <= 13) || str[i] == ' ')
		i++;
	sign = sign_atoi(str, &i);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		if (result > ((ULONG_MAX - (str[i] - '0')) / 10) && sign == 1)
			return (-1);
		if (result > ((ULONG_MAX - (str[i] - '0')) / 10) && sign == -1)
		{
			if (result == 9223372036854775807)
				return (1);
			return (0);
		}
		i++;
	}
	return (sign * result);
}

