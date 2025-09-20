# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/06 19:27:01 by wnid-hsa          #+#    #+#              #
#    Updated: 2025/09/20 10:55:03 by wnid-hsa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address
NAME = cub
SRCS = get_next_line.c get_next_line_utils.c cleaning.c map_parssing.c custom_func.c custom_split.c parssing_helpers.c \
		helpers.c custom_strjoin.c texture_parse.c  parssing.c parssing_lengh.c map_parssing_2.c color_parse.c \
		alloc_fill.c alloc_fill_2.c
HDRS = cub3d.h
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
