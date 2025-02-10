/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_points.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badal-la <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 17:19:38 by badal-la          #+#    #+#             */
/*   Updated: 2025/02/09 12:03:31 by badal-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

void	init_mlx(t_mlx **mlx, t_map *map, char *title)
{
	*mlx = (t_mlx *)malloc(sizeof(t_mlx));
	if (!*mlx)
		error_mlx_malloc(map, "Failed to allocate memory for mlx structure");
	(*mlx)->width_win = 1600;
	(*mlx)->height_win = 1000;
	(*mlx)->mlx_ptr = mlx_init();
	if (!(*mlx)->mlx_ptr)
		error_mlx_init(map, *mlx, "Failed to initialize MiniLibX\n");
	(*mlx)->win_ptr = mlx_new_window((*mlx)->mlx_ptr, (*mlx)->width_win, \
													(*mlx)->height_win, title);
	if (!(*mlx)->win_ptr)
		error_mlx_init(map, *mlx, "Failed to create window\n");
	(*mlx)->img_ptr = mlx_new_image((*mlx)->mlx_ptr, (*mlx)->width_win, \
														(*mlx)->height_win);
	(*mlx)->img_data = mlx_get_data_addr((*mlx)->img_ptr, \
				&(*mlx)->bits_per_pixel, &(*mlx)->size_line, &(*mlx)->endian);
	(*mlx)->panel_width = (*mlx)->width_win / 6;
	(*mlx)->drawable_with = (*mlx)->width_win - (*mlx)->panel_width;
	(*mlx)->drawable_height = (*mlx)->height_win;
	if ((*mlx)->drawable_with / (map->width + 1) 
								< (*mlx)->drawable_height / (map->height + 1))
		(*mlx)->zoom = (*mlx)->drawable_with / (map->width + 1);
	else
		(*mlx)->zoom = (*mlx)->drawable_height / (map->height + 1);
	(*mlx)->projection_type = 0;
    (*mlx)->altitude_scale = 1;
}

void put_pixel_to_image(t_mlx *mlx, int x, int y, int color)
{
	int	pixel_position;
	
	if (x < 0 || x >= mlx->width_win || y < 0 || y >= mlx->height_win)
		return;
	pixel_position = (y * mlx->size_line) + (x * (mlx->bits_per_pixel / 8));
	mlx->img_data[pixel_position] = color & 0xFF;
	mlx->img_data[pixel_position + 1] = (color >> 8) & 0xFF;
	mlx->img_data[pixel_position + 2] = (color >> 16) & 0xFF;
}

void draw_map_points(t_mlx *mlx, t_map *map)
{
	int	x;
	int	y;
	t_point projected;

	y = 0;
	mlx->offset_x = mlx->panel_width + (mlx->drawable_with 
			- ((map->width - map->height) * cos(ISO_ANGLE) * mlx->zoom)) / 2;
	mlx->offset_y = (mlx->height_win 
			- ((map->width + map->height) * sin(ISO_ANGLE) * mlx->zoom)) / 2;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (mlx->projection_type == 0)
				projected = project_iso(map->grid[y][x], mlx);
			else
				projected = project_perspective(map->grid[y][x], mlx);
			put_pixel_to_image(mlx, projected.x, projected.y, projected.color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
}
