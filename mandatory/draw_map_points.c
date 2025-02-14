/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_points.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badal-la <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 17:19:38 by badal-la          #+#    #+#             */
/*   Updated: 2025/02/14 14:37:08 by badal-la         ###   ########.fr       */
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

void	mean_xyz(t_map *map)
{
	int	y;
	int	x;
	
	y = 0;
	map->mean_x = 0;
	map->mean_y = 0;
	map->mean_z = 0;
	while(y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			map->mean_x += map->grid[y][x].x;
			map->mean_y += map->grid[y][x].y;
			map->mean_z += map->grid[y][x].z;
			x++;
		}
		y++;
	}
	map->mean_x = map->mean_x / (map->height * map->width);
	map->mean_y = map->mean_y / (map->height * map->width);
	map->mean_z = map->mean_z / (map->height * map->width);
	//map->mean_z = (map->max_z - map->min_z) / 2;
	ft_printf("mx = %d, my = %d, mz = %d\n", map->mean_x, map->mean_y, map->mean_z);
}

void	iso_projection(t_mlx *mlx, t_map *map)
{
	int	temp_x;
	int	temp_y;
	int	temp_z;
	int	y;
	int	x;
	
	y = 0;
	while(y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			temp_x = map->grid[y][x].x - map->mean_x;
			temp_y = map->grid[y][x].y - map->mean_y;
			temp_z = map->grid[y][x].z - map->mean_z;
			map->grid[y][x].x_proj = (0.866 * temp_x - 0.866 * temp_y) * mlx->zoom;
			map->grid[y][x].y_proj = (0.5 * temp_x + 0.5 * temp_y - temp_z) * mlx->zoom;
			x++;
		}
		y++;
	}
}
/*
void fill_width_and_height_proj(t_mlx *mlx, t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (y == 0 && x == 0)
			{
				mlx->min_x_proj = map->grid[y][x].x_proj;
				mlx->max_x_proj = map->grid[y][x].x_proj;
				mlx->min_y_proj = map->grid[y][x].y_proj;
				mlx->max_y_proj = map->grid[y][x].y_proj;
			}
			else if (map->grid[y][x].x_proj < mlx->min_x_proj)
				mlx->min_x_proj = map->grid[y][x].x_proj;
			else if (map->grid[y][x].y_proj < mlx->min_y_proj)
				mlx->min_y_proj = map->grid[y][x].y_proj;
			else if (map->grid[y][x].x_proj > mlx->max_x_proj)
				mlx->max_x_proj = map->grid[y][x].x_proj;
			else if (map->grid[y][x].y_proj > mlx->max_y_proj)
				mlx->max_y_proj = map->grid[y][x].y_proj;
			x++;
		}
		y++;
	}
	printf("mlx->min_x_proj = %d mlx->min_y_proj = %d mlx->max_x_proj = %d mlx->max_y_proj = %d\n", mlx->min_x_proj, mlx->min_y_proj, mlx->max_x_proj, mlx->max_y_proj);
	mlx->width_proj = mlx->max_x_proj - mlx->min_x_proj;
	mlx->height_proj = mlx->max_y_proj - mlx->min_y_proj;
	printf("widthp = %f, height proj = %f\n", mlx->width_proj, mlx->height_proj);
}*/

/*void	zoom_init(t_mlx *mlx, t_map *map)
{
	float a;
	float b;
	
	mlx->panel_width = WIDTH_WIN / 6; 
	mlx->drawable_width = WIDTH_WIN - mlx->panel_width;
	mlx->drawable_height = HEIGHT_WIN;
	a = (float)(- 0.866f * ((float)(map->width) - 1.0f));
	b = (float)(0.866f * ((float)(map->height) - 1.0f));
	fill_width_and_height_proj(mlx, map);
	printf(" a = %f b = %f\n", a, b);
	mlx->zoom = (int)((float)mlx->drawable_width / fabs(a - b));
	ft_printf("mlx->zoom %d\n", mlx->zoom);
	
}*/
void	zoom_init(t_mlx *mlx, t_map *map)
{
	float a;
	float b;
	
	mlx->panel_width = WIDTH_WIN / 6; 
	mlx->drawable_width = WIDTH_WIN - mlx->panel_width;
	mlx->drawable_height = HEIGHT_WIN;
	a = (float)(- 0.866f * ((float)(map->width) - 1.0f));
	b = (float)(0.866f * ((float)(map->height) - 1.0f));
	ft_printf("dw = %d dh = %d\n", mlx->drawable_width,mlx->drawable_height);
	mlx->zoom = (int)((float)mlx->drawable_width / fabs(a - b));
	ft_printf("mlx->zoom %d\n", mlx->zoom);
	//mlx->zoom = 40;
}

/*void	zoom_init(t_mlx *mlx, t_map *map)
{
	int	max_dimension;

	mlx->zoom = 1;
	mlx->panel_width = WIDTH_WIN / 6; 
	mlx->drawable_width = WIDTH_WIN - mlx->panel_width;
	mlx->drawable_height = HEIGHT_WIN;
	ft_printf("w = %d h = %d\n", map->width, map->height);
	if (map->width > map->height)
		max_dimension = map->width;
	else
		max_dimension = map->height;
	ft_printf("max_dim= %d\n", max_dimension);
	ft_printf("dw = %d dh = %d\n", mlx->drawable_width,mlx->drawable_height);
	if ((mlx->drawable_width / max_dimension)
		< ((mlx->drawable_height / max_dimension) / 2.5))
		mlx->zoom = mlx->drawable_width / max_dimension;
	else
		mlx->zoom = (mlx->drawable_height / max_dimension) / 2.5;
	printf("mlx->zoom %d\n", mlx->zoom);
	mlx->zoom = 30;
}*/

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

void	draw_map_points(t_mlx *mlx, t_map *map)
{
	int	x;
	int	y;
	t_point projected;

	mean_xyz(map);
	zoom_init(mlx, map);
	iso_projection(mlx, map);
	//fill_width_and_height_proj(mlx, map);
	mlx->offset_x = mlx->panel_width + mlx->drawable_width / 2 - (map->mean_x - map->mean_y) * 0.866;
	mlx->offset_y = mlx->drawable_height / 2 - (map->mean_y) * 0.5;
	
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			projected.x = map->grid[y][x].x_proj + mlx->offset_x;
			projected.y = map->grid[y][x].y_proj + mlx->offset_y;
			projected.color = map->grid[y][x].color;
			put_pixel_to_image(mlx, projected.x, projected.y, projected.color);
			x++;
		}
		y++;
	}
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