/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:27:18 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/11/15 23:11:28 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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

static void	closegarbage(t_fds **trash, int status_flag)
{
	t_fds	*tmp;
	
	while (*trash)
	{
		tmp = *trash;
		*trash = (*trash)->next;
		close(tmp->fd);
		free(tmp);
	}
	exit(status_flag);
}

void gc_fds(int fd)
{
	static t_fds	*trash;
	t_fds			*new;

	new = malloc(sizeof(t_fds));
	if(fd < 0)
		closegarbage(&trash, 0);
	if (!new)
		closegarbage(&trash, 1);
	new->fd = fd;
	new->next = trash;
	trash = new;
}