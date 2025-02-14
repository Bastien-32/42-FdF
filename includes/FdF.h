/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badal-la <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:05:12 by badal-la          #+#    #+#             */
/*   Updated: 2025/02/13 15:49:40 by badal-la         ###   ########.fr       */
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

# define ISO_ANGLE 0.523599  // 30° en radians
# define PERSPECTIVE_ANGLE 0.785398 // 45° en radians

# define WIDTH_WIN 1600
# define HEIGHT_WIN 1000

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int		color;
	int		x_proj;
	int		y_proj;
}			t_point;

typedef struct s_map
{
	int		width;
	int		height;
	int		min_z;
	int		max_z;
	int		mean_x;
	int		mean_y;
	int		mean_z;
	t_point	**grid;
}			t_map;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_data;
	int		size_line;
	int		endian;
	int		panel_width;
	int		drawable_width;
	int		drawable_height;
	int		offset_x;
	int		offset_y;
	int		bpp;
	int		zoom;
	double	width_proj;
	double	height_proj;
	int	min_x_proj;
	int	max_x_proj;	
	int	min_y_proj;
	int	max_y_proj;
	double	min_y;
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

int		error(char *message);
void	error_fd(char *message, t_map *map);
int		error_fd_open(char *message, int fd, char *line);
void	free_args_and_exit(void **tab, char *message);
void	error_mlx_malloc(t_map *map, char *message);
void 	error_mlx_init(t_map *map, t_mlx *mlx, char *message);
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
void	fill_z_max_and_min(t_map *map);

/* ****************************************************************************
								draw_map_points
**************************************************************************** */

void	init_mlx(t_mlx *mlx, t_map *map, char *title);
void	mean_xyz(t_map *map);
void	iso_projection(t_mlx *mlx, t_map *map);
void	zoom_init(t_mlx *mlx, t_map *map);
void	put_pixel_to_image(t_mlx *mlx, int x, int y, int color);
void	draw_map_points(t_mlx *mlx, t_map *map);

/* ****************************************************************************
								draw_map_lines
**************************************************************************** */

void    init_bresenham(t_bresenham *b, t_point p1, t_point p2);
t_point project_iso(t_point p, t_mlx *mlx);
t_point project_perspective(t_point p, t_mlx *mlx);
void    draw_line(t_mlx *mlx, t_point p1, t_point p2);
void    draw_map_lines(t_mlx *mlx, t_map *map);

#endif