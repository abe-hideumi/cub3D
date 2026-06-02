/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_move_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knomura <knomura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 13:35:32 by knomura           #+#    #+#             */
/*   Updated: 2026/06/02 13:58:56 by knomura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

static bool	check_wall(t_game *game, double pos_x, double pos_y)
{
	double	x;
	double	y;

	x = fmod(pos_x, 1.0);
	y = fmod(pos_y, 1.0);
	if (x <= 0.1 && game->map.map[(int)pos_y][(int)pos_x - 1] == '1')
		return (true);
	if (x >= 0.9 && game->map.map[(int)pos_y][(int)pos_x + 1] == '1')
		return (true);
	if (y <= 0.1 && game->map.map[(int)pos_y - 1][(int)pos_x] == '1')
		return (true);
	if (y >= 0.9 && game->map.map[(int)pos_y + 1][(int)pos_x] == '1')
		return (true);
	return (false);
}

void	move_forward(t_game *game)
{
	game->player.pos_x += game->player.dir_x * MOVE_SPEED;
	game->player.pos_y += game->player.dir_y * MOVE_SPEED;
	if (check_wall(game, game->player.pos_x, game->player.pos_y))
	{
		game->player.pos_x -= game->player.dir_x * MOVE_SPEED;
		game->player.pos_y -= game->player.dir_y * MOVE_SPEED;
	}
}

void	move_back(t_game *game)
{
	game->player.pos_x -= game->player.dir_x * MOVE_SPEED;
	game->player.pos_y -= game->player.dir_y * MOVE_SPEED;
	if (check_wall(game, game->player.pos_x, game->player.pos_y))
	{
		game->player.pos_x += game->player.dir_x * MOVE_SPEED;
		game->player.pos_y += game->player.dir_y * MOVE_SPEED;
	}
}

void	move_left(t_game *game)
{
	game->player.pos_x -= game->player.plane_x * MOVE_SPEED;
	game->player.pos_y -= game->player.plane_y * MOVE_SPEED;
	if (check_wall(game, game->player.pos_x, game->player.pos_y))
	{
		game->player.pos_x += game->player.plane_x * MOVE_SPEED;
		game->player.pos_y += game->player.plane_y * MOVE_SPEED;
	}
}

void	move_right(t_game *game)
{
	game->player.pos_x += game->player.plane_x * MOVE_SPEED;
	game->player.pos_y += game->player.plane_y * MOVE_SPEED;
	if (check_wall(game, game->player.pos_x, game->player.pos_y))
	{
		game->player.pos_x -= game->player.plane_x * MOVE_SPEED;
		game->player.pos_y -= game->player.plane_y * MOVE_SPEED;
	}
}
