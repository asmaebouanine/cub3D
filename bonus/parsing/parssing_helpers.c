/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:28:26 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/11/11 22:35:31 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cub3D_bonus.h"

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
        || !ft_strcmp(str,"C")
        || !ft_strcmp(str, "DO"))
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
   
   
   max = max_len(ft_strtrim(prev_line, "\n"),
                        ft_strtrim(next, "\n") , ft_strtrim(line, "\n"));
   (void)lengh(max);
   res = gcmalloc(sizeof(t_plines),1);
   if(!res)
        return(NULL);
    res->prev = pad_line(max,ft_strtrim(prev_line, "\n"));
    res->line = pad_line(max, ft_strtrim(line, "\n"));
    res->next = pad_line(max,ft_strtrim(next, "\n"));
   return(res);  
}
