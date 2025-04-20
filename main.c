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
#define LINE_LENGTH 20
#define TILE_SIZE (SCREEN_WIDTH / MAP_WIDTH)
#define FOV 60
#define NUM_RAYS SCREEN_WIDTH
#define RAY_STEP ((float)FOV / NUM_RAYS)
#define MAX_DEPTH 1000

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
	if (g->keydown[A_KEY])
		p()->vel.x = (-s * dt) - 3;
	else if (g->keydown[D_KEY])
		p()->vel.x = (s * dt) + 3;
	double new_x = p()->pos.x + p()->vel.x;
	double new_y = p()->pos.y + p()->vel.y;
	if (g->keydown[RIGHT_KEY])
	{
		p()->angle += 0.05;
		if (p()->angle > 2 * M_PI)
			p()->angle -= 2 * M_PI;
	}
	if (g->keydown[LEFT_KEY])
	{
		p()->angle -= 0.05;
		if (p()->angle < 0)
			p()->angle += 2 * M_PI;
	}

		if (!check_collision(new_x, p()->pos.y))
			p()->pos.x = new_x;
		if (!check_collision(p()->pos.x, new_y))
			p()->pos.y = new_y;
}

static float deg_to_rad(float deg) {
    return deg * (M_PI / 180.0);
}

static float fix_angle(float angle) {
    if (angle < 0)
        angle += 360;
    if (angle >= 360)
        angle -= 360;
    return angle;
}

static void	put_pixel_to_image(t_img *img, int x, int y, int color)
{
	if (x < 0 || x >= 800 || y < 0 || y >= 600)
		return;
	char *pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)pixel = color;
}

static void draw_line(t_img *img, int x1, int y1, int x2, int y2, int color)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        put_pixel_to_image(img, x1, y1, color);
        if (x1 == x2 && y1 == y2)
            break;
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

static void draw_rays_2d(t_game *g) {
    float ra = p()->angle + deg_to_rad(FOV) / 2;

    for (int r = 0; r < NUM_RAYS; r++) {
        float disV = MAX_DEPTH, disH = MAX_DEPTH;
        float vx = p()->pos.x, vy = p()->pos.y;
        float rx, ry, xo, yo;
        float Tan = tan(ra);

        int tile = TILE_SIZE;

        // --- Vertical Raycasting ---
        int dof = 0;
        if (cos(ra) > 0.001) {
            rx = (((int)p()->pos.x / tile) * tile) + tile;
            ry = p()->pos.y + (p()->pos.x - rx) * Tan;
            xo = tile;
            yo = -xo * Tan;
        } else if (cos(ra) < -0.001) {
            rx = (((int)p()->pos.x / tile) * tile) - 0.0001;
            ry = p()->pos.y + (p()->pos.x - rx) * Tan;
            xo = -tile;
            yo = -xo * Tan;
        } else {
            rx = p()->pos.x;
            ry = p()->pos.y;
            dof = 8;
        }

        while (dof < 8) {
            int mx = (int)(rx) / tile;
            int my = (int)(ry) / tile;
            if (mx >= 0 && mx < MAP_WIDTH && my >= 0 && my < MAP_HEIGHT && g_map[my][mx] == 1) {
                disV = cos(ra) * (rx - p()->pos.x) - sin(ra) * (ry - p()->pos.y);
                vx = rx;
                vy = ry;
                break;
            }
            rx += xo;
            ry += yo;
            dof++;
        }

        // --- Horizontal Raycasting ---
        dof = 0;
        Tan = 1.0 / Tan;
        if (sin(ra) > 0.001) {
            ry = (((int)p()->pos.y / tile) * tile) - 0.0001;
            rx = p()->pos.x + (p()->pos.y - ry) * Tan;
            yo = -tile;
            xo = -yo * Tan;
        } else if (sin(ra) < -0.001) {
            ry = (((int)p()->pos.y / tile) * tile) + tile;
            rx = p()->pos.x + (p()->pos.y - ry) * Tan;
            yo = tile;
            xo = -yo * Tan;
        } else {
            rx = p()->pos.x;
            ry = p()->pos.y;
            dof = 8;
        }

        while (dof < 8) {
            int mx = (int)(rx) / tile;
            int my = (int)(ry) / tile;
            if (mx >= 0 && mx < MAP_WIDTH && my >= 0 && my < MAP_HEIGHT && g_map[my][mx] == 1) {
                disH = cos(ra) * (rx - p()->pos.x) - sin(ra) * (ry - p()->pos.y);
                if (disH < disV) {
                    vx = rx;
                    vy = ry;
                }
                break;
            }
            rx += xo;
            ry += yo;
            dof++;
        }

        // Draw ray only if we hit a wall
        if (vx != p()->pos.x || vy != p()->pos.y)
            draw_line(g->map, (int)p()->pos.x, (int)p()->pos.y, (int)vx, (int)vy, 0xFF0000);

        ra -= deg_to_rad(RAY_STEP);
    }
}



static void draw_map_and_player_to_image(t_game *g) {
    int x, y, tile_x, tile_y;
    for (y = 0; y < 600; y++) {
        for (x = 0; x < 800; x++) {
            put_pixel_to_image(g->map, x, y, 0x000000);
        }
    }

    for (y = 0; y < MAP_HEIGHT; y++) {
        for (x = 0; x < MAP_WIDTH; x++) {
            tile_x = x * TILE_SIZE;
            tile_y = y * TILE_SIZE;
            if (g_map[y][x] == 1) {
                int i, j;
                for (j = 0; j < TILE_SIZE; j++) {
                    for (i = 0; i < TILE_SIZE; i++) {
                        put_pixel_to_image(g->map, tile_x + i, tile_y + j, 0xFFFFFF);
                    }
                }
            }
        }
    }


    int player_x = (int)p()->pos.x;
    int player_y = (int)p()->pos.y;
    for (y = 0; y < 10; y++) {
        for (x = 0; x < 10; x++) {
            put_pixel_to_image(g->map, player_x + x, player_y + y, 0x00FFFF);
        }
    }
    draw_rays_2d(g);
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
