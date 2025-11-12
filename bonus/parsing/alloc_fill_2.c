/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_fill_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 09:33:55 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/11/12 00:27:16 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void color_filler(char *colors, t_config **config, char *ident)
{
    char **splitted;
    int color;
    int i;
    
    i = 0;
    splitted = custom_split(colors,',', 1);
    if(!splitted[0] || !splitted[1] || !splitted[2])
        return;
    color = (ft_atoi(splitted[0]) << 16 
                    | ft_atoi(splitted[1]) << 8 | ft_atoi(splitted[2]));
    if(!ft_strcmp(ident, "F"))
        (*config)->color->f_color = color;
    else if(!ft_strcmp(ident, "C"))
        (*config)->color->c_color = color;
}

char *filling_pad(char *line)
{
    int max;
    char *str;
    char *trim;
    
    max = lengh(-1);
    trim = ft_strtrim(line,"\n");
    if(!trim)
        return(NULL);
    str = pad_line(max, trim);
    return(str);
}

void map_filler(int fd, char *first_line, t_config **config)
{
    char *line;
    char *str;
    int   i;
    
    line = first_line;
    if (!line)
        return;
    i = 0;
    while(is_it_map(line))
    {
        str = filling_pad(line);
        if(!str)
            return;
        (*config)->map->line[i] = str;
        i++;
        line = get_next_line(fd);
    }
}

char *return_texture(char * trimmed)
{
    int i;
    char *str;

    i = 0;
    str = trimmed + 2;
    if(!str)
        return(NULL);
    else
    {
        while(str[i] == ' ')
        {
            i++;
        }
        return(ft_strdup_(str + i));
    }
    return(NULL); 
}
void texture_filling(char **splitted,char *trimmed, t_config **config)
{
    if(!ft_strcmp(splitted[0], "NO"))
        (*config)->texture[NO] = return_texture(trimmed);
    else if(!ft_strcmp(splitted[0], "WE"))
        (*config)->texture[WE] = return_texture(trimmed);
    else if(!ft_strcmp(splitted[0], "SO"))
        (*config)->texture[SO] = return_texture(trimmed);
    else if(!ft_strcmp(splitted[0], "EA"))
        (*config)->texture[EA] = return_texture(trimmed);
    else if(!ft_strcmp(splitted[0], "DO"))
        (*config)->texture[DO] = return_texture(trimmed);
    else
    {
        if(!(trimmed +1))
            return;
        color_filler(trimmed + 1, config, splitted[0]);
    }
}
void texture_filler(char *line, t_config **config)
{
    char **splitted;
    char *trimmed;

    if(!line)
        return;
    trimmed = ft_strtrim(line,"  \n");
    if(!trimmed)
        return;
    else if(!ft_strcmp(trimmed,""))
        return;
    splitted = custom_split(trimmed, ' ', 1);
    if(splitted && is_identifier(splitted[0]) == 1)
        texture_filling(splitted,trimmed, config);
}