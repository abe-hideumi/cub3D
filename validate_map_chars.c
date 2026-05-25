#include "map.h"

static t_char_type is_valid_map_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (CHAR_PLAYER);
	if (c == '0' || c == '1' || c == ' ')
		return (CHAR_MAP);
	return (CHAR_INVALID);
}

static void init_player_dir(t_player *player,char c)
{
	if (c == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->plane_x = 1;
		player->plane_y = 0;
	}
	else if (c == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = -1;
	}
	else if (c == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = 1;
	}
	else if (c == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
		player->plane_x = -1;
		player->plane_y = 0;
	}
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
		init_player_dir(&info->player, *c);
		printf("dir == %f %f %f %f", info->player.dir_x, info->player.dir_y, info->player.plane_x, info->player.plane_y);

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