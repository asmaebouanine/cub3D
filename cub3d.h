/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 02:53:03 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/09/12 16:46:06 by wnid-hsa         ###   ########.fr       */
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
char	*custom_strdup(const char	*s1);
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

#endif