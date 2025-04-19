/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:24:02 by hladeiro          #+#    #+#             */
/*   Updated: 2025/04/18 22:05:40 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "map/map.h"

typedef char	*t_string;

typedef struct s_win
{
	void		*mlx;
	void		*win;
	t_vector	size;
}				t_win;

typedef struct s_player
{
	t_vector	vel;
	t_vector	pos;
}				t_player;

typedef struct s_game
{
	void		*mlx;
	t_win		win;
	int			keydown[900000];
	double		(*dt)(void);
	void		(*loop)(struct s_game *game);
	void		(*animate)(struct s_game *game);
}				t_game;

#endif
