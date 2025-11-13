/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_coord.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 00:32:24 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/11/13 13:52:01 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

t_door	*ft_lstnew_dr(int x, int y)
{
	t_door	*new_door;

	new_door = gcmalloc(sizeof(t_door), 0);
	if (!new_door)
		return (NULL);
	new_door->door_x = x;
	new_door->door_y = y;
	new_door->state = 'c';
	new_door->next = NULL;
	return (new_door);
}

int	lst_size_dr(t_door *door)
{
	int	i;

	if (!door)
		return (0);
	i = 0;
	while (door)
	{
		i++;
		door = door->next;
	}
	return (i);
}

void	ft_lstadd_back_dr(t_door **lst, t_door *new)
{
	t_door	*temp;

	if (new == NULL)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while ((temp)->next != NULL)
	{
		(temp) = (temp)->next;
	}
	(temp)->next = new;
}

t_door	*doors_coordin(int x, int y)
{
	static t_door	*door_coor;
	t_door			*new;

	if (!door_coor)
		door_coor = door_struct();
	if (x >= 0 && y >= 0)
	{
		new = ft_lstnew_dr(x, y - 1);
		ft_lstadd_back_dr(&door_coor, new);
	}
	return (door_coor);
}

t_door	**t_door_to_double_char(void)
{
	int		size;
	t_door	*door;
	t_door	**drs_states;
	int		i;

	door = doors_coordin(-1, -1);
	size = lst_size_dr(door);
	if (size <= 0)
		return (NULL);
	drs_states = gcmalloc(size * sizeof(t_door *), 0);
	i = 0;
	if (!drs_states)
		return (NULL);
	door = door->next;
	while (door && i < size)
	{
		drs_states[i] = door;
		door = door->next;
		i++;
	}
	return (drs_states);
}
