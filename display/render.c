#include "display.h"

static void	init_ray(t_game *game, t_ray *ray, int x)
{
	double	camera_x;

	camera_x = 2.0 * x / WIDTH - 1.0;
	ray->dir_x = game->player.dir_x + game->player.plane_x * camera_x;
	ray->dir_y = game->player.dir_y + game->player.plane_y * camera_x;
	ray->map_x = (int)game->player.pos_x;
	ray->map_y = (int)game->player.pos_y;
	ray->delta_dist_x = fabs(1.0 / ray->dir_x);
	ray->delta_dist_y = fabs(1.0 / ray->dir_y);
	set_ray_step(ray, ray->dir_x, ray->dir_y);
	init_side_dist(&game->player, ray, ray->dir_x, ray->dir_y);
}

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
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (game->map.map[ray->map_y][ray->map_x] == '1')
			hit = true;
	}
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
}

static t_img	*get_texture(t_texture *tex, t_ray *ray)
{
	if (ray->side == 0 && ray->step_x > 0)
		return (&tex->we);
	if (ray->side == 0)
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
	if (ray->side == 0)
		wall_x = game->player.pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = game->player.pos_x + ray->perp_wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	col.tex_x = (int)(wall_x * TEX_WIDTH);
	if ((ray->side == 0 && ray->dir_x > 0) || (ray->side == 1 && ray->dir_y < 0))
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
