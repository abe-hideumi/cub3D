/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 18:18:27 by habe              #+#    #+#             */
/*   Updated: 2026/06/04 12:25:45 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

static void	mlx_cleanup(t_game *game)
{
	if (game->mlx != NULL && game->win != NULL)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx != NULL && game->img.img != NULL)
		mlx_destroy_image(game->mlx, game->img.img);
	if (game->mlx != NULL && game->texture.no.img != NULL)
		mlx_destroy_image(game->mlx, game->texture.no.img);
	if (game->mlx != NULL && game->texture.so.img != NULL)
		mlx_destroy_image(game->mlx, game->texture.so.img);
	if (game->mlx != NULL && game->texture.we.img != NULL)
		mlx_destroy_image(game->mlx, game->texture.we.img);
	if (game->mlx != NULL && game->texture.ea.img != NULL)
		mlx_destroy_image(game->mlx, game->texture.ea.img);
	if (game->mlx != NULL)
		destroy_display(game->mlx);
}

void	cleanup(t_game *game)
{
	if (game != NULL)
	{
		mlx_cleanup(game);
		free_map(&game->map);
		if (game->mlx != NULL)
			free(game->mlx);
	}
}
