# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahel-bah <ahel-bah@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 12:59:18 by ahel-bah          #+#    #+#              #
#    Updated: 2022/12/11 16:50:52 by ahel-bah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT = libft/libft.a
C = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = cub3D
SRC = main.c map_handling.c utils.c layers.c keys.c init_data.c get_next_line.c \
fill_data.c extract_line.c draw_2d.c key_check.c map_utils.c intersection.c \
mlx_utils.c mlx_utils2.c 
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
