/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badal-la <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:05:12 by badal-la          #+#    #+#             */
/*   Updated: 2025/02/08 17:41:39 by badal-la         ###   ########.fr       */
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
	t_map	*map;
}			t_mlx;

typedef struct s_bresenham
{
    int		dx;
    int		dy;
    int		sx;
    int		sy;
    int		err;
    int		e2;
}   t_bresenham;

int	error(char *message);
void	error_fd(char *message, t_map *map);
int	error_fd_open(char *message, int fd, char *line);
void	free_args_and_exit(void **tab, char *message);
void	error_mlx_malloc(t_map *map, char *message);
void error_mlx_init(t_map *map, t_mlx *mlx, char *message);
void	free_tab_2d_args(char **arg);
//void	free_t_point_args(t_point **grid, int height);
void	free_map(t_map *map);

/* ****************************************************************************
								commands_in_win
**************************************************************************** */

int close_program(t_mlx *mlx);
int key_press(int keycode, t_mlx *mlx);

/* ****************************************************************************
								  parse_map
**************************************************************************** */

void	fill_width_map(char *file, t_map *map);
void	fill_height_map(char *file, t_map *map);
void	fill_point(char *line, t_map *map, int y);
void	fill_map(char *file, t_map *map);
t_map	*parse_map(char *file);

/* ****************************************************************************
								draw_map_points
**************************************************************************** */

void	init_mlx(t_mlx **mlx, t_map *map, char *title);
void put_pixel_to_image(t_mlx *mlx, int x, int y, int color);
void draw_map_points(t_mlx *mlx, t_map *map);

/* ****************************************************************************
								draw_map_lines
**************************************************************************** */

void    init_bresenham(t_bresenham *b, t_point p1, t_point p2);
void    draw_line(t_mlx *mlx, t_point p1, t_point p2);
void    draw_map_lines(t_mlx *mlx, t_map *map);

#endif