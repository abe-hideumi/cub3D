#include "display.h"

void	player_init(t_player *player)
{
	player->pos_x = 4;
	player->pos_y = 3;
	player->dir_x = 0;
	player->dir_y = -1;
	player->plane_x = 1;
	player->plane_y = 0;
}

int	map_init(t_map *map)
{
	map->map = malloc(sizeof(char **) * 6);
	if (map->map == NULL)
		return (1);
	map->map[0] = ft_strdup("111111");
	if (map->map[0] == NULL)
		return (free(map->map), 1);
	map->map[1] = ft_strdup("100101");
	if (map->map[1] == NULL)
		return (free(map->map[0]), free(map->map), 1);
	map->map[2] = ft_strdup("101001");
	if (map->map[2] == NULL)
		return (free(map->map[0]), free(map->map[1]), free(map->map), 1);
	map->map[3] = ft_strdup("1100N1");
	if (map->map[3] == NULL)
		return (free(map->map[0]), free(map->map[1]), \
			free(map->map[2]), free(map->map), 1);
	map->map[4] = ft_strdup("111111");
	if (map->map[4] == NULL)
		return (free(map->map[0]), free(map->map[1]), \
			free(map->map[2]), free(map->map[3]), free(map->map), 1);
	map->map[5] = NULL;
	map->max_width = 6;
	map->max_height = 5;
	return (0);
}
