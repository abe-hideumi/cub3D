#include "map.h"

static void	check_extenstion(char *map_name)
{
	size_t	len;

	len = ft_strlen(map_name);
	if (len < 5 || ft_strncmp(".cub", map_name + len - 4, 4))
		printf("Invalid file extension. Must be .cub\n");
}

void	parse_cub_file(char *file, t_info *info)
{
	check_extenstion(file);
	info->player_dir = 0;
	info->config = (t_config){NULL, NULL, NULL, NULL, -1, -1};
	info->map_info = (t_map){0};
	info->map_info.map = malloc(sizeof(char *) * 1);
	if (info->map_info.map == NULL)
		put_error("malloc failed");
	read_file(file, info);
	validate_map_chars(info);
	validate_map_enclosed(info);
}

// 仮置きメインファイル
int	main(int ac, char *av[])
{
	t_info	info;

	if (ac != 2)
		return (printf("acないよ\n"), 1);
	parse_cub_file(av[1], &info);
	printf("=== config ===\n");
	printf("NO: %s|\n", info.config.no ? info.config.no : "(null)");
	printf("SO: %s|\n", info.config.so ? info.config.so : "(null)");
	printf("WE: %s|\n", info.config.we ? info.config.we : "(null)");
	printf("EA: %s|\n", info.config.ea ? info.config.ea : "(null)");
	printf("F:  %x|\n", info.config.f);
	printf("C:  %x|\n", info.config.c);
	printf("==============\n");
	printf("パース成功\n");
	for (int i = 0; i < info.map_info.max_height; i++)
		printf("map : %s|\n", info.map_info.map[i]);
	printf("max width: %d max height: %d\n", info.map_info.max_width, info.map_info.max_height);
	printf("==============\n");
	printf("=== normalized map ===\n");
	printf("width: %d  height: %d\n", info.map_info.max_width, info.map_info.max_height);
	for (int i = 0; i < info.map_info.max_height; i++)
		printf("%s|\n", info.map_info.map[i]);
	printf("player: dir=%c\n", info.player_dir);
	printf("======================\n");
	free(info.config.no);
	free(info.config.so);
	free(info.config.we);
	free(info.config.ea);
	for (int i = 0; i < info.map_info.max_height; i++)
		free(info.map_info.map[i]);
	free(info.map_info.map);
	return (0);
}
