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

typedef char	*t_string;

typedef struct s_2Vector
{
	int			x;
	int			y;
}				t_2Vector;

typedef struct s_3Vector
{
	int			x;
	int			y;
	int			z;
}				t_3Vector;

typedef struct s_win
{
	void		*mlx;
	void		*win;
	t_2Vector	size;
}				t_win;

typedef struct s_player
{
	t_2Vector	vel;
	t_2Vector	pos;
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
