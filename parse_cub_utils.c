#include "map.h"

void	*ft_realloc(void *ptr, size_t new_size)
{
	(void)ptr;
	(void)new_size;

	//  実装してください。

	return (NULL);
}

bool	ft_is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (true);
	return (false);
}

void free_config(t_config config)
{
	if (config.no)
		free(config.no);
	if (config.ea)
		free(config.ea);
	if (config.so)
		free(config.so);
	if (config.we)
		free(config.we);
}

void free_parse_map(t_map *map)
{
	int i = 0;

	while (i < map->max_height)
		free(map->map[i++]);
	if (map->map[i])
		free(map->map[i]);
	free(map->map);
}

void free_parse_info(t_info *info, char *str)
{
	if (str)
		free(str);
	free_config(info->config);
	free_parse_map(&info->map_info);
	get_next_line(-1);
	exit(1);
}

void	put_error_free(char *msg, t_info *info, char *str)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	free_parse_info(info, str);
}

void	put_error(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}
