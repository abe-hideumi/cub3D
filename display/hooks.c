/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knomura <knomura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 13:38:26 by knomura           #+#    #+#             */
/*   Updated: 2026/06/02 15:32:31 by knomura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

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
}

static bool	handle_move(t_keycode keycode, t_game *game)
{
	if (keycode == KEY_W)
		return (move_forward(game), true);
	if (keycode == KEY_A)
		return (move_left(game), true);
	if (keycode == KEY_S)
		return (move_back(game), true);
	if (keycode == KEY_D)
		return (move_right(game), true);
	return (false);
}

int	close_hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_destroy_image(game->mlx, game->img.img);
	mlx_destroy_image(game->mlx, game->texture.ea.img);
	mlx_destroy_image(game->mlx, game->texture.so.img);
	mlx_destroy_image(game->mlx, game->texture.no.img);
	mlx_destroy_image(game->mlx, game->texture.we.img);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free_map(&game->map);
	free(game->mlx);
	exit(0);
}

int	key_press(t_keycode keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == KEY_ESC)
		close_hook(game);
	if (handle_move(keycode, game) == true)
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
