/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:05:12 by badal-la          #+#    #+#             */
/*   Updated: 2025/02/08 12:46:47 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../ft_printf/ft_printf.h"
# include "../libft/libft.h"
# include "../get_next_line/get_next_line_bonus.h"

# include "../minilibx-linux/mlx.h"

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int		color;
}			t_point;

typedef struct s_map
{
	int		width;
	int		height;
	t_point	**grid;
}			t_map;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_data;
	int		width_win;
	int		height_win;
	int		drawable_with;
	int		drawable_height;
	int		panel_width;
	int		offset_x;
	int		offset_y;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		zoom;
}			t_mlx;

int	error(char *message);
int	error_fd_open(char *message, int fd, char *line);
void	free_args_and_exit(void **tab, char *message);
void	error_mlx_malloc(t_map *map, char *message);
void error_mlx_init(t_map *map, t_mlx *mlx, char *message);
void	free_tab_2d_args(char **arg);
//void	free_t_point_args(t_point **grid, int height);
void	free_map(t_map *map);


#endif