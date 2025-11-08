/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asbouani <asbouani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:28:40 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/11/08 17:29:46 by asbouani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cub3D.h"

t_config *parsser(int argc, char **argv)
{
    int fd;
    t_config    *config;
    

    config = NULL;
    if(argc == 2)
    {
        fd = open(argv[1], O_RDONLY);
        if(fd >= 0)
        {
            if(!parssing(fd))
            {
                printf("enter a valid map/config file\n");
                return(NULL);
            }
            else
            {
                config = config_struct();
                if(config)
                    fill_config_struct(argv[1], &config); 
            }
        }
        else
           printf("enter a valid map/config file\n");
    }
    else
        printf("enter a valid map/config file\n");
    return(config);
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
    {
        if(is_texture(splitted[0], identifiers) == 1)
            return(parse_texture(splitted,trimmed));
        else if(is_color(splitted[0], identifiers) == 1)
        {
            return(parse_color((trimmed + 1)));
        }
        else
            return(0);
    }
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

int parssing(int fd)
{
    t_identifiers *identifiers;
    
    identifiers = gcmalloc(sizeof(t_identifiers),0);
    if(!identifiers)
        return(0);
    identifiers->no = 0;
    identifiers->so = 0;
    identifiers->we = 0;
    identifiers->ea = 0;
    identifiers->doo = 0;
    identifiers->f = 0;
    identifiers->c = 0;
    return(parssing_core(fd, identifiers));
}