/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badal-la <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:02:32 by badal-la          #+#    #+#             */
/*   Updated: 2025/02/04 19:14:29 by badal-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

#define WIDTH 800
#define HEIGHT 600

void free_split(char **split)
{
    int i = 0;
    while (split[i])
    {
        free(split[i]);
        i++;
    }
    free(split);
}

void	count_lines(char *file, t_map *map)
{
	int		fd;
	char	*line;

	map->height = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error("Error\nCould not open file\n");
	line = get_next_line(fd);
	while (line)
	{
		map->height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (map->height == 0)
		error("Error\nEmpty file\n");
}

int	ft_split_count(char *line, char c)
{
	int		count;
	char	**split;

	split = ft_split(line, c);
	if (!split)
		error("Error\nMalloc failed\n");
	count = 0;
	while(split[count])
		count++;
	free(split);
	return (count);
}

void	count_columns(char *file, t_map *map)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error("Error\nCould not open file\n");
	line = get_next_line(fd);
	if (!line)
		error("Error\nInvalid map format\n");
	map->width = ft_split_count(line, ' ');
	free(line);
	close(fd);
}

void	allocate_grid(t_map *map)
{
	int	y;

	map->grid = malloc(sizeof(t_point *) * map->height);
	if (!map->grid)
		error("Error\nMalloc failed\n");
	y = 0;
	while (y < map->height)
	{
		map->grid[y] = malloc(sizeof(t_point) * map->width);
		if (!map->grid[y])
			free_args_and_exit((char **)map->grid, "Error\nMalloc failed\n");
		y++;
	}
}

void	parse_point(t_point *point, char *token, int x, int y)
{
	char	**split;
	int		count;
	
	split = ft_split(token, ',');
	if (!split || !split[0])
	{
		free(split);
		return;
	}
	count = 0;
	while (split[count])
		count++;
	point->x = x;
	point->y = y;
	point->z = ft_atoi(split[0]);
	free(split[0]);
	if (count > 1)
	{
		point->color = ft_atoi_base(split[1], "0123456789ABCDEF");
		free(split[1]);
	}
	else
		point->color = 0xFFFFFF;
}

void    apply_iso(t_point *p)
{
    int previous_x = p->x;
    int previous_y = p->y;

    p->x = (previous_x - previous_y) * cos(0.523599);
    p->y = (previous_x + previous_y) * sin(0.523599) - p->z;
}

void	parse_line(char *line, t_point *row, int y)
{
	int		x;
	char	**tokens;

	tokens = ft_split(line, ' ');
	x = 0;
	while (tokens[x])
	{
		parse_point(&row[x], tokens[x], x * 20, y * 20);
		apply_iso(&row[x]);
		free(tokens[x]);
		x++;
	}
	free(tokens);
}

void	fill_map_lines(int fd, t_map *map)
{
	int		y;
	char	*line;

	y = 0;
	line = get_next_line(fd);
	while (y < map->height && line)
	{
		parse_line(line, map->grid[y], y);
		free(line);
		y++;
		line = get_next_line(fd);
	}
}

void	parse_map(char *file, t_map *map)
{
	int	fd;

	count_lines(file, map);
	count_columns(file, map);
	if (map->height == 0 || map->width == 0)
    error("Error\nInvalid map dimensions\n");
	allocate_grid(map);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error("Error\nCould not open file\n");
	fill_map_lines(fd, map);
	close(fd);
}
void	draw_map(void *mlx, void *win, t_map *map)
{
	int x;
	int y;

	printf("Drawing map...\n"); 
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			mlx_pixel_put(mlx, win, map->grid[y][x].x, map->grid[y][x].y, map->grid[y][x].color);
			printf("Point %d,%d → X:%d Y:%d Color:%X\n", x, y, map->grid[y][x].x, map->grid[y][x].y, map->grid[y][x].color);
			x++;
		}
		y++;
	}
}


int	main(int argc, char **argv)
{
	void	*mlx;
	void	*win;
	t_map	map;

	if (argc != 2)
        error("Usage: ./fdf map.fdf");
    parse_map(argv[1], &map);

	mlx = mlx_init();
	win = mlx_new_window(mlx, WIDTH, HEIGHT, "FDF - Affichage Map");

	// Dessiner la map
	draw_map(mlx, win, &map);

	mlx_loop(mlx);
	return (0);
}
/* 
t_map	parse_map(char *file, t_map *map)
{
	int		fd;
	char	*line;
	int		i;
	t_map	*map;
	
	
	count_line(file, map);
	map->grid = malloc(sizeof(t_point) * (map->height + 1));
	if (!map->grid)
		error("Error\nMalloc failed\n");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error("Error\nCould not open file\n");
	map->width = 0;
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (map->width == 0)
			map->width = ft_strlen(line);
		else if (map->width != ft_strlen(line))
			error("Error\nMap is not rectangular\n");
		map->grid[i] = malloc(sizeof(t_point) * map->width);
		if (!map->grid[i])
			error("Error\nMalloc failed\n");
		parse_line(line, map->grid[i]);
		free(line);
		if (!line)
			break ;
		i++;
	}
	close(fd);
	return (map);
}

int main(int argc, char **argv)
{
	t_map	map;
	
	if (argc != 2)
		error("Error\nWrong number of arguments\n \
			Usage: ./so_long [map.ber]\n");
	parse_map(argv[1], &map);
	check_map(&map);
	return (0);
} */