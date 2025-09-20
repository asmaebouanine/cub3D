/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 02:53:03 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/09/20 10:53:38 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define BUFFER_SIZE 1

typedef struct s_trash
{
	void			*point;
	struct s_trash	*next;
}					t_trash;

typedef struct s_plines
{
	char	*prev;
	char	*line;
	char	*next;
}				t_plines;

typedef struct s_identifiers
{
    int no;
    int so;
    int we;
    int ea;
    int f;
    int c;
} t_identifiers;


typedef struct s_color
{
    int             c_color;
    int             f_color;
}   t_color;

typedef struct s_map
{
    char        **line;
    int         heigh;
    int         width;
}  t_map;

typedef struct s_config
{
    
    char   **texture;
    t_color     *color;
    t_map       *map;
} t_config;


int	    ft_strlen(const char *str);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*gcmalloc(size_t size, int status_flag);
char	*get_next_line(int fd);
char	*ft_strdup(char *s1, char *temp);
char	*until_newline(char *rest);
char	*rest_of_line(char *temp);
void	*ft_memcpy(void *dst, const void *src, size_t n);
size_t	ft_strlen2(const char *str, char *temp);
int     is_valid_char(char c, char *line, int i);
char	*ft_strtrim(const char *s1, const char *set);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	**custom_split(const char *s, char c, int pid);
int	    count_words(const char *s, char c);
int	    ft_atoi(const char *str);
int	    ft_isdigit(int c);
int     map_parssing(int fd, char *first_line);
int     is_it_map(char *line);
int     ft_strcmp(const char *s1, const char *s2);
int     space_checking(t_plines *res, int i);
int     lengh(int len);
int     width(int i);
char	*ft_strdup_(const char *s1);
char    *pad_line(int max, char *line);
char	*custom_strjoin(const char *s1, const char *s2, int pid);
char	*ft_strndup(const char *s1, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int	    ft_strncmp(const char *s1, const char *s2, size_t n);
int     is_texture(char *str, t_identifiers *identifiers);
int     parse_texture(char **splitted, char *trimmed);
int     valid_texture(char *str);
int     parse_sec_text(char *str);
int     ea_tex_len(int len);
int     no_tex_len(int len);
int     so_tex_len(int len);
int     we_tex_len(int len);
int     is_color(char *str, t_identifiers *identifiers);
int     color_validation(char *color);
int     comma_count(char *color);
int     valid_color(char *colors);
int     parse_color(char **splitted);
void    fill_config_struct(char *file, t_config **config);
void    texture_filler(char *line, t_config **config);
t_map  *alloc_map(void);
t_config *config_struct(void);
void    texture_filler(char *line, t_config **config);
char    *return_texture(char * trimmed);
void    map_filler(int fd, char *first_line, t_config **config);
char    *filling_pad(char *line);
void    color_filler(char *colors, t_config **config, char *ident);
t_config *parsser(int argc, char **argv);
int     config_parsser(char *line, t_identifiers *identifiers);
int     after_map_parse(char *line);
int     parssing_core(int fd, t_identifiers *identifiers);
int     parssing(int fd);
int     space_checking(t_plines *res, int i);
int     max_len(char *prev_line, char *next, char *line);
int     valid_map_chars(char *line);
int     is_valid_char(char c, char *line, int i);
int     space_valid_adj(char c);
int     map_parssing(int fd, char *first_line);
int     lineparssing(char *line, char *next, int first, int *player);
int     parse_inside(t_plines  *res, int *player);
char    *pad_line(int max, char *line);
int     parse_frame(t_plines *res, int *player);
t_plines *padding(char *prev_line, char *next, char *line);
int     is_identifier(char *str);

#endif