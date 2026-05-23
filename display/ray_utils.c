#include "display.h"

void	set_ray_step(t_ray *ray, double dir_x, double dir_y)
{
	if (dir_x < 0)
		ray->step_x = -1;
	else
		ray->step_x = 1;
	if (dir_y < 0)
		ray->step_y = -1;
	else
		ray->step_y = 1;
}

void	init_side_dist(t_player *player, t_ray *ray, double dir_x, double dir_y)
{
	if (dir_x < 0)
		ray->side_dist_x = (player->pos_x - ray->map_x) * \
			ray->delta_dist_x;
	else
		ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x) * \
			ray->delta_dist_x;
	if (dir_y < 0)
		ray->side_dist_y = (player->pos_y - ray->map_y) * \
			ray->delta_dist_y;
	else
		ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y) * \
			ray->delta_dist_y;
}
