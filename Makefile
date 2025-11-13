# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/14 14:59:01 by asbouani          #+#    #+#              #
#    Updated: 2025/11/13 11:55:18 by wnid-hsa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc

CFLAGS = -Wall -Wextra -Werror -Imlx #-fsanitize=address

MLX = -Lmlx -lmlx -lX11 -lXext -lm

HEADER = mandatory/cub3D.h

HEADER_B = bonus/cub3D_bonus.h

SRCS = mandatory/raycasting/cub3D.c mandatory/raycasting/move_player.c mandatory/raycasting/cast_ray.c mandatory/raycasting/ray_rander.c mandatory/raycasting/init_player.c \
		mandatory/parsing/get_next_line.c mandatory/parsing/get_next_line_utils.c mandatory/parsing/cleaning.c mandatory/parsing/map_parssing.c mandatory/parsing/custom_func.c mandatory/parsing/custom_split.c mandatory/parsing/parssing_helpers.c \
		mandatory/parsing/helpers.c mandatory/parsing/custom_strjoin.c mandatory/parsing/texture_parse.c mandatory/parsing/parssing.c mandatory/parsing/parssing_lengh.c mandatory/parsing/map_parssing_2.c mandatory/parsing/color_parse.c \
		mandatory/parsing/alloc_fill.c mandatory/parsing/alloc_fill_2.c mandatory/texturing/xmp_to_image.c mandatory/texturing/texturing_tiles.c mandatory/texturing/texturing_helpers.c mandatory/parsing/alloc_fill_3.c \
		mandatory/parsing/parsing_core.c mandatory/parsing/parse_inside.c
	
		
SRCS_B = bonus/raycasting/cub3D.c bonus/raycasting/move_player.c bonus/raycasting/cast_ray.c bonus/raycasting/ray_rander.c bonus/raycasting/init_player.c bonus/raycasting/mouse_control_b.c  bonus/raycasting/door_handling_b.c bonus/raycasting/collision_check_b.c \
		bonus/parsing/get_next_line.c bonus/parsing/get_next_line_utils.c bonus/parsing/cleaning.c bonus/parsing/map_parssing.c bonus/parsing/custom_func.c bonus/parsing/custom_split.c bonus/parsing/parssing_helpers.c \
		bonus/parsing/helpers.c bonus/parsing/custom_strjoin.c bonus/parsing/texture_parse.c bonus/parsing/parssing.c bonus/parsing/parssing_lengh.c bonus/parsing/map_parssing_2.c bonus/parsing/color_parse.c \
		bonus/parsing/map_parssing_3.c bonus/parsing/alloc_fill.c bonus/parsing/alloc_fill_2.c bonus/texturing/xmp_to_image.c bonus/texturing/texturing_tiles.c bonus/texturing/texturing_helpers.c \
		bonus/parsing/door_coord.c bonus/animations/xpm_to_img_anim.c bonus/raycasting/minimap_b.c bonus/parsing/alloc_fill_3.c bonus/parsing/parse_inside.c bonus/parsing/parssing_core.c

OBJCS = $(SRCS:.c=.o)

OBJCS_B = $(SRCS_B:.c=.o)

all: $(NAME)

mandatory/%.o: mandatory/%.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@
	
bonus/%.o: bonus/%.c $(HEADER_B)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJCS)
	$(CC) $(CFLAGS) $(OBJCS) $(MLX) -o $(NAME)

bonus: $(OBJCS_B)
	$(CC) $(CFLAGS) $(OBJCS_B) $(MLX) -o $(NAME)

clean: 
	rm -f $(OBJCS) $(OBJCS_B)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean

