/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_coord.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 00:32:24 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/11/03 00:53:22 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

t_door *ft_lstnew_dr(int x, int y)
{
    t_door *new_door;

    new_door = gcmalloc(sizeof(t_door), 0);
    if(!new_door)
        return(NULL);
    new_door->door_x = x;
    new_door->door_y = y;
    new_door->state = 'c';
    new_door->next = NULL;
    return(new_door);
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
t_door *doors_coordin(int x, int y)
{
    static t_door *door_coor;
    t_door *new;
    
    if(!door_coor)
        door_coor = door_struct();
    if(x >= 0 && y >= 0)
    {
        new = ft_lstnew_dr(x, y -1);
        ft_lstadd_back_dr(&door_coor, new);
    }
    return(door_coor);
}