/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badal-la <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 17:15:01 by badal-la          #+#    #+#             */
/*   Updated: 2025/02/08 17:15:19 by badal-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

void	fill_width_map(char *file, t_map *map)
{
	int 	fd1;
	char	*line;

	fd1 = open(file, O_RDONLY);
	if (fd1 < 0)
		error_fd("Opening file failed!", map);
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
	
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_fd("Opening file failed!", map);
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '\n' && line[0] != '\0')
			map->height++;
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
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
	if (fd < 0)
		error_fd("Opening file failed!", map);
	map->grid = (t_point **)malloc(sizeof(t_point *) * map->height);
	if (!map->grid)
		error_fd("Malloc map lines failed!", map);
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