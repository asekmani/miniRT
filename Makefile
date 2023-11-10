# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aouhadou <aouhadou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/23 10:28:09 by aouhadou          #+#    #+#              #
#    Updated: 2022/09/26 14:06:19 by aouhadou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADER = includes/minirt.h

NAME=miniRT
NAME_B=miniRT_bonus

M_SRCS= M_src/miniRT.c \
				M_src/utils.c \
				M_src/render.c \
				M_src/exit.c \
				M_src/ft_split.c \
				M_src/get_next_line.c \
				M_src/Memory_allocator.c \
				M_src/init_struct.c \
				M_src/parsing.c \
				M_src/elements_parse.c \
				M_src/shapes_parse.c \
				M_src/params_parse.c
	
B_SRCS= B_src/miniRT_bonusß.c \
	
CFLAGS= -g -Wall -Wextra -Werror
CC= gcc

OBJS_M=$(M_SRCS:.c=.o)
OBJS_B=$(B_SRCS:.c=.o)

all: $(NAME)
bonus: $(NAME_B)

$(NAME):$(OBJS_M) $(HEADER)
	@$(CC)  libmlx.a -lmlx -framework OpenGL -framework AppKit $(CFLAGS) $(OBJS_M) -o $(NAME)

$(NAME_B):$(OBJS_B) $(HEADER)
	@$(CC) libmlx.a -lmlx -framework OpenGL -framework AppKit $(CFLAGS) $(OBJS_B) -o $(NAME_B)

%.o:%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@rm -rf $(OBJS_M) $(OBJS_B)

fclean : clean
	@rm -rf $(NAME) $(NAME_B)


re : fclean $(NAME) clean
re_b : fclean $(NAME_B) clean

.PHONY: all $(NAME) $(NAME_B) clean fclean re