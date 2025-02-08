/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_in_win.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:05:56 by student           #+#    #+#             */
/*   Updated: 2025/02/08 13:05:59 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

int close_program(t_mlx *mlx, t_map *map)
{
	if (mlx->img_ptr)
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr);
	if (mlx->win_ptr)
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	if (mlx->mlx_ptr)
		free(mlx->mlx_ptr);
	if (map)
		free_map(map);
	if (mlx)
		free(mlx);
	exit(0);
}

int key_press(int keycode, t_mlx *mlx)
{
	if (keycode == 53 || keycode == 65307)
		close_program(mlx, NULL);
	return (0);
}