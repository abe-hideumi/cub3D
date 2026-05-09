
#include "habe.h"

int	key_hook(int keycode, void *param)
{
	t_game *game;

	game = (t_game *)param;
	if (keycode == KEY_ESC)
		close_hook(game);
	return (0);
}

int	close_hook(t_game *game)
{
	mlx_destroy_image(game->mlx, game->img.img);
	mlx_destroy_window(game->mlx, game->win);
	free(game->map.map[0]);
	free(game->map.map[1]);
	free(game->map.map[2]);
	free(game->map.map[3]);
	free(game->map.map[4]);
	free(game->map.map);
	exit(0);
}
