#include "cub3D.h"

int	main(int ac, char *av[])
{
	t_game	game;

	(void)ac;
	(void)av;
	ft_memset(&game, 0, sizeof(t_game));
	if (display_init(&game) == 1)
		return (1);
	game_render(&game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, DESTROY_NOTIFY, 0, close_hook, &game);
	mlx_loop_hook(game.mlx, key_press, &game);
	mlx_loop(game.mlx);
	return (0);
}
