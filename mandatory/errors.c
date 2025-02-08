/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:23:24 by badal-la          #+#    #+#             */
/*   Updated: 2025/02/08 12:17:12 by student          ###   ########.fr       */
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

	i = 0;
	while (i < map->height)
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
	free(map);
}