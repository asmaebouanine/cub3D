/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asbouani <asbouani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:27:04 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/11/08 17:30:42 by asbouani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cub3D_bonus.h"

t_player *player_position(void)
{
    t_player *player_;
    player_ = gcmalloc(sizeof(t_player), 0);
    if(!player_)
        return(NULL);
    else
        return(player_);
}

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
        config->texture = gcmalloc(6 *(sizeof(char *)), 0);
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
        if(do_tex_len(-1))
        {
            config->texture[4] = gcmalloc(do_tex_len(-1) , 0);
            if(!config->texture[4])
                return(NULL);
        }
        else
            config->texture[4]= NULL;
        config->texture[5]= NULL;
        config->player =  player_position();
        if(!config->player)
            return(NULL);
    }
    return(config);
}

t_map *alloc_map(void)
{
    int     width_;
    int     len;
    t_map  *map;
    int     i;

    width_ = width(-1);
    len = lengh(-1);
    map = gcmalloc(sizeof(t_map), 0);
    if (!map)
        return (NULL);

        //add: initialize the width and the height of the map
    map->width = len;
    map->height = width_;
    map->line = gcmalloc((width_ + 1) * sizeof(char *), 0);
    if (!map->line)
        return (NULL);
    i = 0;
    while (i < width_)
    {
        map->line[i] = gcmalloc(len + 1, 0);
        if (!map->line[i])
            return (NULL);
        i++;
    }
    map->line[i] = NULL;
    return (map);
}

void fill_config_struct(char *file, t_config **config)
{
    int fd;
    char *line;
    t_player player_;
    
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
    player_ = save_coordin(-1, -1, 0);
    (*config)->player->direction = player_.direction;
    (*config)->player->x = player_.x;
    (*config)->player->y = player_.y - 1;
}
