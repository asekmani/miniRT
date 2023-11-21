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

# HEADER = includes/minirt.h

NAME=miniRT
NAME_B=miniRT_bonus

OBJ_DIR = obj

M_SRCS = M_src/miniRT.c \
		 M_src/utils.c \
         M_src/render.c \
         M_src/exit.c \
         M_src/ft_color.c \
         M_src/ft_camera.c \
         M_src/ft_split.c \
         M_src/get_next_line.c \
         M_src/Memory_allocator.c \
         M_src/init_struct.c \
         M_src/parsing.c \
         M_src/elements_parse.c \
         M_src/shapes_parse.c \
         M_src/params_parse.c \
		 M_src/vector_operations.c \
         M_src/intersection.c \
		 M_src/test.c

B_SRCS = B_src/miniRT_bonus.c

CFLAGS = -g3 -Wall -Wextra -Werror
# MFLAGS = libmlx.a -lmlx -framework OpenGL -framework AppKit
CC = cc

OBJS_M = $(addprefix $(OBJ_DIR)/, $(M_SRCS:.c=.o))
OBJS_B = $(addprefix $(OBJ_DIR)/, $(B_SRCS:.c=.o))

all: $(NAME)
bonus: $(NAME_B)

$(NAME): $(OBJS_M) $(HEADER)
	@$(CC)  $(CFLAGS) $(OBJS_M) -Lminilibx-linux -L/usr/lib -Iminilibx-linux/ -o $(NAME) -lXext -lX11 -lm -lmlx_Linux

$(NAME_B): $(OBJS_B) $(HEADER)
	@$(CC) $(CFLAGS) $(OBJS_B) -Lminilibx-linux -L/usr/lib -Iminilibx-linux/ -o $(NAME_B) -lXext -lX11 -lm -lmlx_Linux

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I/usr/include -Iminilibx-linux/ -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME) $(NAME_B)

re: fclean $(NAME) clean
re_b: fclean $(NAME_B) clean

.PHONY: all $(NAME) $(NAME_B) clean fclean re