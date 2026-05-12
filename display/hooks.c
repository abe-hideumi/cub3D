
#include "display.h"

int	handle_move(int keycode, t_game *game)
{
	if (keycode == KEY_A)
	{
		game->player.pos_x -= game->player.dir_y * 0.1;
		game->player.pos_y += game->player.dir_x * 0.1;
		return (1);
	}
	if (keycode == KEY_D)
	{
		game->player.pos_x += game->player.dir_y * 0.1;
		game->player.pos_y -= game->player.dir_x * 0.1;
		return (1);
	}
	if (keycode == KEY_W)
		return (printf("Key W pressed\n"), 1);
	if (keycode == KEY_S)
		return (printf("Key S pressed\n"), 1);
	return (0);
}

int	key_hook(int keycode, void *param)
{
	t_game *game;

	game = (t_game *)param;
	if (keycode == KEY_ESC)
		return (close_hook(game), 0);
	if (handle_move(keycode, game) != 0)
		render(game);
	if (keycode == KEY_LEFT)
		return (printf("Left\n"), 0);
	if (keycode == KEY_RIGHT)
		return (printf("Right\n"), 0);
	return (0);
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->max_height)
	{
		free(map->map[i]);
		i++;
	}
	free(map->map);
}

int	close_hook(t_game *game)
{
	mlx_destroy_image(game->mlx, game->img.img);
	mlx_destroy_window(game->mlx, game->win);
	free_map(&game->map);
	exit(0);
}
