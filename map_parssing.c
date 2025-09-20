/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parssing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:18:14 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/09/20 12:33:15 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int parse_frame(t_plines *res, int *player)
{
    int i;

    if(!res || !res->line)
        return(0);
    i = 0;
    (void)player;
    while((res->line)[i] && res->line[i] != '\n')
    {
        if((res->line)[i] != '1' && (res->line)[i] != ' ')
            return(-1);
        else if((res->line)[i] == ' ' && !space_checking(res, i))
            return(-1);
        i++;
    }
    return(1);
}


char *pad_line(int max, char *line)
{
    int len;
    char  *padded;

    len = ft_strlen(line);
    if(len == max)
        return(line);
    padded = gcmalloc(max + 1 , 1);
    if(!padded)
        return(NULL);
    if(line)
        ft_strlcpy(padded, line, len + 1);
    while(len  < max)
    {
        padded[len]=' ';
        len++;
    }
    padded[len] = '\0';
    return(padded);
}
t_player save_coordin(int x, int y, char c)
{
    static t_player player;
    if(x >=0 && y >= 0)
    {
        player.direction = c;
        player.x = x;
        player.y = y;
    }
    return(player);
}
int parse_inside(t_plines  *res, int *player, int flag)
{
    int i;
    size_t len;
    
    if(!res)
        return(-1);
    i = 0;
    len = ft_strlen(res->line);
    if(!len || !valid_map_chars(res->line))
        return(-1);
    while( res->line[i] && res->line[i] == ' ' && res->line[i] != '\n')
    {
        if(!space_checking(res, i))
            return(-1);
        i++;
    }
    if(res->line[i]!= '1')
        return(-1);
    while(res->line[i] && res->line[i]!= '\n')
    {
        if(res->line[i] == ' ')
        {
            if(!space_checking(res, i))
                return(-1);
        }   
        if(res->line[i] == 'N' || res->line[i] == 'S' || res->line[i] == 'E' || res->line[i] == 'W')
        {
            save_coordin(i, flag, res->line[i]);
            (*player)++;
        }
        i++;
    }
    if(i-1 >=0 && res->line[i-1] != '1')
        return(-1);
    return(1);
}

int lineparssing(char *line, char *next, int first, int *player)
{
    static char     *prev_line;
    t_plines        *res;
    
    res = padding(prev_line, next, line);
    if(!res)
        return(0);
    prev_line = res->line;
    if(!next || first == 1)
        return(parse_frame(res, player));
    else
        return(parse_inside(res, player, first));
    return(1);
}
 
    
int map_parssing(int fd, char *first_line)
{
    char *line;
    char *next;
    int  flag;
    static int player;
    
    line = first_line;
    if (!line)
        return(0);
    flag = 0;
    while(is_it_map(line))
    {
        (void)width(0);
        next = get_next_line(fd);
        flag++;
        if(lineparssing(line, next, flag, &player) == -1)
        {
            return(0);
        }
        line = next;
    }
    if(player != 1)
        return(0);
    return(1);
}
