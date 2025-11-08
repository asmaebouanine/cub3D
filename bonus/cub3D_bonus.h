/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asbouani <asbouani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:18:41 by asbouani          #+#    #+#             */
/*   Updated: 2025/11/08 16:20:52 by asbouani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
#define CUB3D_BONUS_H

#define TILE_SIZE 20
#define VIEW_SIZE 10

#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "../mlx/mlx.h"

#define BUFFER_SIZE 1

#define TILE_SIZE 20
#define VIEW_SIZE 10 
#define SIZE 64

#define WIDTH 1280
#define HEIGHT 720

#define LEFT_ARROW 65363
#define RIGHT_ARROW 65361
#define W 119
#define A 97
#define S 115
#define D 100
#define X 120
#define ESC 65307


# define NO 0
# define WE 1
# define SO 2
# define EA 3
# define DO 4

typedef struct s_player
{
  char direction;
  int size;
  double x;
  double y;
  double dx;
  double dy;
  double plane_x;
  double plane_y;
  bool key_up;
  bool key_down;
  bool key_left;
  bool key_right;
  bool key_rot_left;
  bool key_rot_right;
  double rot_step;
} t_player;


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
    int doo;
    int f;
    int c;
}          t_identifiers;


typedef struct s_color
{
    int             c_color;
    int             f_color;
}   t_color;


typedef struct s_map
{
    char        **line;
    int         height;
    int         width;
}  t_map;

typedef struct s_config
{
    char   **texture;
    t_color     *color;
    t_map       *map;
    t_player    *player;
} t_config;

typedef struct s_door
{
    int door_x;
    int door_y;
    char state;
    struct s_door *next;
} t_door;

typedef struct s_ray
{
    double ray_dx;
    double ray_dy;
    double delta_x;
    double delta_y;
    double dist_x;
    double dist_y;
    int step_x;
    int step_y;
    int side;
    int map_x;
    int map_y;
    int tex_id;
    int type;
    double  wallX;
} t_ray;

typedef struct s_texture
{
    void    *img;
    char    *addr;
    int     width;
    int     height;
    int     bpp;
    int     line_size;
    int     endian;
} t_texture;

typedef struct s_line
{
    int line_height;
    int draw_start;
    int draw_end;
    int color;
    
} t_line;


typedef struct s_convas
{
    t_texture  textures[5];
    
} t_convas;

typedef struct s_game
{
  int   win_height;
  int   win_width;
  void  *mlx;
  void  *win;
  void  *img;
  char  *date;
  int   endian;
  int   size_line;
  int   bits_per_pixel;
  t_player player;
  t_config *config;
  t_map *map;
  t_convas convas;
  t_door **doors;
} t_game;


void    minimap(t_game *game);
int     mouse_move(int x, int y, t_game *game);

double  cast_ray(t_game *game, t_player *p,t_ray *ray);
void    put_pixel(int x, int y, int color, t_game *game);
void    render_column(t_game *game, int x);
void    init_player(t_game *g);
void	move_player(t_game *game, char **map);
void	rotate_player(t_player *p, double rot_speed);
int     key_press(int keycode, t_game *game);
int     key_release(int keycode, t_game *game);

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
int     parse_color(char *trimmed);
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
int     parse_inside(t_plines  *res, int *player, int flag);
char    *pad_line(int max, char *line);
int     parse_frame(t_plines *res, int *player);
t_plines *padding(char *prev_line, char *next, char *line);
int     is_identifier(char *str);
t_player save_coordin(int x, int y, char direc);
t_texture  *lst_new_convas(char *path, void *mlx_ptr);
t_convas *xmp_to_image(char **textures, void *mlx_ptr);
void    draw_wall(int x, t_line *line, t_game *game, t_ray *ray, double dist);
void    draw_floor_and_ceiling(t_game *game, int x);
void    calc_wall(t_game *game, t_ray *ray, double dist, t_line *line);
void    wallx_call(t_game *game, t_ray *ray, double dist);
unsigned int get_texture_color(t_texture *tex, int x, int y);
unsigned int apply_shading(unsigned int color, double dist);
int     door_checking(t_plines *res, int i);
t_door *doors_coordin(int x, int y);
t_door *door_struct(void);
int do_tex_len(int len);
t_door **t_door_to_double_char(void);
int find_cooresp_dr(t_game *game, int map_y, int map_x);

#endif