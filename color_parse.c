/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 09:21:06 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/09/20 09:24:17 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int parse_color(char **splitted)
{
    
    if(splitted[2])
        return(0);
    else
        return(valid_color(splitted[1]));
    
}

int valid_color(char *colors)
{
    char **splitted;
    int i;
    
    i = 0;
    if(!colors)
        return(0);
    if(!comma_count(colors))
        return(0);
    if(count_words(colors,',') != 3)
        return(0);
    splitted = custom_split(colors,',', 1);
    while(splitted[i])
    {
        if(!color_validation(splitted[i]))
            return(0);  
        i++;
    }
    return(1); 
} 
  
int comma_count(char *color)
{
    int i;
    int count;

    if(!color)
        return(0);
    i = 0;
    count = 0;
    while(color[i])
    {
        if(color[i] == ',')
            count++;
        i++;
    }
    if (count != 2)
        return(0);
    else
        return(1);
}

int color_validation(char *color)
{
    char *trimmed;
    int i;
    int numb;
    
    trimmed = ft_strtrim(color, " ");
    i = 0;
    if(!trimmed)
        return(0);
    while(trimmed[i])
    {
        if(!ft_isdigit(trimmed[i]))
            return(0);
        i++;
    }
    numb = ft_atoi(trimmed);
    if(numb <0 || numb >255)
        return(0);
    else
        return(1);
}
int is_color(char *str, t_identifiers *identifiers)
{
   if(!ft_strcmp(str,"F") || !ft_strcmp(str,"C"))
   {
        if(!ft_strcmp(str,"F"))
            identifiers->f++;
        else if(!ft_strcmp(str,"C"))
            identifiers->c++;
        if(identifiers->f > 1 || identifiers->c > 1)
            return(0);
        return(1);
   }
    return(0);
}