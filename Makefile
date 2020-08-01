# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sid-bell <sid-bell@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/01 06:02:07 by sid-bell          #+#    #+#              #
#    Updated: 2020/08/01 03:20:10 by sid-bell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fractol

FLAGS= -Wall -Wextra -Werror 

LIBMLX= src/minilibx/libmlx.a -lXext -lX11 -lm

LIBFT= src/libft/libft.a

HEADER= fdf.h

HINC = src/fractol.h

MLX=src/minilibx/libmlx.a

INC= -I/usr/local/include -Isrc/includes -Isrc/libft -Isrc/minilibx

OBJ=src/main.o src/events.o src/ft_draw.o

CFLAGS = $(INC) $(FLAGS)

CC=gcc

all: $(MLX) $(LIBFT)  $(NAME) 

$(NAME): $(LIBFT) $(HINC) $(OBJ)
	gcc $(OBJ) -o $(NAME) src/libft/libft.a $(LIBMLX) -lXext -lX11

$(LIBFT):
	make -C src/libft
$(MLX):
	make -C src/minilibx
clean:
	make -C src/libft clean
	make -C src/minilibx clean
	rm -rf $(OBJ)

fclean: clean
	make -C src/libft fclean
	rm -rf $(NAME)

re: fclean all
