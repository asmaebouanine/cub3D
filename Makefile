# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asbouani <asbouani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/14 14:59:01 by asbouani          #+#    #+#              #
#    Updated: 2025/09/18 19:33:23 by asbouani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc

CFLAGS = -Wall -Wextra -Werror -Imlx  -fsanitize=address

MLX = -Lmlx -lmlx -lX11 -lXext -lm

HEADER = cub3D.h

SRCS = raycasting/cub3D.c raycasting/player.c \
		parsing/get_next_line.c parsing/get_next_line_utils.c parsing/cleaning.c parsing/map_parssing.c \
		parsing/custom_func.c parsing/custom_split.c parsing/parser.c parsing/helpers.c

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