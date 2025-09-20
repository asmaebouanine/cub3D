/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 09:28:03 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/09/20 10:55:44 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_config *config_struct(void)
{
    t_config    *config;
    
    config = gcmalloc(sizeof(t_config), 0);
    if (!config)
        return(NULL);
    else
    {
       config->map = alloc_map();
        if(!config->map)
            return(NULL);
        config->color = gcmalloc(sizeof(t_color), 0);
        if(!config->color)
            return(NULL);
        config->texture = gcmalloc(5 *(sizeof(char *)), 0);
        if(!config->texture)
            return(NULL);
        config->texture[0] = gcmalloc(no_tex_len(-1), 0);
        if(!config->texture[0])
            return(NULL);
        config->texture[1] = gcmalloc(we_tex_len(-1) , 0);
        if(!config->texture[1])
            return(NULL);
        config->texture[2] = gcmalloc(so_tex_len(-1), 0);
        if(!config->texture[2])
            return(NULL);
        config->texture[3] = gcmalloc(ea_tex_len(-1) , 0);
        if(!config->texture[3])
            return(NULL);
        config->texture[4]= NULL;
    }
    return(config);
}

t_map  *alloc_map(void)
{
    int     width_;
    int     len;
    t_map  *map;
    int     i;
    
    width_ = width(-1);
    len = lengh(-1);
    map = gcmalloc(sizeof(t_map), 0);
    if(!map)
        return(NULL);
    map->line = gcmalloc((width_ + 1)*sizeof(char *), 0);
    if(!map->line)
        return(NULL);
    i = 0;
    while(i < width_)
    {
        map->line[i] = gcmalloc(len -1, 0);
        i++;
    }
    map->line[i] = NULL;
    return(map);
}

void fill_config_struct(char *file, t_config **config)
{
    int fd;
    char *line;
    
    if(!file)
        return;
    fd = open(file, O_RDONLY);
    if(fd<0)
        return;
    line = get_next_line(fd);
    if (!line)
        return;
    while(!is_it_map(line))
    {
        texture_filler(line, config);
        line = get_next_line(fd);
    }
    map_filler(fd, line, config);
}