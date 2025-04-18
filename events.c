#include "cubo.h"

void	key_pressed(t_game *g)
{
	if (g->keydown[UP_KEY] || g->keydown[W_KEY])
		p()->vel.y = -3;
	if (g->keydown[DOWN_KEY] || g->keydown[S_KEY])
		p()->vel.y = 3;
	if (g->keydown[D_KEY] || g->keydown[RIGHT_KEY])
		p()->vel.x = 3;
	if (g->keydown[A_KEY] || g->keydown[LEFT_KEY])
		p()->vel.x = -3;
}

void	key_released(t_game *g)
{
	if (!g->keydown[UP_KEY] && !g->keydown[W_KEY] && !g->keydown[DOWN_KEY]
		&& !g->keydown[S_KEY])
		p()->vel.y = 0;
	if (!g->keydown[D_KEY] && !g->keydown[RIGHT_KEY] && !g->keydown[A_KEY]
		&& !g->keydown[LEFT_KEY])
		p()->vel.x = 0;
}

static int	keypress(int key, t_game *g)
{
	if (key == 53 || key == 65307)
		exit(0);
	if (key < 1000)
		g->keydown[key] = true;
	return (0);
}

static int	keyrelease(int k, t_game *g)
{
	if (k < 1000)
		g->keydown[k] = false;
	return (0);
}

void	event_handler(t_game *game)
{
	mlx_hook(game->win.win, 2, 1L << 0, keypress, game);
	mlx_hook(game->win.win, 3, 1L << 1, keyrelease, game);
	mlx_do_key_autorepeatoff(game->mlx);
}
