/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 22:05:50 by hladeiro          #+#    #+#             */
/*   Updated: 2025/04/18 21:48:09 by malourei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubo.h"

static void	move_player(t_game *g, double dt)
{
	const float s = 300.0;
	if (g->keydown[UP_KEY] || g->keydown[W_KEY])
		p()->vel.y = (-s * dt) - 3;
	else if (g->keydown[S_KEY] || g->keydown[DOWN_KEY])
		p()->vel.y = (s * dt) + 3;
	if (g->keydown[A_KEY] || g->keydown[LEFT_KEY])
		p()->vel.x = (-s * dt) - 3;
	else if (g->keydown[D_KEY] || g->keydown[RIGHT_KEY])
		p()->vel.x = (s * dt) + 3;
	p()->pos.x += p()->vel.x;
	p()->pos.y += p()->vel.y;
	if (p()->pos.x < 0)
		p()->pos.x = 0;
	if (p()->pos.x > 800 - 20)
		p()->pos.x = 800 - 20;
	if (p()->pos.y < 0)
		p()->pos.y = 0;
	if (p()->pos.y > 600 - 20)
		p()->pos.y = 600 - 20;
}

static void	draw_player(t_game *g)
{
	int	x;
	int	y;

	y = p()->pos.y - 1;
	while (++y < p()->pos.y + 20)
	{
		x = p()->pos.x - 1;
		while (++x < p()->pos.x + 20)
			mlx_pixel_put(g->mlx, g->win.win, x, y, 0x00FFFF);
	}
}

t_player	*p(void)
{
	static t_player	p;
	static int		i;

	if (!i)
	{
		p.pos.x = 400;
		p.pos.y = 400;
		p.vel.x = 0;
		p.vel.y = 0;
		i++;
	}
	return (&p);
}

static void	update_game(t_game *g, double dt)
{
	mlx_clear_window(g->mlx, g->win.win);
	key_pressed(g);
	move_player(g, g->dt());
	draw_player(g);
	key_released(g);
}

static void	game_loop(t_game *g)
{
	return (update_game(g, g->dt()));
}

static void	game_start(void)
{
	t_game	*g;

	g = inti_game();
	g->animate = game_loop;
	event_handler(g);
	g->loop(g);
}

int	main(void)
{
	game_start();
	return (0);
}
