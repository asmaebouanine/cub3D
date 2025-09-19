/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asbouani <asbouani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 14:40:52 by asbouani          #+#    #+#             */
/*   Updated: 2025/09/19 14:28:44 by asbouani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "mlx/mlx.h"

#define BUFFER_SIZE 1

#define WIDTH  1280
#define HEIGHT 720

#define SIZE 80
// #define BLOCK 80

#define W 119
#define A 97
#define S 115
#define D 100

typedef struct s_trash
{
	void			*point;
	struct s_trash	*next;
}	t_trash;

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

typedef struct s_player
{
  float x;
  float y;
  bool key_up;
  bool key_down;
  bool key_left;
  bool key_right;
} t_player;

typedef struct s_game
{
  char  **map;
  void  *mlx;
  void  *win;
  void  *img;
  char  *date;
  int   endian;
  int   size_line;
  int   bits_per_pixel;
  t_player player;
  t_config *config;
}   t_game;

t_config *parsser(int argc, char **argv);
int   ft_strlen(const char *str);
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


void  init_player(t_player *player);
void  move_player(t_player *player);
int   key_press(int keycode, t_player *player);
int   key_release(int keycode, t_player *player);

#endif



