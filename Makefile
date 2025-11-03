# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asbouani <asbouani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/14 14:59:01 by asbouani          #+#    #+#              #
#    Updated: 2025/11/03 13:47:59 by asbouani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc

CFLAGS = -Wall -Wextra -Werror -Imlx  -fsanitize=address

MLX = -Lmlx -lmlx -lX11 -lXext -lm

HEADER = cub3D.h

SRCS = raycasting/cub3D.c raycasting/move_player.c raycasting/cast_ray.c raycasting/ray_rander.c raycasting/init_player.c raycasting/mouse_control.c\
		parsing/get_next_line.c parsing/get_next_line_utils.c parsing/cleaning.c parsing/map_parssing.c parsing/custom_func.c parsing/custom_split.c parsing/parssing_helpers.c \
		parsing/helpers.c parsing/custom_strjoin.c parsing/texture_parse.c  parsing/parssing.c parsing/parssing_lengh.c parsing/map_parssing_2.c parsing/color_parse.c \
		parsing/map_parssing_3.c parsing/alloc_fill.c parsing/alloc_fill_2.c texturing/xmp_to_image.c texturing/texturing_tiles.c texturing/texturing_helpers.c \
		parsing/door_coord.c

OBJCS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJCS)
	$(CC) $(CFLAGS) $(OBJCS) $(MLX) -o $(NAME)
	
clean: 
	rm -rf $(OBJCS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean