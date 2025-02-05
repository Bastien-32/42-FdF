/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badal-la <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:02:32 by badal-la          #+#    #+#             */
/*   Updated: 2025/02/05 16:01:06 by badal-la         ###   ########.fr       */
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
		error("Opening file failed");
	line = get_next_line(fd);
	printf("line = %s", line);
	map->width = ft_nwords(line, ' ');
	printf("width = %d\n", map->width);
	close(fd);
}
void	fill_height_map(char *file, t_map *map)
{
	int 	fd;
	char	*line;
	int		line_count = 0;  // Compteur de lignes lues
	
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error("Opening file failed");

	line = get_next_line(fd);
	while (line)
	{
		line_count++; // Incrémentation du compteur
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
	printf("DEBUG: Nombre total de lignes lues = %d\n", line_count); // Vérification finale
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
	return (map);
}

int	main(int argc, char **argv)
{
	t_map	*map;

	if (argc != 2)
        error("Usage: ./fdf map.fdf");
    map = parse_map(argv[1]);
	printf("width = %d | height = %d\n", map->width, map->height);


	return (0);
}

