/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 13:39:21 by knomura           #+#    #+#             */
/*   Updated: 2026/06/03 19:50:00 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display/display.h"

int	main(int ac, char *av[])
{
	t_game	game;
	t_info	info;

	if (ac != 2)
		return (printf("acないよ\n"), 1);
	parse_cub_file(av[1], &info);
	ft_memset(&game, 0, sizeof(t_game));
	display_init(&game, &info);
	game_render(&game);
	mlx_hook(game.win, KEY_PRESS, 1L << 0, key_down, &game);
	mlx_hook(game.win, KEY_RELEASE, 1L << 1, key_up, &game);
	mlx_hook(game.win, DESTROY_NOTIFY, 0, close_hook, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
