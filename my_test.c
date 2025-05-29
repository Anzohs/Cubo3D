/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 22:05:50 by hladeiro          #+#    #+#             */
/*   Updated: 2025/04/18 21:48:09 by malourei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubo.h"
#include "mlx/mlx.h"
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 512
#define TILE_SIZE 64
#define FOV 60
#define NUM_RAYS SCREEN_WIDTH
#define DR 0.0174533 // One degree in radians

static int g_map[8][8] = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1}
};


void put_pixel_to_image(t_img *img, int x, int y, int color)
{
    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
        return;
    char *pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(unsigned int *)pixel = color;
}

// Function to draw a line between two points
void draw_line(t_img *img, int x1, int y1, int x2, int y2, int color)
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


// Player singleton
t_player *p(void)
{
    static t_player player;
    static bool initialized = false;

    if (!initialized)
    {
        player.pos.x = TILE_SIZE + TILE_SIZE / 2;
        player.pos.y = TILE_SIZE + TILE_SIZE / 2;
        player.vel.x = 0;
        player.vel.y = 0;
        player.angle = 0.0;
        initialized = true;
    }
    return (&player);
}

// Check for collision with walls
static int check_collision(double x, double y)
{
    int grid_x = (int)(x / TILE_SIZE);
    int grid_y = (int)(y / TILE_SIZE);

    if (grid_x < 0 || grid_x >= 8 || grid_y < 0 || grid_y >= 8)
        return (1);
    return (g_map[grid_y][grid_x] == 1);
}

// Move the player based on velocity
static void move_player(t_game *g)
{
    double new_x = p()->pos.x + p()->vel.x;
    double new_y = p()->pos.y + p()->vel.y;

    if (!check_collision(new_x, p()->pos.y))
        p()->pos.x = new_x;
    if (!check_collision(p()->pos.x, new_y))
        p()->pos.y = new_y;
}

// Draw the 2D map
static void draw_map(t_game *g)
{
    int x, y, tile_x, tile_y;

    for (y = 0; y < 8; y++)
    {
        for (x = 0; x < 8; x++)
        {
            tile_x = x * TILE_SIZE;
            tile_y = y * TILE_SIZE;
            int color = (g_map[y][x] == 1) ? 0xFFFFFF : 0x000000;
            for (int i = 0; i < TILE_SIZE; i++)
            {
                for (int j = 0; j < TILE_SIZE; j++)
                {
                    put_pixel_to_image(g->map, tile_x + i, tile_y + j, color);
                }
            }
        }
    }
}

// Draw the player on the map
static void draw_player(t_game *g)
{
    int player_x = (int)p()->pos.x;
    int player_y = (int)p()->pos.y;

    for (int y = 0; y < 10; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            put_pixel_to_image(g->map, player_x + x, player_y + y, 0x00FFFF);
        }
    }
}

// Draw rays for 2D visualization
static void draw_rays_2d(t_game *g)
{
    int r, mx, my, dof;
    float rx, ry, ra, xo, yo, aTan, nTan, disH, disV, hx, hy, vx, vy, disT;

    ra = p()->angle - DR * 30;
    if (ra < 0)
        ra += 2 * M_PI;
    if (ra > 2 * M_PI)
        ra -= 2 * M_PI;

    for (r = 0; r < 60; r++)
    {
        // Horizontal Raycasting
        disH = 1000000;
        hx = p()->pos.x;
        hy = p()->pos.y;
        dof = 0;
        aTan = -1 / tan(ra);
        if (ra > M_PI)
        {
            ry = (((int)p()->pos.y >> 6) << 6) - 0.0001;
            rx = (p()->pos.y - ry) * aTan + p()->pos.x;
            yo = -64;
            xo = -yo * aTan;
        }
        else if (ra < M_PI)
        {
            ry = (((int)p()->pos.y >> 6) << 6) + 64;
            rx = (p()->pos.y - ry) * aTan + p()->pos.x;
            yo = 64;
            xo = -yo * aTan;
        }
        else
        {
            rx = p()->pos.x;
            ry = p()->pos.y;
            dof = 8;
        }
        while (dof < 8)
        {
            mx = (int)(rx) >> 6;
            my = (int)(ry) >> 6;
            if (mx >= 0 && my >= 0 && mx < 8 && my < 8 && g_map[my][mx] == 1)
            {
                hx = rx;
                hy = ry;
                disH = sqrt((hx - p()->pos.x) * (hx - p()->pos.x) + (hy - p()->pos.y) * (hy - p()->pos.y));
                dof = 8;
            }
            else
            {
                rx += xo;
                ry += yo;
                dof++;
            }
        }

        // Vertical Raycasting
        disV = 1000000;
        vx = p()->pos.x;
        vy = p()->pos.y;
        dof = 0;
        nTan = -tan(ra);
        if (ra > M_PI_2 && ra < 3 * M_PI_2)
        {
            rx = (((int)p()->pos.x >> 6) << 6) - 0.0001;
            ry = (p()->pos.x - rx) * nTan + p()->pos.y;
            xo = -64;
            yo = -xo * nTan;
        }
        else if (ra < M_PI_2 || ra > 3 * M_PI_2)
        {
            rx = (((int)p()->pos.x >> 6) << 6) + 64;
            ry = (p()->pos.x - rx) * nTan + p()->pos.y;
            xo = 64;
            yo = -xo * nTan;
        }
        else
        {
            rx = p()->pos.x;
            ry = p()->pos.y;
            dof = 8;
        }
        while (dof < 8)
        {
            mx = (int)(rx) >> 6;
            my = (int)(ry) >> 6;
            if (mx >= 0 && my >= 0 && mx < 8 && my < 8 && g_map[my][mx] == 1)
            {
                vx = rx;
                vy = ry;
                disV = sqrt((vx - p()->pos.x) * (vx - p()->pos.x) + (vy - p()->pos.y) * (vy - p()->pos.y));
                dof = 8;
            }
            else
            {
                rx += xo;
                ry += yo;
                dof++;
            }
        }

        // Determine the closest intersection
        if (disV < disH)
        {
            rx = vx;
            ry = vy;
            disT = disV;
        }
        else
        {
            rx = hx;
            ry = hy;
            disT = disH;
        }

        // Draw the ray
        draw_line(g->map, (int)p()->pos.x, (int)p()->pos.y, (int)rx, (int)ry, 0xFF0000);

        // Increment the ray angle
        ra += DR;
        if (ra < 0)
            ra += 2 * M_PI;
        if (ra > 2 * M_PI)
            ra -= 2 * M_PI;
    }
}

// Update the game state
static void update_game(t_game *g)
{
    move_player(g);
    draw_map(g);
    draw_player(g);
    draw_rays_2d(g);
    mlx_put_image_to_window(g->mlx, g->win.win, g->map->img, 0, 0);
}

// Main function
int main(void)
{
    t_game *g = inti_game();
    g->animate = update_game;
    event_handler(g);
    g->loop(g);
    return (0);
}
