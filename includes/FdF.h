/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badal-la <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:05:12 by badal-la          #+#    #+#             */
/*   Updated: 2025/01/28 17:06:34 by badal-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../ft_printf/ft_printf.h"
# include "../libft/libft.h"
# include "../get_next_line/get_next_line_bonus.h"

# include <errno.h>
# include <fcntl.h>
#include <stdio.h>

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
}			t_point;

typedef struct s_info_map
{
	int	max_x;
	int	max_y;
	int	min_z;
	int	max_z;
}			t_info_map;


int	error(char *message);

int	error_fd_open(char *message, int fd, char *line);

void	free_args_and_exit(char **tab, char *message);

#endif