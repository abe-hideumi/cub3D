
#include "habe.h"

static void	player_init(t_player *player)
{
	player->pos_x = 4;
	player->pos_y = 3;
	player->dir_x = 0;
	player->dir_y = -1;
	player->plane_x = 1;
	player->plane_y = 0;
}

static int	map_init(t_map *map)
{
	map->map = malloc(sizeof(char **) * 6);
	if (map->map == NULL)
		return (1);
	map->map[0] = ft_strdup("111111");
	if (map->map[0] == NULL)
		return (free(map->map), 1);
	map->map[1] = ft_strdup("100101");
	if (map->map[1] == NULL)
		return (free(map->map[0]), free(map->map), 1);
	map->map[2] = ft_strdup("101001");
	if (map->map[2] == NULL)
		return (free(map->map[0]), free(map->map[1]), free(map->map), 1);
	map->map[3] = ft_strdup("1100N1");
	if (map->map[3] == NULL)
		return (free(map->map[0]), free(map->map[1]), free(map->map[2]), free(map->map), 1);
	map->map[4] = ft_strdup("111111");
	if (map->map[4] == NULL)
		return (free(map->map[0]), free(map->map[1]), free(map->map[2]), free(map->map[3]), free(map->map), 1);
	map->map[5] = NULL;
	map->width = 6;
	map->height = 5;
	return (0);
}

static int	game_init(t_game *game)
{
	player_init(&game->player);
	if (map_init(&game->map) == 1)
		return (1);
	game->ceiling_color = WHITE;
	game->floor_color = BLACK;
	return (0);
}

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

int	display_init(t_game *game)
{
	if (game_init(game) == 1)
		return (write(2, "Error\n", 6), 1);
	mlx_img_init(game);
	return (0);
}
