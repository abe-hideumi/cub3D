#include <stdio.h>
#include <fcntl.h>
#include "map.h"

void	put_error(void)
{
	ft_putstr_fd("Error\n", 2);
	exit(1);
}

void	check_extenstion(char *map_name)
{
	size_t	len;

	len = ft_strlen(map_name);
	if (len < 5 || ft_strncmp(".cub", map_name + len - 4, 4))
		printf("Invalid file extension. Must be .cub\n");
}

void read_file(char *file, t_info *info)
{
	int fd;
	char *line;
	size_t len;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		put_error();
	line = get_next_line(fd);
	while (line)
	{
		len = 0;
		while (line[len] && line[len] != '\0')
			len++;
		if (info->file_max_len < len)
			info->file_max_len = len;
		info->file_height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void parse_config(char *file, t_info *info)
{
	info->file_max_len = 0;
	info->file_height = 0;
	check_extenstion(file);
	read_file(file, info);
	



}


// 仮置きメインファイル
int main(int ac, char *av[])
{
	if (ac != 2)
		return (printf("jjj\n"), 1);
	t_info info;

	parse_config(av[1], info);





	return (0);
}