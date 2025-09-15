/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 19:34:25 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/09/07 05:08:34 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	freegarbage(t_trash **trash, int status_flag)
{
	t_trash	*tmp;

	while (*trash)
	{
		tmp = *trash;
		*trash = (*trash)->next;
		free(tmp->point);
		free(tmp);
	}
	exit(status_flag);
}

void	*gcmalloc(size_t size, int status_flag)
{
	static t_trash	*trash;
	void			*ptr;
	t_trash			*new;

	if (size == 0)
		freegarbage(&trash, status_flag);
	new = malloc(sizeof(t_trash));
	if (!new)
		freegarbage(&trash, 1);
	ptr = malloc(size);
	if (!ptr)
		freegarbage(&trash, 1);
	new->point = ptr;
	new->next = trash;
	trash = new;
	return (ptr);
}
