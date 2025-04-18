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

NAME = CUBE

MLXFLAGS = -L ./mlx/ -lmlx -framework OpenGL -framework AppKit -lz
ifeq ($(shell uname), Linux)
	MLXFLAGS = -L ./mlx_linux/ -lmlx -Imlx -lXext -lX11
endif
