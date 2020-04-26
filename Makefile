# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sid-bell <idbellasaid@gmail.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/01 06:02:07 by sid-bell          #+#    #+#              #
#    Updated: 2020/04/26 14:14:20 by sid-bell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fractol

FLAGS= -g -Wall -Wextra -Werror 

LIBMLX= -L/usr/X11/lib /usr/X11/lib/libmlx.a -lXext -lX11 -lm

LIBFT= src/libft/libft.a

HEADER= fdf.h

HINC = src/fractol.h

INC= -I/usr/local/include -Isrc/includes -Isrc/libft

OBJ=src/main.o src/events.o src/ft_draw.o

CFLAGS = $(INC) $(FLAGS)

CC=gcc

all: $(LIBFT)  $(NAME) 

$(NAME): $(LIBFT) $(HINC) $(OBJ)
	gcc $(OBJ) -o $(NAME) src/libft/libft.a -lm -L/usr/X11/lib /usr/X11/lib/libmlx.a -lXext -lX11 -lpthread

$(LIBFT):
	make -C src/libft

clean:
	make -C src/libft clean
	rm -rf $(OBJ)

fclean: clean
	make -C src/libft fclean
	rm -rf $(NAME)

re: fclean all
