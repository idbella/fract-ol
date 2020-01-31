# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/01 06:02:07 by sid-bell          #+#    #+#              #
#    Updated: 2020/01/31 21:33:47 by sid-bell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fractol

FLAGS= -g -Wall -Wextra -Werror 

LIBMLX= -L /usr/local -lmlx -framework OpenGl -framework AppKit

LIBFT= src/libft/libft.a

HEADER= fdf.h

HINC = src/fractol.h

INC= -I/usr/local/include -Isrc/includes -Isrc/libft

OBJ=src/main.o src/events.o src/ft_draw.o

CFLAGS = $(INC) $(FLAGS)

CC=gcc

all: $(LIBFT)  $(NAME) 

$(NAME): $(LIBFT) $(HINC) $(OBJ)
	gcc -I /usr/local/include $(LIBFT) $(LIBMLX) $(INC) $(FLAGS) $(OBJ) -o $(NAME)

$(LIBFT):
	make -C src/libft

clean:
	make -C src/libft clean
	rm -rf $(OBJ)

fclean: clean
	make -C src/libft fclean
	rm -rf $(NAME)

re: fclean all
