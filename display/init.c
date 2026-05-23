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

static bool	xpm_init(t_game *game, t_img *dst, char *path)
{
	int	width;
	int	height;

	dst->img = mlx_xpm_file_to_image(game->mlx, path, &width, &height);
	if (dst->img == NULL)
		return (false);
	dst->addr = mlx_get_data_addr(dst->img,
			&dst->bpp, &dst->line_len, &dst->endian);
	return (true);
}

static bool	texture_load(t_game *game)
{
	// TODO: configを受取るようにして、xpm_initの引数を変更する
	if (!xpm_init(game, &game->texture.no, "mock_textures/mock_north.xpm"))
		return (false);
	if (!xpm_init(game, &game->texture.so, "mock_textures/mock_south.xpm"))
		return (false);
	if (!xpm_init(game, &game->texture.we, "mock_textures/mock_west.xpm"))
		return (false);
	if (!xpm_init(game, &game->texture.ea, "mock_textures/mock_east.xpm"))
		return (false);
	return (true);
}

int	display_init(t_game *game)
{
	if (game_init(game) == false)
		return (write(2, "Error\n", 6), 1);
	mlx_img_init(game);
	if (texture_load(game) == false)
		return (write(2, "Error\n", 6), 1);
	return (0);
}
