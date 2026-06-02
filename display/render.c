#include "display.h"

static void	perform_dda(t_game *game, t_ray *ray)
{
	bool	hit;

	hit = false;
	while (hit != true)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = X_SIDE;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = Y_SIDE;
		}
		if (game->map.map[ray->map_y][ray->map_x] == '1')
			hit = true;
	}
	if (ray->side == X_SIDE)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
}

static t_img	*get_texture(t_texture *tex, t_ray *ray)
{
	if (ray->side == X_SIDE && ray->step_x > 0)
		return (&tex->we);
	if (ray->side == X_SIDE)
		return (&tex->ea);
	if (ray->step_y > 0)
		return (&tex->no);
	return (&tex->so);
}

static t_col	draw_column(t_game *game, t_ray *ray)
{
	t_col	col;
	double	wall_x;
	int		wall_h;

	wall_h = (int)(HEIGHT / ray->perp_wall_dist);
	col.draw_start = HEIGHT / 2 - wall_h / 2;
	col.draw_end = HEIGHT / 2 + wall_h / 2;
	if (ray->side == X_SIDE)
		wall_x = game->player.pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = game->player.pos_x + ray->perp_wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	col.tex_x = (int)(wall_x * TEX_WIDTH);
	if ((ray->side == X_SIDE && ray->dir_x > 0) || \
			(ray->side == Y_SIDE && ray->dir_y < 0))
		col.tex_x = TEX_WIDTH - col.tex_x - 1;
	col.tex = get_texture(&game->texture, ray);
	col.tex_step = (double)TEX_HEIGHT / wall_h;
	col.tex_pos = 0;
	return (col);
}

void	game_render(t_game *game)
{
	t_ray	ray;
	t_col	col;
	int		x;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(game, &ray, x);
		perform_dda(game, &ray);
		col = draw_column(game, &ray);
		draw_stripe(game, &col, x);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}
