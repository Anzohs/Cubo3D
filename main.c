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
#include "mlx/mlx.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MAP_WIDTH 20
#define MAP_HEIGHT 15
#define TILE_SIZE (SCREEN_WIDTH / MAP_WIDTH)

static int g_map[MAP_HEIGHT][MAP_WIDTH] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

static int	check_collision(double x, double y)
{
	int grid_x1 = (int)(x / TILE_SIZE);
	int grid_y1 = (int)(y / TILE_SIZE);
	int grid_x2 = (int)((x + 10) / TILE_SIZE);
	int grid_y2 = (int)((y + 10) / TILE_SIZE);

	if (grid_x1 < 0 || grid_x2 >= MAP_WIDTH || grid_y1 < 0 || grid_y2 >= MAP_HEIGHT)
		return (1);

	if (g_map[grid_y1][grid_x1] == 1 || g_map[grid_y1][grid_x2] == 1 ||
		g_map[grid_y2][grid_x1] == 1 || g_map[grid_y2][grid_x2] == 1)
		return (1);

	return (0);
}

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
	double new_x = p()->pos.x + p()->vel.x;
	double new_y = p()->pos.y + p()->vel.y;

		if (!check_collision(new_x, p()->pos.y))
			p()->pos.x = new_x;
		if (!check_collision(p()->pos.x, new_y))
			p()->pos.y = new_y;

		if (p()->pos.x < 0)
			p()->pos.x = 0;
		if (p()->pos.x > 800 - 20)
			p()->pos.x = 800 - 20;
		if (p()->pos.y < 0)
			p()->pos.y = 0;
		if (p()->pos.y > 600 - 20)
			p()->pos.y = 600 - 20;
}

static void	put_pixel_to_image(t_img *img, int x, int y, int color)
{
	if (x < 0 || x >= 800 || y < 0 || y >= 600)
		return;
	char *pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)pixel = color;
}

static void	draw_map_and_player_to_image(t_game *g)
{
	int x, y, tile_x, tile_y;
	for (y = 0; y < 600; y++)
	{
		for (x = 0; x < 800; x++)
		{
			put_pixel_to_image(g->map, x, y, 0x000000);
		}
	}

	for (y = 0; y < MAP_HEIGHT; y++)
	{
		for (x = 0; x < MAP_WIDTH; x++)
		{
			tile_x = x * TILE_SIZE;
			tile_y = y * TILE_SIZE;
			if (g_map[y][x] == 1)
			{
				int i, j;
				for (j = 0; j < TILE_SIZE; j++)
				{
					for (i = 0; i < TILE_SIZE; i++)
					{
						put_pixel_to_image(g->map, tile_x + i, tile_y + j, 0xFFFFFF);
					}
				}
			}
		}
	}
	int player_x = (int)p()->pos.x;
	int player_y = (int)p()->pos.y;
	for (y = 0; y < 10; y++)
	{
		for (x = 0; x < 10; x++)
		{
			put_pixel_to_image(g->map, player_x + x, player_y + y, 0x00FFFF);
		}
	}
}


t_player	*p(void)
{
	static t_player	p;
	static int		i;

	if (!i)
	{
		p.pos.x = TILE_SIZE + TILE_SIZE / 2;
		p.pos.y = TILE_SIZE + TILE_SIZE / 2;
		p.vel.x = 0;
		p.vel.y = 0;
		i++;
	}
	return (&p);
}

static void	update_game(t_game *g, double dt)
{
	mlx_put_image_to_window(g->mlx, g->win.win, g->map->img, 0 , 0);
	key_pressed(g);
	move_player(g, dt);
	draw_map_and_player_to_image(g);
	mlx_put_image_to_window(g->mlx, g->win.win, g->map->img, 0, 0);
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
