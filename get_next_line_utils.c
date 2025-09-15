/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 19:55:28 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/09/07 03:01:44 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



size_t	ft_strlen2(const char *str, char *temp)
{
	size_t	i;
	int		flag;

	if (str == NULL)
		return (0);
	flag = 0;
	if (str == temp)
		flag = 1;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n' && flag == 1)
		{
			i++;
			break ;
		}
		i++;
	}
	return (i);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*ptr;
	unsigned const char	*ptr2;
	size_t				i;

	if (dst == src)
	{
		return ((void *)src);
	}
	ptr = (unsigned char *)dst;
	ptr2 = (unsigned const char *)src;
	i = 0;
	while (i < n)
	{
		ptr[i] = ptr2[i];
		i++;
	}
	return (dst);
}

char	*ft_strdup(char *s1, char *temp)
{
	char	*ptr;

	if (s1 == NULL || *s1 == '\0')
		return (NULL);
	ptr = (char *)gcmalloc(ft_strlen2(s1, temp) + 1, 0);
	if (ptr == NULL)
		return (NULL);
	ptr = ft_memcpy(ptr, s1, ft_strlen2(s1, temp));
	ptr[ft_strlen2(s1, temp)] = '\0';
	return (ptr);
}

char	*rest_of_line(char *temp)
{
	int		i;
	char	*rest;

	i = 0;
	rest = NULL;
	while (temp[i])
	{
		if (temp[i] == '\n')
		{
			i++;
			rest = ft_strdup(temp + i, temp);
			return (rest);
		}
		i++;
	}
	return (NULL);
}

char	*until_newline(char *rest)
{
	int		i;
	char	*r;
	int		count;

	(1 && (i = 0), (count = 0));
	while (rest[i])
	{
		if (rest[i] == '\n')
			break ;
		i++;
	}
	if (rest[i] == '\n')
	{
		r = (char *)gcmalloc(i + 2, 0);
		if (!r)
			return (NULL);
		r[i + 1] = '\0';
		while (count <= i)
		{
			r[count] = rest[count];
			count++;
		}
		return (r);
	}
	return (NULL);
}
