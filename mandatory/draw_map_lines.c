/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_lines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badal-la <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 17:37:33 by badal-la          #+#    #+#             */
/*   Updated: 2025/02/08 17:46:48 by badal-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

void    init_bresenham(t_bresenham *b, t_point p1, t_point p2)
{
    b->dx = p2.x - p1.x;
    if (b->dx < 0)
        b->dx = -b->dx;
    b->dy = p2.y - p1.y;
    if (b->dy < 0)
        b->dy = -b->dy;
    if (p1.x < p2.x)
        b->sx = 1;
    else
        b->sx = -1;
    if (p1.y < p2.y)
        b->sy = 1;
    else
        b->sy = -1;
    b->err = b->dx - b->dy;
}

void    draw_line(t_mlx *mlx, t_point p1, t_point p2)
{
    t_bresenham b;

    p1.x = p1.x * mlx->zoom + mlx->offset_x;
    p1.y = p1.y * mlx->zoom + mlx->offset_y;
    p2.x = p2.x * mlx->zoom + mlx->offset_x;
    p2.y = p2.y * mlx->zoom + mlx->offset_y;
    init_bresenham(&b, p1, p2);
    while (1)
    {
        put_pixel_to_image(mlx, p1.x, p1.y, p1.color);
        if (p1.x == p2.x && p1.y == p2.y)
            break;
        b.e2 = 2 * b.err;
        if (b.e2 > -b.dy)
        {
            b.err = b.err - b.dy;
            p1.x = p1.x + b.sx;
        }
        if (b.e2 < b.dx)
        {
            b.err = b.err + b.dx;
            p1.y = p1.y + b.sy;
        }
    }
} 

void    draw_map_lines(t_mlx *mlx, t_map *map)
{
    int x;
    int y;

    y = 0;
    while (y < map->height)
    {
        x = 0;
        while (x < map->width)
        {
            if (x < map->width - 1)
                draw_line(mlx, map->grid[y][x], map->grid[y][x + 1]);
            if (y < map->height - 1)
                draw_line(mlx, map->grid[y][x], map->grid[y + 1][x]);
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
} 