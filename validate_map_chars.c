#include "map.h"

static t_char_type is_valid_map_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (CHAR_PLAYER);
	if (c == '0' || c == '1' || c == ' ')
		return (CHAR_MAP);
	return (CHAR_INVALID);
}

static void validate_map_char(t_info *info, char *c, int i, int j)
{
	int ret;

	ret = is_valid_map_char(*c);
	if (ret == CHAR_PLAYER)
	{
		if (info->player_dir)
			put_error("More than 2 player");
		info->player_dir = *c;
		info->player.pos_x = j;
		info->player.pos_y = i;
		info->player.dir_x = 1;
		info->player.dir_y = 1;
		info->player.plane_x = 1;
		info->player.plane_y = 1;
		*c = 'P';
	}
	else if (ret == CHAR_INVALID)
		put_error("Unallowed char in map");
}

void validate_map_chars(t_info *info)
{
	char **map;
	int len;
	int i;
	int j;

	map = info->map_info.map;
	i = 0;
	while (i < info->map_info.max_height)
	{
		j = 0;
		len = ft_strlen(map[i]);
		while (j < len)
		{
			validate_map_char(info, &map[i][j], i, j);
			j++;
		}
		i++;
	}
	if (!info->player_dir)
		put_error("No Player");
}