# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cadlane <cadlane@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/15 05:16:16 by cadlane           #+#    #+#              #
#    Updated: 2024/08/15 05:16:18 by cadlane          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror 


SRC = fractol.c fractal_init.c fractal_render.c hooks.c util.c 

OBJ = $(SRC:.c=.o)
LINK = -Lminilibx-linux -lmlx_Linux -lX11 -lXext

NAME = fractol

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LINK) -o $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean:clean
	rm -rf $(NAME)

re : fclean all
.SECONDARY:  $(OBJ)