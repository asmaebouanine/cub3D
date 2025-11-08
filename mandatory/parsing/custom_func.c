/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asbouani <asbouani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:27:26 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/11/08 17:29:04 by asbouani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cub3D.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				i;
	const unsigned char	*ptr;
	const unsigned char	*ptr1;

	ptr = (const unsigned char *)s1;
	ptr1 = (const unsigned char *)s2;
	if (n == 0)
	{
		return (0);
	}
	else
	{
		i = 0;
		while (i < (n - 1) && (ptr[i] == ptr1[i])
			&& (ptr[i] != '\0' && ptr1[i] != '\0'))
		{
			i++;
		}
		return (ptr[i] - ptr1[i]);
	}
}

char	*ft_strdup_(const char *s1)
{
	char	*ptr;

	if (s1 == NULL || *s1 == '\0')
		return (NULL);
	ptr = (char *)gcmalloc(ft_strlen(s1) + 1, 0);
	if (ptr == NULL)
		return (NULL);
	ptr = ft_memcpy(ptr, s1, ft_strlen(s1));
	ptr[ft_strlen(s1)] = '\0';
	return (ptr);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	if (size > 0)
	{
		while (i < (size - 1) && src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}

static int	isin(const char *set, char c)
{
	size_t	i;

	i = 0;
	if (!set)
		return (0);
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	start;
	size_t	end;
	size_t	len;
	char	*result;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup_(s1));
	if (s1[0] == '\0')
		return (ft_strdup_(""));
	start = 0;
	while (s1[start] && isin(set, s1[start]))
		start++;
	end = ft_strlen(s1) - 1;
	while (end > start && isin(set, s1[end]))
		end--;
	len = end - start + 1;
	result = gcmalloc(len + 1, 0);
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1 + start, len + 1);
	return (result);
}