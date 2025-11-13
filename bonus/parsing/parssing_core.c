/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_core.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 11:02:21 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/11/13 11:48:58 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"


int config_parsser_2(char **splitted,char *trimmed, t_identifiers *identifiers)
{
     if(is_texture(splitted[0], identifiers) == 1)
        return(parse_texture(splitted,trimmed));
    else if(is_color(splitted[0], identifiers) == 1)
        return(parse_color((trimmed + 1)));
    else
        return(0);
} 

int config_parsser(char *line, t_identifiers *identifiers)
{
    char **splitted;
    char *trimmed;

    if(!line)
        return(0);
    trimmed = ft_strtrim(line,"  \n");
    if(!trimmed)
        return(0);
    else if(!ft_strcmp(trimmed,""))
        return(1);
    splitted = custom_split(trimmed, ' ', 1);
    if(!splitted)
        return(0);
    if(is_identifier(splitted[0]) == 0)
    return(0); 
    else
        return(config_parsser_2(splitted,trimmed, identifiers));
}

int after_map_parse(char *line)
{
    int i;

    i = 0;
    if(!line)
        return(1);
    while(line[i])
    {
        if(line[i]!= ' ' && line[i] !='\n')
            return(0);
        i++;
    }
    return(1);
}

int parssing_core(int fd, t_identifiers *identifiers)
{
    char *line;
    
    line = get_next_line(fd);
    if (!line)
        return(0);
    while(!is_it_map(line))
    {
        if(!config_parsser(line, identifiers))
            return(0);
        line = get_next_line(fd);
    }
    if(!identifiers->no || !identifiers->so 
        || !identifiers->we || !identifiers->ea 
        || !identifiers->f || !identifiers->c)
        return(0);
    if(!map_parssing(fd, line))
        return(0);
    line = get_next_line(fd);
    while(line)
    {
        if(!after_map_parse(line))
            return(0);
        line = get_next_line(fd);
    }
    return(1);
}

