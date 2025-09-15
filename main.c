/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:04:29 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/09/12 18:22:43 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_it_map(char *line)
{
    char *trimmed;
    
    trimmed = ft_strtrim(line, " ");
    if(!trimmed)
        return(0);
    else if(is_valid_char(trimmed[0], line , 0))
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
 int valid_texture(const char *path) 
 {
    int len;
    int fd;
    
    if(!path)
    return(0);
    len = ft_strlen(path);
    if (len < 4)
        return (0);
    if(ft_strcmp(path + len -4, ".xpm"))
        return(0);
    else
    {
        fd = open(path, O_RDONLY);
        if(fd < 0)
            return(0);
        else
            return(1);
    }
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

int no_tex_len(int len)
{
    static int no;
    
    if(len >0)
    {
        no = len;
    }
    return(no);
}

int we_tex_len(int len)
{
    static int we;
    
    if(len >0)
    {
        we = len;
    }
    return(we);
}

int so_tex_len(int len)
{
    static int so;
    
    if(len >0)
    {
        so = len;
    }
    return(so);
}

int ea_tex_len(int len)
{
    static int ea;
    
    if(len >0)
    {
        ea = len;
    }
    return(ea);
}

int parse_texture(char **splitted)
{
    int i;

    i = 1;
    if(splitted[2])
        return(0);  
    else
    {
        if(!splitted[0] || !splitted[1])
            return(0);
        if(!ft_strcmp(splitted[0], "NO"))
            no_tex_len(ft_strlen(splitted[1]));
        else if(!ft_strcmp(splitted[0], "WE"))
            we_tex_len(ft_strlen(splitted[1]));
        else if(!ft_strcmp(splitted[0], "SO"))
            so_tex_len(ft_strlen(splitted[1]));
        else if(!ft_strcmp(splitted[0], "EA"))
            ea_tex_len(ft_strlen(splitted[1]));
        return(valid_texture(splitted[1]));
    }
}

int parse_color(char **splitted)
{
    
    if(splitted[2])
        return(0);
    else
        return(valid_color(splitted[1]));
    
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
            return(parse_texture(splitted));
        else if(is_color(splitted[0], identifiers) == 1)
            return(parse_color(splitted));
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
    identifiers->f = 0;
    identifiers->c = 0;
    return(parssing_core(fd, identifiers));
}

int  lengh(int len)
{
    static int llen;

    if(len > llen)
    {
        llen = len;
    }
    return(llen); 
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

void color_filler(char *colors, t_config **config, char *ident)
{
    char **splitted;
    int color;
    int i;
    
    i = 0;
    splitted = custom_split(colors,',', 1);
    color = (ft_atoi(splitted[0]) << 16 | ft_atoi(splitted[1]) << 8 | ft_atoi(splitted[2]));
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
    if(!splitted)
        return;
    if(is_identifier(splitted[0]) == 1)
    {
        if(!ft_strcmp(splitted[0], "NO"))
           (*config)->texture[0] = ft_strdup_(splitted[1]);
        else if(!ft_strcmp(splitted[0], "WE"))
            (*config)->texture[1] = ft_strdup_(splitted[1]);
        else if(!ft_strcmp(splitted[0], "SO"))
            (*config)->texture[2] = ft_strdup_(splitted[1]);
        else if(!ft_strcmp(splitted[0], "EA"))
           (*config)->texture[3] = ft_strdup_(splitted[1]);
        else
            color_filler(splitted[1], config, splitted[0]);
    }
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

int main(int argc, char **argv)
{
    t_config    *config;

    config = parsser(argc, argv);
    if(!config)
        return(0);
        
}