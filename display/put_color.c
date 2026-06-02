/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knomura <knomura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 13:38:42 by knomura           #+#    #+#             */
/*   Updated: 2026/06/02 13:38:43 by knomura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_stripe(t_game *game, t_col *col, int x)
{
	int		ds;
	int		de;
	int		y;

	ds = col->draw_start;
	de = col->draw_end;
	if (ds < 0)
		ds = 0;
	if (de >= HEIGHT)
		de = HEIGHT - 1;
	col->tex_pos += (double)(ds - col->draw_start) * col->tex_step;
	y = 0;
	while (y < ds)
		put_pixel(&game->img, x, y++, game->texture.c);
	while (y <= de)
	{
		put_pixel(&game->img, x, y++, *(int *)(col->tex->addr
				+ ((int)col->tex_pos & (TEX_HEIGHT - 1)) * col->tex->line_len
				+ col->tex_x * (col->tex->bpp / 8)));
		col->tex_pos += col->tex_step;
	}
	while (y < HEIGHT)
		put_pixel(&game->img, x, y++, game->texture.f);
}
