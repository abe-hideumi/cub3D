#include "display.h"

int	handle_move(t_keycode keycode, t_game *game)
{
	if (keycode == KEY_A)
	{
		game->player.pos_x -= game->player.plane_x * MOVE_SPEED;
		game->player.pos_y += game->player.plane_y * MOVE_SPEED;
		return (printf("Key A\n"), 1);
	}
	if (keycode == KEY_D)
	{
		game->player.pos_x += game->player.plane_x * MOVE_SPEED;
		game->player.pos_y -= game->player.plane_y * MOVE_SPEED;
		return (printf("Key D\n"), 1);
	}
	if (keycode == KEY_W)
	{
		game->player.pos_x += game->player.dir_x * MOVE_SPEED;
		game->player.pos_y += game->player.dir_y * MOVE_SPEED;
		return (printf("Key W\n"), 1);
	}
	if (keycode == KEY_S)
	{
		game->player.pos_x -= game->player.dir_x * MOVE_SPEED;
		game->player.pos_y -= game->player.dir_y * MOVE_SPEED;
		return (printf("Key S\n"), 1);
	}
	return (0);
}

static void	dir_right(t_game *game)
{
	double	old_dir_x;
	double	old_dir_y;
	double	old_plane_x;
	double	old_plane_y;

	old_dir_x = game->player.dir_x;
	old_dir_y = game->player.dir_y;
	old_plane_x = game->player.plane_x;
	old_plane_y = game->player.plane_y;
	game->player.dir_x = rotate_right_x(old_dir_x, old_dir_y);
	game->player.dir_y = rotate_right_y(old_dir_x, old_dir_y);
	game->player.plane_x = rotate_right_x(old_plane_x, old_plane_y);
	game->player.plane_y = rotate_right_y(old_plane_x, old_plane_y);
	printf("Right\n");
}

static void	dir_left(t_game *game)
{
	double	old_dir_x;
	double	old_dir_y;
	double	old_plane_x;
	double	old_plane_y;

	old_dir_x = game->player.dir_x;
	old_dir_y = game->player.dir_y;
	old_plane_x = game->player.plane_x;
	old_plane_y = game->player.plane_y;
	game->player.dir_x = rotate_left_x(old_dir_x, old_dir_y);
	game->player.dir_y = rotate_left_y(old_dir_x, old_dir_y);
	game->player.plane_x = rotate_left_x(old_plane_x, old_plane_y);
	game->player.plane_y = rotate_left_y(old_plane_x, old_plane_y);
	printf("Left\n");
}

int	key_press(t_keycode keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (handle_move(keycode, game) != 0)
		game_render(game);
	if (keycode == KEY_LEFT)
	{
		dir_left(game);
		game_render(game);
	}
	if (keycode == KEY_RIGHT)
	{
		dir_right(game);
		game_render(game);
	}
	return (0);
}

int	close_hook(t_keycode keycode, void *param)
{
	t_game	*game;

	if (keycode != KEY_ESC)
		return (0);
	game = (t_game *)param;
	mlx_destroy_image(game->mlx, game->img.img);
	mlx_destroy_window(game->mlx, game->win);
	free_map(&game->map);
	exit(0);
}
