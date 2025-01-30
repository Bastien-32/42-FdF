/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badal-la <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:02:32 by badal-la          #+#    #+#             */
/*   Updated: 2025/01/28 18:10:53 by badal-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

t_point	**fill_points(char *line, t_point **point, int i, int j)
{
	while (line[j])
	{
		if (line[j] == ' ')
			j++;
		else
		{
			point[i][j].x = j;
			point[i][j].y = i;
			point[i][j].z = ft_atoi(&line[j]);
			while (line[j] && line[j] != ' ')
				j++;
		}
	}
	return (point);
}

t_point	**read_and_extract(char *file, t_point **point)
{
	int		fd;
	char	*line;
	int		i;
	int		j;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error("Could not open file"); // si je l'ai vérifié avant est ce necessaire ou bien la réouverture peut mal s'effectuer?
	i = 0;
	while (get_next_line(fd) > 0)
	{
		j = 0;
		line = get_next_line(fd);
		point = fill_points(line, point, i, j);
		i++;
	}
	close(fd);
	return (point);
}

void	check_and_info_map(char *file, t_info_map *info)
{
	int			fd;
	char		*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error("Could not open file");
	line = get_next_line(fd);
	if (!line)
		error_fd_open("Map is empty\n", fd, NULL);
	info->max_x = ft_nwords(line, ' ');
	info->max_y = 1;
	info->min_z = 0;
	info->max_z = 0;
	free(line);
	while (line)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_nwords(line, ' ') != (*info).max_x)
			error_fd_open("Map is not valid (Number columns)\n", fd, line);
		(*info).max_y++;
		free(line);
	}
	close(fd);
}

int main(int ac, char **av)
{
	t_info_map	info;
	t_point		**point;

	**point = 0;
	errno = 0;
	if (ac != 2)
		error("Usage: ./FdF map.fdf");
	check_and_info_map(av[1], &info);
	read_and_extract(av[1], point);
	int i = 0;
	int j = 0;
	while (point[j])
	{
		i = 0;
		while (point[j][i].x != 0 || point[j][i].y != 0 || point[j][i].z != 0)
		{
			ft_printf("%d ", point[j][i].z);
			i++;
		}
		ft_printf("\n");
		j++;
	}
}



/* 
#extraire les points dans une structure
#			sorties d'erreurs :	
#					- fd pas trouvé
#					- fichier vide
#					- check meme nombre de points pour toutes les ligne
#					- check si les points sont des nombres entiers
#						(négatifs ok?)
#						(limites int?)
#extraire les points dans une structure

relier les points
mettre z en relief
rendu visuel
gestion fenetre :
	- rotation
	- deplacement
	- zoom
	- couleur
	- menu (infos)
 */