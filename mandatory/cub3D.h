/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asbouani <asbouani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 14:40:52 by asbouani          #+#    #+#             */
/*   Updated: 2025/11/17 20:46:52 by asbouani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <stdbool.h>
# include "../mlx/mlx.h"

# define BUFFER_SIZE 1
# define SIZE 64

# define LEFT_ARROW 65363
# define RIGHT_ARROW 65361
# define W 119
# define A 97
# define S 115
# define D 100
# define ESC 65307

# define NO 0
# define WE 1
# define SO 2
# define EA 3

typedef struct s_player
{
	char	direction;
	int		size;
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	plane_x;
	double	plane_y;
	double	rot_step;
	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;
	bool	key_rot_left;
	bool	key_rot_right;
}	t_player;

typedef struct s_trash
{
	void			*point;
	struct s_trash	*next;
}	t_trash;

typedef struct s_fds
{
	int				fd;
	struct s_fds	*next;
}	t_fds;

typedef struct s_plines
{
	char	*prev;
	char	*line;
	char	*next;
}	t_plines;

typedef struct s_identifiers
{
	int	no;
	int	so;
	int	we;
	int	ea;
	int	f;
	int	c;
}	t_identifiers;

typedef struct s_color
{
	int	c_color;
	int	f_color;
}	t_color;

typedef struct s_map
{
	char	**line;
	int		height;
	int		width;
}	t_map;

typedef struct s_config
{
	char		**texture;
	t_map		*map;
	t_color		*color;
	t_player	*player;
}	t_config;

typedef struct s_ray
{
	double	ray_dx;
	double	ray_dy;
	double	delta_x;
	double	delta_y;
	double	dist_x;
	double	dist_y;
	double	wall_x;
	int		step_x;
	int		step_y;
	int		side;
	int		map_x;
	int		map_y;
	int		tex_id;
}	t_ray;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_size;
	int		endian;
}	t_texture;

typedef struct s_line
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	color;
}	t_line;

typedef struct s_convas
{
	t_texture	textures[4];
}	t_convas;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*date;
	int			endian;
	int			size_line;
	int			bits_per_pixel;
	int			win_height;
	int			win_width;
	t_player	player;
	t_config	*config;
	t_map		*map;
	t_convas	convas;
}	t_game;

typedef struct s_tex_coor
{
	double	step;
	double	tex_pos;
	int		tex_x;
	int		tex_y;
}	t_tex_coord;

double			cast_ray(t_game *game, t_player *p, t_ray *ray);
void			put_pixel(int x, int y, int color, t_game *game);
void			render_column(t_game *game, int x);
void			init_player(t_game *g);
void			move_player(t_player *p, char **map);
void			rotate_player(t_player *p, double rot_speed);
int				key_press(int keycode, t_player *player);
int				key_release(int keycode, t_player *player);

t_map			*alloc_map(void);
t_config		*config_struct(void);
t_config		*parsser(int argc, char **argv);
t_config		*parsser_core(int argc, char **argv, t_config **config);
t_plines		*padding(char *prev_line, char *next, char *line);
t_player		save_coordin(int x, int y, char direc);
t_texture		*lst_new_convas(char *path, void *mlx_ptr);
t_convas		*xmp_to_image(char **textures, void *mlx_ptr);
size_t			ft_strlen2(const char *str, char *temp);
size_t			ft_strlcpy(char *dest, const char *src, size_t size);
void			*ft_memcpy(void *dst, const void *src, size_t n);
unsigned int	get_texture_color(t_texture *tex, int x, int y);
unsigned int	apply_shading(unsigned int color);
void			*gcmalloc(size_t size, int status_flag);
void			texture_filler(char *line, t_config **config);
void			fill_config_struct(char *file, t_config **config);
void			map_filler(int fd, char *first_line, t_config **config);
void			color_filler(char *colors, t_config **config, char *ident);
void			draw_floor_and_ceiling(t_game *game, int x);
void			calc_wall(t_game *game, t_ray *ray, double dist, t_line *line);
void			wallx_call(t_game *game, t_ray *ray, double dist);
void			draw_wall(int x, t_line *line, t_game *game, t_ray *ray);
char			*return_texture(char *trimmed);
char			*filling_pad(char *line);
char			*get_next_line(int fd);
char			*ft_strdup(char *s1, char *temp);
char			*until_newline(char *rest);
char			*rest_of_line(char *temp);
char			**custom_split(const char *s, char c, int pid);
char			*ft_strtrim(const char *s1, const char *set);
char			*ft_strdup_(const char *s1);
char			*pad_line(int max, char *line);
char			*custom_strjoin(const char *s1, const char *s2, int pid);
char			*ft_strndup(const char *s1, size_t n);
char			*ft_strnstr(const char *haystack, const char *needle,
					size_t len);
int				is_valid_char(char c, char *line, int i);
int				count_words(const char *s, char c);
int				ft_strlen(const char *str);
int				ft_atoi(const char *str);
int				ft_isdigit(int c);
int				map_parssing(int fd, char *first_line);
int				is_it_map(char *line);
int				ft_strcmp(const char *s1, const char *s2);
int				space_checking(t_plines *res, int i);
int				lengh(int len);
int				width(int i);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				is_texture(char *str, t_identifiers *identifiers);
int				parse_texture(char **splitted, char *trimmed);
int				valid_texture(char *str);
int				parse_sec_text(char *str);
int				ea_tex_len(int len);
int				no_tex_len(int len);
int				so_tex_len(int len);
int				we_tex_len(int len);
int				is_color(char *str, t_identifiers *identifiers);
int				color_validation(char *color);
int				comma_count(char *color);
int				valid_color(char *colors);
int				parse_color(char *trimmed);
int				config_parsser(char *line, t_identifiers *identifiers);
int				after_map_parse(char *line);
int				parssing_core(int fd, t_identifiers *identifiers);
int				parssing(int fd);
int				max_len(char *prev_line, char *next, char *line);
int				valid_map_chars(char *line);
int				space_valid_adj(char c);
int				lineparssing(char *line, char *next, int first, int *player);
int				parse_frame(t_plines *res, int *player);
int				parse_inside(t_plines *res, int *player, int flag);
int				is_identifier(char *str);
int				save_distance(double dist);
void			color_filler(char *colors, t_config **config, char *ident);
int				parse_inside(t_plines *res, int *player, int flag);
int				parse_inside_2(t_plines *res, int *player, int flag, int *i);
int				parssing_core(int fd, t_identifiers *identifiers);
int				after_map_parse(char *line);
int				config_parsser(char *line, t_identifiers *identifiers);
int				config_parsser_2(char **splitted,
					char *trimmed, t_identifiers *identifiers);
int				is_texture(char *str, t_identifiers *identifiers);
void			gc_fds(int fd);

#endif