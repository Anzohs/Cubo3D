#include "cubo.h"

static void	move_player(t_game *g)
{
	p()->pos.x += (p()->vel.x) + (p()->vel.x * g->dt());
	p()->pos.y += (p()->vel.y) + (p()->vel.y * g->dt());

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
	move_player(g);
	draw_player(g);
	key_released(g);
}

static void	game_loop(t_game *g)
{
	return (update_game(g, g->dt()));
}

void	game_start(void)
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
