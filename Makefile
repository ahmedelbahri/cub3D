# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akadi <akadi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 12:59:18 by ahel-bah          #+#    #+#              #
#    Updated: 2022/11/12 17:12:38 by akadi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT = libft/libft.a
C = gcc
CFLAGS = -Wall -Wextra -Werror -g
NAME = cub3D
SRC = main.c map_handling.c utils.c layers.c keys.c init_data.c get_next_line.c \
fill_data.c extract_line.c draw_2d.c
OBJ = $(SRC:.c=.o)
# BNS = 
# B_OBJ = $(BNS:.c=.o)

all: $(LIBFT) $(NAME) 

$(NAME): $(OBJ) cub3D.h
	$(C) $(CFLAGS) $(OBJ) -lmlx -framework OpenGL -framework AppKit -o $(NAME) $(LIBFT)

$(LIBFT):
	make bonus -C libft
clean:
	rm -rf $(OBJ) $(B_OBJ)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all
