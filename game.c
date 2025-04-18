/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:46:10 by hladeiro          #+#    #+#             */
/*   Updated: 2025/04/18 20:46:11 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubo.h"


static int	update(t_game *g)
{
	if (g->animate)
		g->animate(g);
	return (0);
}

int	exit_t(t_game *game)
{
	exit(0);
	return (1);
}

void	loop(t_game *g)
{
	mlx_loop(g->mlx);
}

t_game	*inti_game(void)
{
	t_game	*g;

	g = ft_calloc(sizeof(t_game), 1);
	if (!g)
		exit(0);
	g->mlx = mlx_init();
	g->win.win = mlx_new_window(g->mlx, 800, 600, "Cube");
	g->win.mlx = g->mlx;
	mlx_hook(g->win.win, 17, (1L << 0), &exit_t, g);
	g->loop = loop;
	g->dt = get_delta_time;
	mlx_loop_hook(g->mlx, &update, g);
	return (g);
}
