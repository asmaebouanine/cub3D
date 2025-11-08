# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asbouani <asbouani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/14 14:59:01 by asbouani          #+#    #+#              #
#    Updated: 2025/11/08 17:36:10 by asbouani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc

CFLAGS = -Wall -Wextra -Werror -Imlx  -fsanitize=address

MLX = -Lmlx -lmlx -lX11 -lXext -lm

HEADER = mandatory/cub3D.h

HEADER_B = mandatory/cub3D_mandatory.h

SRCS = mandatory/raycasting/cub3D.c mandatory/raycasting/move_player.c mandatory/raycasting/cast_ray.c mandatory/raycasting/ray_rander.c mandatory/raycasting/init_player.c \
		mandatory/parsing/get_next_line.c mandatory/parsing/get_next_line_utils.c mandatory/parsing/cleaning.c mandatory/parsing/map_parssing.c mandatory/parsing/custom_func.c mandatory/parsing/custom_split.c mandatory/parsing/parssing_helpers.c \
		mandatory/parsing/helpers.c mandatory/parsing/custom_strjoin.c mandatory/parsing/texture_parse.c  mandatory/parsing/parssing.c mandatory/parsing/parssing_lengh.c mandatory/parsing/map_parssing_2.c mandatory/parsing/color_parse.c \
		mandatory/parsing/map_parssing_3.c mandatory/parsing/alloc_fill.c mandatory/parsing/alloc_fill_2.c mandatory/texturing/xmp_to_image.c mandatory/texturing/texturing_tiles.c mandatory/texturing/texturing_helpers.c \
		mandatory/parsing/door_coord.c
		
SRCS_B = bonus/raycasting/cub3D.c bonus/raycasting/move_player.c bonus/raycasting/cast_ray.c bonus/raycasting/ray_rander.c bonus/raycasting/init_player.c bonus/raycasting/mouse_control_b.c \
		bonus/parsing/get_next_line.c bonus/parsing/get_next_line_utils.c bonus/parsing/cleaning.c bonus/parsing/map_parssing.c bonus/parsing/custom_func.c bonus/parsing/custom_split.c bonus/parsing/parssing_helpers.c \
		bonus/parsing/helpers.c bonus/parsing/custom_strjoin.c bonus/parsing/texture_parse.c  bonus/parsing/parssing.c bonus/parsing/parssing_lengh.c bonus/parsing/map_parssing_2.c bonus/parsing/color_parse.c \
		bonus/parsing/map_parssing_3.c bonus/parsing/alloc_fill.c bonus/parsing/alloc_fill_2.c bonus/texturing/xmp_to_image.c bonus/texturing/texturing_tiles.c bonus/texturing/texturing_helpers.c \
		bonus/parsing/door_coord.c

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
	rm -rf $(OBJCS) $(OBJCS_B)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean