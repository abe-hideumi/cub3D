#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "map.h"
#include "libft/libft.h"
#include "get_next_line/get_next_line.h"

static int check_single_direction(char **map, int x, int y)
{
	if (x < 0 || y < 0 || !map[y] || x >= ft_strlen(map[y]) || map[y][x] == ' ')
		return 1;
	return 0;
}

static bool check_all_direction(char **map, int x, int y)
{
	int err;

	err = 0;
	err = check_single_direction(map, x + 1, y);
	err += check_single_direction(map, x - 1, y);
	err += check_single_direction(map, x, y + 1);
	err += check_single_direction(map, x, y - 1);

	return err;
}

void validate_map_enclosed(t_info *info)
{
	char **map = info->map_info.map;
	int x;
	int y;

	y = 0;
	while (y < info->map_info.max_height)
	{
		x = 0;
		int len = ft_strlen(map[y]);
		while (x < len)
		{
			if (map[y][x] == 'P' || map[y][x] == '0')
				if (check_all_direction(map, x, y))
					put_error("Map not closed");
			x++;
		}
		y++;
	}
}