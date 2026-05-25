#include "display.h"

static bool	mlx_img_init(t_game *game)
{
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		return (false);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	if (game->win == NULL)
		return (false);
	game->img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (game->img.img == NULL)
		return (false);
	game->img.addr = mlx_get_data_addr(game->img.img, \
						&game->img.bpp, \
						&game->img.line_len, \
						&game->img.endian);
	return (true);
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

static bool	texture_load(t_game *game, t_config *config)
{
	// TODO: configを受取るようにして、xpm_initの引数を変更する
	if (!xpm_init(game, &game->texture.no, config->no))
		return (false);
	if (!xpm_init(game, &game->texture.so, config->so))
		return (false);
	if (!xpm_init(game, &game->texture.we, config->we))
		return (false);
	if (!xpm_init(game, &game->texture.ea, config->ea))
		return (false);
	return (true);
}

bool	display_init(t_game *game, t_info *info)
{
	game->map = info->map_info; // max width height 必要ならすべて渡す不要ならdisplayがわのmap の型はchar **mapにする
	game->player = info->player;
	game->texture.f = info->config.f;
	game->texture.c = info->config.c;

	// game_init は多分失敗しないようにできるから不要になる
	// if (game_init(game) == false)
	// {
	// 	ft_putstr_fd("Error\nFailed to initialize game data\n", 2);
	// 	return (false);
	// }
	if (mlx_img_init(game) == false)
	{
		ft_putstr_fd("Error\nFailed to initialize mlx image\n", 2);
		return (false);
	}
	if (texture_load(game, &info->config) == false)
	{
		ft_putstr_fd("Error\nFailed to load textures\n", 2);
		return (false);
	}
	return (true);
}
