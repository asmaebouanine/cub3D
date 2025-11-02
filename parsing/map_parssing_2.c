/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parssing_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:28:11 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/11/02 17:28:15 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int space_valid_adj(char c)
{
    if(c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
        return(0);
    else
        return(1);
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