# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahel-bah <ahel-bah@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 12:59:18 by ahel-bah          #+#    #+#              #
#    Updated: 2022/11/08 23:03:17 by ahel-bah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT = libft/libft.a
C = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = cub3D
SRC = main.c map_handling.c utils.c layers.c keys.c init_data.c get_next_line.c \
fill_data.c extract_line.c draw_2d.c
OBJ = $(SRC:.c=.o)
# BNS = 
# B_OBJ = $(BNS:.c=.o)

all: $(LIBFT) $(NAME) 
$(LIBFT):
	make bonus -C libft

$(NAME): $(OBJ)
	$(C) $(CFLAGS) $(OBJ) -lmlx -framework OpenGL -framework AppKit -o $(NAME) $(LIBFT)

clean:
	rm -rf $(OBJ) $(B_OBJ)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all
