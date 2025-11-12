/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:27:04 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/11/11 17:58:20 by wnid-hsa         ###   ########.fr       */
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
void anims(char **anim)
{
    anim[0] = custom_strdup("./weapons/weapon_0.xpm", 0);
    anim[1] = custom_strdup("./weapons/weapon_1.xpm", 0);
    anim[2] = custom_strdup("./weapons/weapon_2.xpm", 0);
    anim[3] = custom_strdup("./weapons/weapon_3.xpm", 0);
    anim[4] = custom_strdup("./weapons/weapon_4.xpm", 0);
    anim[5] = custom_strdup("./weapons/weapon_5.xpm", 0);
    anim[6] = custom_strdup("./weapons/weapon_6.xpm", 0);
    anim[7] = custom_strdup("./weapons/weapon_7.xpm", 0);
    anim[8] = custom_strdup("./weapons/weapon_8.xpm", 0);
    anim[9] = custom_strdup("./weapons/weapon_9.xpm", 0);
    anim[10] = custom_strdup("./weapons/weapon_10.xpm", 0);
    anim[11] = custom_strdup("./weapons/weapon_11.xpm", 0);
    anim[12] = custom_strdup("./weapons/weapon_12.xpm", 0);
    anim[13] = custom_strdup("./weapons/weapon_13.xpm", 0);
    anim[14] = custom_strdup("./weapons/weapon_14.xpm", 0);
    anim[15] = custom_strdup("./weapons/weapon_15.xpm", 0);
    anim[16] = custom_strdup("./weapons/weapon_16.xpm", 0);
    anim[17] = custom_strdup("./weapons/weapon_17.xpm", 0);
    anim[18] = custom_strdup("./weapons/weapon_18.xpm", 0);
    anim[19] = custom_strdup("./weapons/weapon_19.xpm", 0);
    anim[20] = custom_strdup("./weapons/weapon_20.xpm", 0);
    anim[21] = custom_strdup("./weapons/weapon_21.xpm", 0);
    anim[22] = custom_strdup("./weapons/weapon_22.xpm", 0);
    anim[23] = custom_strdup("./weapons/weapon_23.xpm", 0);
}

char **anim_alloc(void)
{
    char **anim;
    int i;
    
    anim = gcmalloc(25 *(sizeof(char *)), 0);
    if(!anim)
        return(NULL);
    anims(anim);
    i = 0;
    while(i < 24)
    {
        if(!anim[i])
            return(NULL);
        i++;
    }
    anim[24] = NULL;
    return(anim);
}
void fill_map_tex(t_config    **config)
{
    (*config)->map = alloc_map();
    if(!((*config)->map))
            return;
    (*config)->color = gcmalloc(sizeof(t_color), 0);
    if(!((*config)->color))
        return;
   (*config)->texture = gcmalloc(6 *(sizeof(char *)), 0);
    if(!((*config)->texture))
        return;
    (*config)->texture[0] = gcmalloc(no_tex_len(-1), 0);
    if(!((*config)->texture[0]))
        return;
    (*config)->texture[1] = gcmalloc(we_tex_len(-1) , 0);
    if(!((*config)->texture[1]))
        return;
    (*config)->texture[2] = gcmalloc(so_tex_len(-1), 0);
    if(!((*config)->texture[2]))
        return;
    (*config)->texture[3] = gcmalloc(ea_tex_len(-1) , 0);
    if(!((*config)->texture[3]))
        return;
}
t_config *config_struct(void)
{
    t_config    *config;
    
    config = gcmalloc(sizeof(t_config), 0);
    if(config)
    {
        fill_map_tex(&config);
        if(!config->map ||!config->color || !config->texture 
            ||!config->texture[0] || !config->texture[1] 
            || !config->texture[2] ||!config->texture[3] )
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
        config->anim = anim_alloc();
        if(!config->player || !config->anim)
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
