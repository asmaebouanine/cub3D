/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_strjoin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:27:43 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/11/02 17:27:44 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cub3D.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	size;

	size = ft_strlen(needle);
	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	i = 0;
	while (haystack[i] && (size <= len - i))
	{
		if (ft_strncmp(haystack + i, needle, size) == 0)
		{
			return ((char *)haystack + i);
		}
		i++;
	}
	return (NULL);
}

char	*ft_strndup(const char *s1, size_t n)
{
	size_t	size;
	char	*str;

	if (!s1 || !n)
		return (NULL);
	size = ft_strlen(s1);
	if (size > n)
		size = n;
	str = (char *)malloc(size + 1);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1, size + 1);
	return (str);
}

char	*custom_strdup(const char	*s1, int pid)
{
	char	*ptr;

	if (!s1)
		return (NULL);
	ptr = (char *)gcmalloc(ft_strlen(s1) + 1, pid);
	if (ptr == NULL)
		return (NULL);
	ptr = ft_memcpy(ptr, s1, ft_strlen(s1));
	ptr[ft_strlen(s1)] = '\0';
	return (ptr);
}

static	void	loop_copying_s2(const char *s2, char **ptr, int count)
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

char	*custom_strjoin(const char *s1, const char *s2, int pid)
{
	char	*ptr;
	size_t	i;
	size_t	count;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (!s1)
		return (custom_strdup(s2, pid));
	if (!s2)
		return (custom_strdup(s1, pid));
	ptr = (char *)gcmalloc(ft_strlen(s1) + ft_strlen(s2) + 1, pid);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	count = i;
	loop_copying_s2(s2, &ptr, count);
	return (ptr);
}
