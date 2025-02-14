/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badal-la <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:02:32 by badal-la          #+#    #+#             */
/*   Updated: 2025/02/13 09:35:48 by badal-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

int	main(int argc, char **argv)
{
	t_map	*map;
	t_mlx	mlx;

	if (argc != 2)
        error("Usage: ./fdf map.fdf");
    map = parse_map(argv[1]);
	init_mlx(&mlx, map, "FdF");
	draw_map_lines(&mlx, map);
	mlx.map = map;
	mlx_hook(mlx.win_ptr, 17, 0, close_program, &mlx);
	mlx_hook(mlx.win_ptr, 2, 1L << 0, key_press, &mlx); 
	mlx_loop(mlx.mlx_ptr);
	return (0);
}

