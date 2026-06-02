/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knomura <knomura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 13:39:21 by knomura           #+#    #+#             */
/*   Updated: 2026/06/02 18:36:04 by knomura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display/display.h"

int	main(int ac, char *av[])
{
	t_game	game;
	t_info	info;

	if (ac != 2)
		return (printf("Usage: ./cub3D <map.cub>\n"), 1);
	parse_cub_file(av[1], &info);
	ft_memset(&game, 0, sizeof(t_game));
	if (display_init(&game, &info) == false)
		return (1);
	game_render(&game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, DESTROY_NOTIFY, 0, close_hook, &game);
	mlx_loop_hook(game.mlx, key_press, &game);
	mlx_loop(game.mlx);
	return (0);
}
