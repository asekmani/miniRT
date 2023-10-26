# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asekmani <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/18 17:21:09 by asekmani          #+#    #+#              #
#    Updated: 2022/12/01 12:18:11 by asekmani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= miniRT

SRCS=	M_src/miniRT.c \
		M_src/utils.c \
		M_src/init.c \
		M_src/exit.c \

INC_DIR= includes/

OBJ= ${SRCS:.c=.o}

CC= cc
FLAGS= -Wall -Wextra -Werror -g3
RM=rm -f

all: $(NAME)

$(NAME): $(OBJ)
	cd minilibx-linux;make;cd ..
	$(CC) $(FLAGS) $(OBJ) -Lminilibx-linux -L/usr/lib -Iminilibx-linux/ -o $(NAME) -lXext -lX11 -lm -lmlx_Linux

AR= ar rcs

%.o: %.c
	$(CC) -Wall -Wextra -Werror -I/usr/include -Iminilibx-linux/ -c $< -o $@

clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME}

re: fclean all


.PHONY: all clean fclean re bonus
