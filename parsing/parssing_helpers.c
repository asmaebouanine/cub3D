/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asbouani <asbouani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:04:29 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/10/03 15:04:43 by asbouani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int is_it_map(char *line)
{
    char *trimmed;
    
    trimmed = ft_strtrim(line, " ");
    if(!trimmed)
        return(0);
    else if(is_valid_char(trimmed[0], trimmed , 0))
        return(1);
    else
        return(0);
}


int is_identifier(char *str)
{
    if(!ft_strcmp(str,"NO") 
        || !ft_strcmp(str, "SO") 
        || !ft_strcmp(str, "WE") 
        || !ft_strcmp(str, "EA") 
        || !ft_strcmp(str,"F") 
        || !ft_strcmp(str,"C"))
            return(1);
    else
        return(0);
}

int width(int i)
{
    static int width;

    if(i< 0)
        return(width);
    else
    {
        width++;
        return(width);
    }
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
