# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/15 20:06:44 by hladeiro          #+#    #+#              #
#    Updated: 2025/04/15 20:08:37 by hladeiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	cub3D
CC = cc
FLAGS = -g -O3
LIBFT = libft/libft.a
MLX = mlx/libmlx.a
SRC = game.c events.c get_delta_time.c main.c
OBJ_DIR = obj
OBJ := $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))
INC = -I. -Ilibft -Imlx
M = mlx

MLXFLAGS = -L ./mlx/ -lmlx -framework OpenGL -framework AppKit -lz
ifeq ($(shell uname), Linux)
	MLXFLAGS = -L ./mlx_linux/ -lmlx -Imlx -lXext -lX11
	MLX = mlx_linux/libmlx.a
	INC = -I. -Ilibft -Imlx_linux
	M = mlx_linux
endif

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(FLAGS) $(INC) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C libft

$(MLX):
	@$(MAKE) -C $(M)

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(LIBFT) $(MLXFLAGS) -o $(NAME)
	@echo "Executable created: $(NAME)"

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C libft clean
	@echo "Cleaned up object files and libraries"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(M) clean
	@$(MAKE) -C libft fclean
	@echo "Removed executable: $(NAME)"
