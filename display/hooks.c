
#include "display.h"

int	handle_move(int keycode, t_game *game)
{
	if (keycode == KEY_A)
	{
		game->player.pos_y += multiply(game->player.plane_y, MOVE_SPEED);
		game->player.pos_x -= multiply(game->player.plane_x, MOVE_SPEED);
		return (printf("Key A\n"), 1);
	}
	if (keycode == KEY_D)
	{
		game->player.pos_y -= multiply(game->player.plane_y, MOVE_SPEED);
		game->player.pos_x += multiply(game->player.plane_x, MOVE_SPEED);
		return (printf("Key D\n"), 1);
	}
	if (keycode == KEY_W)
	{
		game->player.pos_x += multiply(game->player.dir_x, MOVE_SPEED);
		game->player.pos_y += multiply(game->player.dir_y, MOVE_SPEED);
		return (printf("Key W\n"), 1);
	}
	if (keycode == KEY_S)
	{
		game->player.pos_x -= multiply(game->player.dir_x, MOVE_SPEED);
		game->player.pos_y -= multiply(game->player.dir_y, MOVE_SPEED);
		return (printf("Key S\n"), 1);
	}
	return (0);
}

static void	dir_right(t_game *game)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	game->player.dir_x = multiply(game->player.dir_x, cos(-ROT_SPEED)) - multiply(game->player.dir_y, sin(-ROT_SPEED));
	game->player.dir_y = multiply(old_dir_x, sin(-ROT_SPEED)) + multiply(game->player.dir_y, cos(-ROT_SPEED));
	game->player.plane_x = multiply(game->player.plane_x, cos(-ROT_SPEED)) - multiply(game->player.plane_y, sin(-ROT_SPEED));
	game->player.plane_y = multiply(old_plane_x, sin(-ROT_SPEED)) + multiply(game->player.plane_y, cos(-ROT_SPEED));
}

static void	dir_left(t_game *game)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	game->player.dir_x = multiply(game->player.dir_x, cos(ROT_SPEED)) - multiply(game->player.dir_y, sin(ROT_SPEED));
	game->player.dir_y = multiply(old_dir_x, sin(ROT_SPEED)) + multiply(game->player.dir_y, cos(ROT_SPEED));
	game->player.plane_x = multiply(game->player.plane_x, cos(ROT_SPEED)) - multiply(game->player.plane_y, sin(ROT_SPEED));
	game->player.plane_y = multiply(old_plane_x, sin(ROT_SPEED)) + multiply(game->player.plane_y, cos(ROT_SPEED));
}

int	key_hook(int keycode, void *param)
{
	t_game *game;

	game = (t_game *)param;
	if (keycode == KEY_ESC)
		return (close_hook(game), 0);
	if (handle_move(keycode, game) != 0)
		game_render(game);
	if (keycode == KEY_LEFT)
	{
		dir_left(game);
		return (printf("Left\n"), 0);
	}
	if (keycode == KEY_RIGHT)
	{
		dir_right(game);
		return (printf("Right\n"), 0);
	}
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
