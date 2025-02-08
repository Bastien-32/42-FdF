/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badal-la <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:23:24 by badal-la          #+#    #+#             */
/*   Updated: 2025/02/08 16:40:17 by badal-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

int	error(char *message)
{
	ft_printf("Error\n");
	if (errno)
		perror(message);
	else
		ft_printf("%s\n", message);
	exit (1);
}

void	error_fd(char *message, t_map *map)
{
		free(map);
		error(message);
}

int	error_fd_open(char *message, int fd, char *line)
{
	ft_printf("Error\n");
	if (errno)
		perror(message);
	else
		ft_printf("%s\n", message);
	free(line);
	close(fd);
	exit (1);
}

void	free_args_and_exit(void **tab, char *message)
{
	int	i;

	if (!tab)
		return ;
	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
	error(message);
}

void	error_mlx_malloc(t_map *map, char *message)
{
	free_map(map);
	error(message);
}

void	error_mlx_init(t_map *map, t_mlx *mlx, char *message)
{
	free_map(map);
	free(mlx);
	error(message);
}

//a deplacer dans une autre fichier
void	free_tab_2d_args(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		free(arg[i]);
		i++;
	}
	free(arg);
}

//a deplacer dans une autre fichier
void	free_map(t_map *map)
{
	int i;

	if (!map)
		return;
	if (!map->grid)
	{
		printf("DEBUG: map->grid n'est pas alloué\n");
		free(map);
		return;
	}
	i = 0;
	printf("map height = %d\n", map->height);
	while (i < map->height)
	{
		if (map->grid[i])
		{
			printf("DEBUG: Libération de map->grid[%d]\n", i);
			free(map->grid[i]);
		}
		else
			printf("DEBUG: map->grid[%d] n'est pas alloué\n", i);
		i++;
	}

	printf("DEBUG: Libération de map->grid\n");
	free(map->grid);
	map->grid = NULL;

	printf("DEBUG: Libération de la structure map\n");
	free(map);
}