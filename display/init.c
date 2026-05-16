#include "display.h"

static void	mlx_img_init(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	game->img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img, \
						&game->img.bpp, \
						&game->img.line_len, \
						&game->img.endian);
}

int	game_init(t_game *game)
{
	player_init(&game->player);
	if (map_init(&game->map) == 1)
		return (1);
	game->config.c = WHITE;
	game->config.f = BLACK;
	return (0);
}

int	display_init(t_game *game)
{
	if (game_init(game) == 1)
		return (write(2, "Error\n", 6), 1);
	mlx_img_init(game);
	return (0);
}
