/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:02:32 by badal-la          #+#    #+#             */
/*   Updated: 2025/02/06 16:51:30 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

#define WIDTH 800
#define HEIGHT 600

void	fill_width_map(char *file, t_map *map)
{
	int 	fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error("Opening file failed!");
	line = get_next_line(fd);
	printf("line = %s", line);
	map->width = ft_nwords(line, ' ');
	printf("width = %d\n", map->width);
	free(line);
	close(fd);
}

void	fill_height_map(char *file, t_map *map)
{
	int 	fd;
	char	*line;
	int		line_count = 0;
	
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error("Opening file failed!");
	line = get_next_line(fd);
	printf("line in heigh = %s", line);
	while (line)
	{
		line_count++;
		printf("DEBUG: Ligne %d = %s\n", line_count, line);
		if (ft_nwords(line, ' ') != map->width)
		{
			printf("line = %s \nnwords line = %d | width = %d\n", line, ft_nwords(line, ' '), map->width);
			error_fd_open("Map is not rectangle", fd, line);
		}
		if (line[0] != '\n' && line[0] != '\0')
			map->height++;
		free(line);
		line = get_next_line(fd);
	}
	printf("DEBUG: Nombre total de lignes lues = %d\n", line_count);
	close(fd);
}

void	fill_point(char *line, t_map *map, int x)
{
	int		y;
	char	**split;
	char	**token;
	
	y = 0;
	split = ft_split(line, ' ');
	while (y < map->width)
	{
		printf("Token exploited : %s\n", split[y]);
		map->grid[x][y].x = x;
		map->grid[x][y].y = y;
		if (ft_strchr(split[y], ','))
		{
			printf("token with ','\n");
			token = ft_split(split[y], ',');
			map->grid[x][y].z = ft_atoi(token[0]);
			map->grid[x][y].color = ft_atoi_base(token[1], "0123456789abcdef");
			printf("x = %d | y = %d | z = %d | color = %x \n", map->grid[x][y].x, map->grid[x][y].y, map->grid[x][y].z, map->grid[x][y].color);
		}
		else
		{
			printf("token without ','\n");
			map->grid[x][y].z = ft_atoi(split[y]);
			map->grid[x][y].color = 0xFFFFFF;
			printf("x = %d | y = %d | z = %d | color = %x \n", map->grid[x][y].x, map->grid[x][y].y, map->grid[x][y].z, map->grid[x][y].color);
		}
		y++;
	}
	printf("line ok\n");
}

void	fill_map(char *file, t_map *map)
{
	int		x;
	int		fd;
	char	*line;
	
	fd = open(file, O_RDONLY);
	map->grid = (t_point **)malloc(sizeof(t_point *) * map->height);
	if (!map->grid)
		error("Malloc map failed");
	x = 0;
	while (x < map->height)
	{
		line = get_next_line(fd);
		map->grid[x] = (t_point *)malloc(sizeof(t_point) * map->width);
		if (!map->grid[x])
			free_args_and_exit((void **)map->grid, "Malloc map failed");
		printf("Line = %s | x = %d\n", line, x);
		fill_point(line, map, x);
		free(line);
		x++;
	}
	close(fd);
}

t_map	*parse_map(char *file)
{
	t_map	*map;
	
	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		error("Malloc map failed");
	ft_bzero(map, sizeof(t_map));
	fill_width_map(file, map);
	fill_height_map(file, map);
	fill_map(file, map);
	return (map);
}

int	main(int argc, char **argv)
{
	t_map	*map;

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
			//free(map->grid[x][y]);
			y++;
		}
		printf("\n");
		x++;
	}
	free(map->grid);
	
	return (0);
}

