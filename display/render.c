
#include "display.h"

static void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

static void	init_ray(t_game *game, t_ray *ray, int x)
{
	double	camera_x;
	double	dir_x;
	double	dir_y;

	camera_x = 2.0 * x / WIDTH - 1.0;
	dir_x = game->player.dir_x + game->player.plane_x * camera_x;
	dir_y = game->player.dir_y + game->player.plane_y * camera_x;
	ray->map_x = (int)game->player.pos_x;
	ray->map_y = (int)game->player.pos_y;
	ray->delta_dist_x = fabs(1.0 / dir_x);
	ray->delta_dist_y = fabs(1.0 / dir_y);
	ray->step_x = (dir_x < 0) ? -1 : 1;
	ray->step_y = (dir_y < 0) ? -1 : 1;
	if (dir_x < 0)
		ray->side_dist_x = (game->player.pos_x - ray->map_x) * ray->delta_dist_x;
	else
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.pos_x) * ray->delta_dist_x;
	if (dir_y < 0)
		ray->side_dist_y = (game->player.pos_y - ray->map_y) * ray->delta_dist_y;
	else
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.pos_y) * ray->delta_dist_y;
}

static void	perform_dda(t_game *game, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (!hit)
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
			hit = 1;
	}
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
}

static void	draw_column(t_game *game, t_ray *ray, int x)
{
	int	wall_height;
	int	draw_start;
	int	draw_end;
	int	wall_color;
	int	y;

	wall_height = (int)(HEIGHT / ray->perp_wall_dist);
	draw_start = HEIGHT / 2 - wall_height / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = HEIGHT / 2 + wall_height / 2;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	wall_color = (ray->side == 1) ? 0x888888 : WHITE;
	y = 0;
	while (y < draw_start)
		put_pixel(&game->img, x, y++, game->config.c);
	while (y <= draw_end)
		put_pixel(&game->img, x, y++, wall_color);
	while (y < HEIGHT)
		put_pixel(&game->img, x, y++, game->config.f);
}

void	game_render(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(game, &ray, x);
		perform_dda(game, &ray);
		draw_column(game, &ray, x);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}
