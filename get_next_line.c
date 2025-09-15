/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 19:52:36 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/09/07 02:18:04 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	loop_copying_s2(const char *s2, char **ptr, int count)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		(*ptr)[count] = s2[i];
		i++;
		count++;
	}
	(*ptr)[count] = '\0';
}

char	*ft_strjoin(char *s1, char *s2, char *temp, int flag)
{
	char	*ptr;
	size_t	i;
	char	*to_free;

	flag = 0;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (!s1)
	{
		(1 && (to_free = s2), (ptr = ft_strdup(s2, temp)));
		return (ptr);
	}
	if (!s2)
		return (ft_strdup(s1, temp));
	ptr = (char *)gcmalloc(ft_strlen2(s1, temp) + ft_strlen2(s2, temp) + 1, 0);
	if (ptr == NULL)
		return (NULL);
	i = -1;
	while (s1[++i])
		ptr[i] = s1[i];
	loop_copying_s2(s2, &ptr, i);
	return (ptr);
}

char	*actual_temp(char *temp)
{
	int		i;
	char	*p;

	if (!temp)
		return (NULL);
	p = (char *)gcmalloc(ft_strlen2(temp, temp) + 1, 0);
	if (!p)
		return (NULL);
	i = 0;
	while (temp[i])
	{
		if (temp[i] == '\n')
		{
			p[i] = '\n';
			p[i + 1] = '\0';
			return (p);
		}
		p[i] = temp[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*rest_handling(char **join, char **rest, char *temp)
{
	int	flag;
	int	i;

	flag = 0;
	i = 0;
	while ((*rest)[i])
	{
		if ((*rest)[i] == '\n')
			flag = 1;
		i++;
	}
	if (flag == 1)
	{
		*join = until_newline(*rest);
		*rest = rest_of_line(*rest);
		return (*join);
	}
	else
	{
		*join = ft_strjoin(*join, *rest, temp, 0);
		*rest = NULL;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*join;
	int			b_read;
	char		*temp;

	(1 && (join = NULL), (temp = (char *)gcmalloc(BUFFER_SIZE + 1, 0)));
	if (rest != NULL && rest_handling(&join, &rest, temp) != NULL)
		return (join);
	b_read = read(fd, temp, BUFFER_SIZE);
	if (b_read < 0)
		return (NULL);
	temp[b_read] = '\0';
	while (b_read > 0)
	{
		join = ft_strjoin(join, actual_temp(temp), temp, 1);
		(1 && (rest = rest_of_line(temp)), (b_read = -1));
		if (!join)
			return (NULL);
		while (join[++b_read])
			if (join[b_read] == '\n')
				return (join);
		(1 && (b_read = read(fd, temp, BUFFER_SIZE)), (temp[b_read] = '\0'));
	}
	return (join);
}

