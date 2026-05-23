#include "../cub3D.h"

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->max_height)
	{
		free(map->map[i]);
		i++;
	}
	free(map->map);
}
