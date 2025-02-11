/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_points.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badal-la <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 17:19:38 by badal-la          #+#    #+#             */
/*   Updated: 2025/02/11 11:16:20 by badal-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

void	init_mlx(t_mlx *mlx, t_map *map, char *title)
{
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		error_mlx_init(map, mlx, "Failed to initialize MiniLibX\n");
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIDTH_WIN, HEIGHT_WIN, title);
	if (!mlx->win_ptr)
		error_mlx_init(map, mlx, "Failed to create window\n");
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, WIDTH_WIN, HEIGHT_WIN);
	mlx->img_data = mlx_get_data_addr(mlx->img_ptr, \
						&mlx->bpp, &mlx->size_line, &mlx->endian);
}

void	iso_projection(t_mlx *mlx, t_map *map)
{
	
}

void	draw_map(t_mlx *mlx, t_map *map)
{
	iso_projection(mlx, map);
}
/* 
void	put_pixel_to_image(t_mlx *mlx, int x, int y, int color)
{
	int	pixel_position;
	
	if (x < 0 || x >= WIDTH_WIN || y < 0 || y >= HEIGHT_WIN)
		return;
	pixel_position = (y * mlx->size_line) + (x * (mlx->bpp / 8));
	mlx->img_data[pixel_position] = color & 0xFF;
	mlx->img_data[pixel_position + 1] = (color >> 8) & 0xFF;
	mlx->img_data[pixel_position + 2] = (color >> 16) & 0xFF;
}

void	zoom_init(t_mlx *mlx)
{
    mlx->panel_width = WIDTH_WIN / 6; 
    mlx->drawable_width = WIDTH_WIN - mlx->panel_width;
    mlx->drawable_height = HEIGHT_WIN;
    if (mlx->drawable_width / mlx->width_iso < mlx->drawable_height / mlx->height_iso)
        mlx->zoom = mlx->drawable_width / mlx->width_iso;
    else
    mlx->zoom = mlx->drawable_height / mlx->height_iso;
	mlx->offset_x = mlx->panel_width + (mlx->drawable_width \
											- mlx->width_iso) / 2;
	mlx->offset_y = (HEIGHT_WIN - mlx->height_iso * mlx->zoom) / 2 \
              								- (mlx->min_y * mlx->zoom) / 2;
}

void iso_position(t_mlx *mlx, t_map *map)
{
    int y;
    int x;
    double min_x = INFINITY;
    double max_x = -INFINITY;
    double min_y = INFINITY;
    double max_y = -INFINITY;

    y = 0;
    while (y < map->height)
    {
        x = 0;
        while (x < map->width)
        {
            map->grid[y][x].x = (x - y) * cos(ISO_ANGLE);
            map->grid[y][x].y = (x + y) * sin(ISO_ANGLE) - map->grid[y][x].z;

            if (map->grid[y][x].x < min_x)
                min_x = map->grid[y][x].x;
            if (map->grid[y][x].x > max_x)
                max_x = map->grid[y][x].x;
            if (map->grid[y][x].y < min_y)
                min_y = map->grid[y][x].y;
            if (map->grid[y][x].y > max_y)
                max_y = map->grid[y][x].y;

            x++;
        }
        y++;
    }

    mlx->width_iso = max_x - min_x;
    mlx->height_iso = max_y - min_y;
    mlx->min_y = min_y;
}

void	draw_map_points(t_mlx *mlx, t_map *map)
{
	int	x;
	int	y;
	t_point projected;
	
	iso_position(mlx, map);
	zoom_init(mlx);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			projected.x = map->grid[y][x].x * mlx->zoom + mlx->offset_x;
			projected.y = map->grid[y][x].y * mlx->zoom + mlx->offset_y;
			projected.color = map->grid[y][x].color;
			put_pixel_to_image(mlx, projected.x, projected.y, projected.color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
}
 */