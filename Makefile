# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avassor <avassor@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/10 12:13:14 by mira              #+#    #+#              #
#    Updated: 2023/08/19 01:07:54 by jgarcia          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CUB3D	= cub3d
NAME	= $(CUB3D)

CC		=	gcc
CFLAGS 	=	-g -Wall -Wextra #-Werror
LFLAGS	=	-lX11 -lXext -lm
INC		=	-I ./inc/

MLX_PATH	=	minilibx-linux/
MLX_NAME	=	libmlx_Linux.a
MINILIBX	=	$(MLX_PATH)$(MLX_NAME)

SRC_PATH =	./src/
OBJ_PATH =	obj/

SRC =				cub3d.c					\
					clean.c					\
					get_next_line_utils.c	\
					get_next_line.c			\
					gnl_add.c				\
					pars_map.c				\
					get_arg.c				\
					read_utils.c			\
					rror.c					\
					utils.c					\
					pars_utils.c			\
					raycast.c				\
					draw_line.c				\
					graphic_utils.c			\
					hooks.c					\
					player.c				\
					rays.c					\
					render.c

SRCS = $(shell find $(SRC_PATH) -type d)

OBJS = $(addprefix $(OBJ_PATH), $(SRC:%.c=%.o))
vpath %.c $(SRCS)

$(NAME): $(MINILIBX) $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(MINILIBX) $(LFLAGS)

$(OBJ_PATH)%.o: %.c ./inc/cub3d.h
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

$(MINILIBX):
	$(MAKE) -sC $(MLX_PATH)

all: $(NAME)

clean:
	rm -rdf $(OBJ_PATH)
	$(MAKE) clean -C $(MLX_PATH)

fclean: clean
	rm -f $(NAME)
	rm -f $(MLX_PATH)$(MLX_NAME)

re: fclean all

.PHONY: all clean fclean re