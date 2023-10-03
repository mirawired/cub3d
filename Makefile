# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avassor <avassor@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/10 12:13:14 by mira              #+#    #+#              #
#    Updated: 2023/10/03 11:57:46 by avassor          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CUB3D	= cub3d
NAME	= $(CUB3D)
BONUS_NAME = $(CUB3D)_bonus
CC		=	gcc
CFLAGS 	=	-g -Wall -Wextra #-Werror
LFLAGS	=	-lX11 -lXext -lm
INC		=	-I ./inc/

MLX_PATH	=	minilibx-linux/
MLX_NAME	=	libmlx_Linux.a
MINILIBX	=	$(MLX_PATH)$(MLX_NAME)

SRC_PATH =	./src/
OBJ_PATH =	obj/
BONUS_OBJ_PATH = obj_bonus/

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
					rays.c					\
					render.c				\
					gc.c					\
					gc_utils.c				\
					textures.c				\
					mlx_helpers.c			\
					data_init.c				\
					movements.c				\
					movements_extra.c		\
					rays_add.c

BONUS_SRC = 		cub3d.c					\
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
					raycast_bonus.c			\
					draw_line.c				\
					graphic_utils_bonus.c	\
					hooks.c					\
					player_bonus.c			\
					rays_bonus.c			\
					render_bonus.c			\
					gc.c					\
					gc_utils.c				\
					bfs.c					\
					minimap.c				\
					ai.c					\
					textures.c				\
					mlx_helpers.c			\
					data_init_bonus.c		\
					movements.c				\
					movements_extra.c		\
					sprites.c				\
					rays_add.c

SRCS = $(shell find $(SRC_PATH) -type d)
BONUS_SRCS = $(shell find $(SRC_PATH) -type d)
OBJS = $(addprefix $(OBJ_PATH), $(SRC:%.c=%.o))
BONUS_OBJ = $(addprefix $(BONUS_OBJ_PATH), $(BONUS_SRC:%.c=%.o))

vpath %.c $(SRCS)
vpath %.c $(BONUS_SRCS)

all: $(NAME)

bonus: $(BONUS_NAME)

$(NAME): $(MINILIBX) $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(MINILIBX) $(LFLAGS)

$(OBJ_PATH)%.o: %.c ./inc/cub3d.h
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

$(BONUS_OBJ_PATH)%.o: %.c ./inc/cub3d.h
	mkdir -p $(BONUS_OBJ_PATH)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

$(BONUS_NAME): $(MINILIBX) $(BONUS_OBJ)
	$(CC) -o $(BONUS_NAME) $(BONUS_OBJ) $(MINILIBX) $(LFLAGS)

$(MINILIBX):
	$(MAKE) -sC $(MLX_PATH)

all: $(NAME)

clean:
	rm -rdf $(OBJ_PATH)
	rm -rdf $(BONUS_OBJ_PATH)
	$(MAKE) clean -C $(MLX_PATH)

fclean: clean
	rm -f $(NAME)
	rm -f $(MLX_PATH)$(MLX_NAME)

re: fclean all

.PHONY: all bonus clean fclean re
