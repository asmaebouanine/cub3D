/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 09:11:10 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/09/21 16:44:30 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_texture(char *str, t_identifiers *identifiers)
{
    if(!ft_strcmp(str,"NO") 
        || !ft_strcmp(str, "SO") 
        || !ft_strcmp(str, "WE") 
        || !ft_strcmp(str, "EA"))
    {
        if(!ft_strcmp(str, "NO"))
            identifiers->no++;
        else if(!ft_strcmp(str, "SO"))
            identifiers->so++;
        else if(!ft_strcmp(str, "WE"))
            identifiers->we++;
        else if(!ft_strcmp(str, "EA"))
            identifiers->ea++;
        if(identifiers->no > 1 || identifiers->so > 1 ||  identifiers->we > 1 || identifiers->ea > 1)
            return(0);
        return(1);
    }
    else
        return(0);
}

int parse_sec_text(char *str)
{
    int i;

    i = 0;
    if(!str)
        return(0);
    while(str[i] == ' ')
    {
        i++;
    }
    if(!ft_strcmp(str+i, ".xpm"))
        return(1);
    else
        return(0);
}

int valid_texture(char *str) 
{
    int len;
    char *path;
    char *rest;
    char **splitted;
    int fd;
    
    len = ft_strlen(str);
    if(!len)
        return(0);
    rest = ft_strnstr(str, ".xpm", len);
    if(!rest)
        return(0);
    splitted = custom_split(rest,' ', 0);
    if(!splitted || !splitted[0] ||splitted[1])
        return(0);
    else
        path = ft_strtrim(str, " \n");
    if(!path)
        return(0);
    len = ft_strlen(path);
    if (len < 4)
        return (0);
    fd = open(path, O_RDONLY);
    if(fd < 0)
        return(0);
    else
        return(len);
}

int parse_texture(char **splitted, char *trimmed)
{
    int i;
    char *str;
    int len;

    i = 0;
    if(!splitted[0] || !splitted[1])
        return(0);
    str = trimmed + 2;
    if(!str)
        return(0);
    else
    {
        while(str[i] == ' ')
        {
            i++;
        }
        len = valid_texture(str + i);
        if(len)
        {
            if(!ft_strcmp(splitted[0], "NO"))
                no_tex_len(len);
            else if(!ft_strcmp(splitted[0], "WE"))
                we_tex_len(len);
            else if(!ft_strcmp(splitted[0], "SO"))
                so_tex_len(len);
            else if(!ft_strcmp(splitted[0], "EA"))
                ea_tex_len(len);
            return(1);
        } 
    }
    return(0); 
}