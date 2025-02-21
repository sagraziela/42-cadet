# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/10 13:28:46 by lmiguel-          #+#    #+#              #
#    Updated: 2025/02/20 13:46:59 by lmiguel-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= cub3d
CC 			= cc 
FLAGS 		= -Wall -Wextra -Werror -g -O0
MLX			= /mlx/Makefile.gen
MLX_OBJ_DIR	= ./mlx
LIBFT		= /libft/libft.a
INCLUDE 	= -I ./src -I ./libft -I ./mlx
LIB			= -L ./libft -lft -L ./mlx -lX11 -lXext -lm -lmlx -lbsd
#LIB = -L ./libft -lft -L ./mlx -lmlx -L/usr/lib/x86_64-linux-gnu/ -lXext -lX11 -lm -lbsd
OBJ_PATH = ./build/
OBJ = $(addprefix $(OBJ_PATH), $(notdir $(SRC:.c=.o)))
SRC			=	src/main.c							\
				src/bresenham_assist.c				\
				src/draw_minimap.c					\
				src/extra_functions.c				\
				src/ray_assist.c					\
				src/render_assist.c					\
				src/map_handle.c					\
				src/player_camera_handler.c			\
				src/player_move_handler.c			\
				src/player_spawn_handler.c			\
				src/parse.c							\
				src/parse_assist.c					\
				src/init.c							\
				src/handle_texture.c				\
				src/handle_colors.c					\
				src/handle_colors_assist.c			\
				src/read_map.c						\
				src/handle_map.c					\
				src/handle_map_utils.c				\
				src/exit.c							\

all:		$(MLX) $(LIBFT) $(NAME)

run: $(NAME)
	./cub3d ./maps/grazi.cub

val: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./cub3d ./maps/grazi.cub

$(NAME):	$(OBJ)
			$(CC) $(FLAGS) -o $@ $^ $(LIB)
$(MLX):
			@make -C mlx
$(LIBFT):
			@make -C libft

$(OBJ_PATH)%.o: ./src/%.c
			@mkdir -p $(OBJ_PATH)
			$(CC) $(FLAGS) $(INCLUDE) -o $@ -c $<

clean:
			@make -s $@ -C libft
			@rm -rf $(OBJ)
			@rm -rf $(OBJ_PATH)
			@$(MAKE) -C $(MLX_OBJ_DIR) clean

fclean:		clean
			@make -s $@ -C libft
			@rm -rf $(NAME)
			
re:			fclean all

.PHONY:		all clean fclean re run val
