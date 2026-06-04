/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 13:38:26 by knomura           #+#    #+#             */
/*   Updated: 2026/06/04 12:56:43 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

static bool	apply_keys(t_game *game)
{
	bool	moved;

	moved = false;
	if (game->key_state[KEY_W])
		moved = (move_forward(game), true);
	if (game->key_state[KEY_A])
		moved = (move_left(game), true);
	if (game->key_state[KEY_S])
		moved = (move_back(game), true);
	if (game->key_state[KEY_D])
		moved = (move_right(game), true);
	if (game->key_state[KEY_LEFT])
		moved = (dir_left(game), true);
	if (game->key_state[KEY_RIGHT])
		moved = (dir_right(game), true);
	return (moved);
}

int	close_hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	cleanup(game);
	exit(0);
}

int	key_down(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == KEY_ESC)
		close_hook(game);
	if (keycode >= 0 && keycode < MAX_KEYCODE)
		game->key_state[keycode] = true;
	return (0);
}

int	key_up(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode >= 0 && keycode < MAX_KEYCODE)
		game->key_state[keycode] = false;
	return (0);
}

int	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (apply_keys(game))
		game_render(game);
	return (0);
}
