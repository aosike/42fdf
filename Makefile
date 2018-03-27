# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agundry <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/26 18:31:07 by agundry           #+#    #+#              #
#    Updated: 2018/03/26 19:56:32 by agundry          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	fdf

CFLAGS	=	-Wall -Wextra -Werror -g

SRC		=	fdf.c

OBJ		=	$(patsubst %.c,%.o,$(SRC))

$(NAME)	:
			make -C libft/
			make -C mlx/
			gcc $(CFLAGS) -c $(SRC) -I fdf.h
			gcc $(CFLAGS) -o $(NAME) $(OBJ) -L libft/ -lft \
			-L ./mlx -l mlx -framework OpenGL -framework AppKit

all		:	$(NAME)

clean	:
			make -C libft/ clean
			make -C mlx/ clean
			rm -f $(OBJ)
	
fclean	:
			make -C libft/ fclean
			rm -f $(OBJ) $(NAME)

re		:	fclean all
