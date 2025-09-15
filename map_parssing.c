/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parssing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:18:14 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/09/12 17:50:58 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_strlen(const char *str)
{
    int i;

    i = 0;
    if (!str)
        return(0);
    while(str[i])
    {
        i++;
    }
    return(i); 
}

int is_valid_char(char c, char *line, int i)
{
    if(c == '0' || c == '1' || (( i+1 < ft_strlen(line)) 
            && (c == 'N' || c == 'S') && line[i+1] != 'O')  
            || (c == 'E' && ( i+1 < ft_strlen(line))&& line[i+1] != 'A')
            ||( c == 'W' && ( i+1 < ft_strlen(line))&& line[i+1] != 'E') 
            || c == ' ')
        return (1);
    else
        return (0);
}

int valid_map_chars(char *line)
{
    int i;
    
    i = 0;
    while(line[i] && line[i] !='\n')
    {
        if(!is_valid_char(line[i], line, i))
            return(0);
        i++;
    }
    return(1);
}

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

int max_len(char *prev_line, char *next, char *line)
{
    int plen;
    int nlen;
    int llen;

    plen = ft_strlen(prev_line);
    nlen = ft_strlen(next);
    llen = ft_strlen(line);
    
    if(plen >= nlen && plen >= llen)
        return(plen);
    else if(nlen >= llen)
        return(nlen);
    return(llen);
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

t_plines *padding(char *prev_line, char *next, char *line)
{
   int max;
   t_plines *res;
   
   
   max = max_len(prev_line, next, line);
   (void)lengh(max);
   res = gcmalloc(sizeof(t_plines),1);
   if(!res)
        return(NULL);
    res->prev = pad_line(max,prev_line);
    res->line = pad_line(max, line);
    res->next = pad_line(max, next);
   return(res);  
}

int space_valid_adj(char c)
{
    if(c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
        return(0);
    else
        return(1);
}

int space_checking(t_plines *res, int i)
{
  
    if(( res->line && (i + 1 < ft_strlen(res->line))
        &&(!space_valid_adj(res->line[i+1]))) 
        || (res->line && (i - 1 >= 0) && !space_valid_adj(res->line[i-1]))
        || ( res->prev && !space_valid_adj(res->prev[i]))
        || ( res->next && !space_valid_adj(res->next[i])))
            return(0);
    else
        return(1);
    
}

int parse_inside(t_plines  *res, int *player)
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
            (*player)++;
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
        return(parse_inside(res, player));
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
