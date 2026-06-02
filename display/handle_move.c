/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knomura <knomura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 13:35:32 by knomura           #+#    #+#             */
/*   Updated: 2026/06/02 13:35:37 by knomura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

static void	move_forward(t_game *game)
{
	game->player.pos_x += game->player.dir_x * MOVE_SPEED;
	game->player.pos_y += game->player.dir_y * MOVE_SPEED;
	if (check_wall(game, game->player.pos_x, game->player.pos_y))
	{
		game->player.pos_x -= game->player.dir_x * MOVE_SPEED;
		game->player.pos_y -= game->player.dir_y * MOVE_SPEED;
	}
}

static void	move_back(t_game *game)
{
	game->player.pos_x -= game->player.dir_x * MOVE_SPEED;
	game->player.pos_y -= game->player.dir_y * MOVE_SPEED;
	if (check_wall(game, game->player.pos_x, game->player.pos_y))
	{
		game->player.pos_x += game->player.dir_x * MOVE_SPEED;
		game->player.pos_y += game->player.dir_y * MOVE_SPEED;
	}
}

static void	move_left(t_game *game)
{
	game->player.pos_x -= game->player.plane_x * MOVE_SPEED;
	game->player.pos_y -= game->player.plane_y * MOVE_SPEED;
	if (check_wall(game, game->player.pos_x, game->player.pos_y))
	{
		game->player.pos_x += game->player.plane_x * MOVE_SPEED;
		game->player.pos_y += game->player.plane_y * MOVE_SPEED;
	}
}

static void	move_right(t_game *game)
{
	game->player.pos_x += game->player.plane_x * MOVE_SPEED;
	game->player.pos_y += game->player.plane_y * MOVE_SPEED;
	if (check_wall(game, game->player.pos_x, game->player.pos_y))
	{
		game->player.pos_x -= game->player.plane_x * MOVE_SPEED;
		game->player.pos_y -= game->player.plane_y * MOVE_SPEED;
	}
}

bool	handle_move(t_keycode keycode, t_game *game)
{
	if (keycode == KEY_W)
		return (move_forward(game), printf("Key W\n"), true);
	if (keycode == KEY_A)
		return (move_left(game), printf("Key A\n"), true);
	if (keycode == KEY_S)
		return (move_back(game), printf("Key S\n"), true);
	if (keycode == KEY_D)
		return (move_right(game), printf("Key D\n"), true);
	return (false);
}
