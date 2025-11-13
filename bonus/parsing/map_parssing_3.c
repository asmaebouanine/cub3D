/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parssing_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 19:02:37 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/11/13 11:48:58 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

int do_tex_len(int len)
{
    static int doo;
    
    if(len >0)
    {
        doo = len;
    }
    return(doo);
}

int vertical_checking(t_plines *res, int i)
{
    bool behind;
    bool front;

    behind = (res->line 
                    &&(i + 1 < ft_strlen(res->line))
                         &&(res->line[i+1] == '1'));
    front = ( res->line 
            &&(i - 1 >= 0) 
            && res->line[i-1] == '1');
    if(behind && front)
        return(1);
    else
        return(0);
}

int horizontal_checking(t_plines *res, int i)
{
    bool top;
    bool bottom;

    top = (res->prev && i < ft_strlen(res->prev) && res->prev[i] == '1');
    bottom = (res->next && i < ft_strlen(res->next) &&res->next[i] == '1');
    if(top && bottom )
        return(1);
    else
        return(0);
    
}

int door_checking(t_plines *res, int i)
{
    if(!res)
        return(0);
    if(horizontal_checking(res, i) && vertical_checking(res,i))
        return(0);
    else if(!horizontal_checking(res, i) && !vertical_checking(res,i))
        return(0);
    else
        return(1);
}

t_door *door_struct(void)
{
    t_door *door_coor;

    door_coor =  gcmalloc(sizeof(t_door), 0);
    if(!door_coor)
        return(NULL);
    else
    {
        door_coor->door_x = -1;
        door_coor->door_y = -1;
        door_coor->state = '\0';
        door_coor->next = NULL;
    }
    return(door_coor);
}