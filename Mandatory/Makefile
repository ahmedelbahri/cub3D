# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahel-bah <ahel-bah@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 12:59:18 by ahel-bah          #+#    #+#              #
#    Updated: 2022/12/19 17:14:11 by ahel-bah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT = ../libft/libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -lmlx -framework OpenGL -framework AppKit
NAME = cub3D
SRC = main.c map_handling.c utils.c layers.c keys.c init_data.c get_next_line.c \
fill_data.c extract_line.c draw_2d.c key_check.c map_utils.c intersection.c \
mlx_utils.c normalize.c
OBJ = $(SRC:.c=.o)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLXFLAGS) -o $@ $(LIBFT)

%.o: %.c ../include/cub3D.h
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make bonus -C ../libft
clean:
	rm -rf $(OBJ) $(B_OBJ)
	make clean -C ../libft

fclean: clean
	rm -f $(NAME)
	make fclean -C ../libft

re: fclean all
