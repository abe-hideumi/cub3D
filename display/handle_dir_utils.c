/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 12:55:43 by habe              #+#    #+#             */
/*   Updated: 2026/06/04 12:56:48 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

void	dir_right(t_game *game)
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

void	dir_left(t_game *game)
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
