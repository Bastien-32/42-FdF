/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:02:32 by badal-la          #+#    #+#             */
/*   Updated: 2025/02/08 12:49:53 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

#define WIDTH 800
#define HEIGHT 600

void	fill_width_map(char *file, t_map *map)
{
	int 	fd1;
	char	*line;

	fd1 = open(file, O_RDONLY);
	if (fd1 < 0)
	{
		free(map);
		error("Opening file failed!");
	}
	line = get_next_line(fd1);
	map->width = ft_nwords(line, ' ');
	while (line)
	{
		if (ft_nwords(line, ' ') != map->width)
		{
			free(map);
			error_fd_open("Map is not rectangle", fd1, line);
		}
		free(line);
		line = get_next_line(fd1);
	}
	if (line)
		free(line);
	close(fd1);
}

void	fill_height_map(char *file, t_map *map)
{
	int 	fd;
	char	*line;
	int		line_count = 0;
	
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		free(map);
		error("Opening file failed!");
	}
	line = get_next_line(fd);
	while (line)
	{
		line_count++;
		if (line[0] != '\n' && line[0] != '\0')
			map->height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	fill_point(char *line, t_map *map, int y)
{
	int		x;
	char	**split;
	char	**token;
	
	x = 0;
	split = ft_split(line, ' ');
	while (x < map->width)
	{
		map->grid[y][x].x = x;
		map->grid[y][x].y = y;
		if (ft_strchr(split[x], ','))
		{
			token = ft_split(split[x], ',');
			map->grid[y][x].z = ft_atoi(token[0]);
			map->grid[y][x].color = ft_atoi_base(token[1], "0123456789abcdef");
			free_tab_2d_args(token);
		}
		else
		{
			map->grid[y][x].z = ft_atoi(split[x]);
			map->grid[y][x].color = 0xFFFFFF;
		}
		x++;
	}
	free_tab_2d_args(split);
}

void	fill_map(char *file, t_map *map)
{
	int		y;
	int		fd;
	char	*line;
	
	fd = open(file, O_RDONLY);
	map->grid = (t_point **)malloc(sizeof(t_point *) * map->height);
	if (!map->grid)
		error("Malloc map line failed");
	y = 0;
	while (y < map->height)
	{
		line = get_next_line(fd);
		map->grid[y] = (t_point *)malloc(sizeof(t_point) * map->width);
		if (!map->grid[y])
			free_args_and_exit((void **)map->grid, "Malloc map column failed");
		fill_point(line, map, y);
		free(line);
		y++;
	}
	close(fd);
}

t_map	*parse_map(char *file)
{
	t_map	*map;
	
	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		error("Malloc info map failed");
	ft_bzero(map, sizeof(t_map));
	fill_width_map(file, map);
	fill_height_map(file, map);
	fill_map(file, map);
	return (map);
}

void	init_mlx(t_mlx **mlx, t_map *map, char *title)
{
	*mlx = (t_mlx *)malloc(sizeof(t_mlx));
	if (!*mlx)
		error_mlx_malloc(map, "Failed to allocate memory for mlx structure");
	(*mlx)->width_win = 1600;
	(*mlx)->height_win = 1200;
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
	if ((*mlx)->width_win / (map->width + 1) 
									< (*mlx)->height_win / (map->height + 1))
		(*mlx)->zoom = (*mlx)->width_win / (map->width + 1);
	else
		(*mlx)->zoom = (*mlx)->height_win / (map->height + 1);
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

	y = 0;
	mlx->offset_x = mlx->panel_width
					+ (mlx->drawable_with - (map->width - 1) * mlx->zoom) / 2;
	mlx->offset_y = (mlx->height_win - (map->height - 1) * mlx->zoom) / 2;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			int draw_x = map->grid[y][x].x * mlx->zoom + mlx->offset_x;
			int draw_y = map->grid[y][x].y * mlx->zoom + mlx->offset_y;
			put_pixel_to_image(mlx, draw_x, draw_y, map->grid[y][x].color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
}

int	main(int argc, char **argv)
{
	t_map	*map;
	t_mlx	*mlx;

	if (argc != 2)
        error("Usage: ./fdf map.fdf");
    map = parse_map(argv[1]);
	
	int x = 0;
	
	while (x < map->height)
	{
		int y = 0;
		while (y < map->width)
		{
			printf("%d,%X ", map->grid[x][y].z, map->grid[x][y].color);
			y++;
		}
		printf("\n");
		x++;
	}
	init_mlx(&mlx, map, "FdF");
	draw_map_points(mlx, map);
	mlx_loop(mlx->mlx_ptr);
	free_map(map);
	return (0);
}

