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

void insert_texture(char **field, char *line)
{
	size_t	len;
	int		fd;

	printf("%s\n", line);
	if (*field != NULL)
		put_error();
	line += 3;
	while (*line == ' ')
		line++;
	if (*line == '\0' || *line == '\n')
		put_error(); // テキスチャーファイルが存在しない
	len = ft_strlen(line);
	while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == ' '))
		len--;
	if (len == 0)
		put_error();
	*field = ft_substr(line, 0, len);
	if (*field == NULL)
		put_error();
	fd = open(*field, O_RDONLY);
	if (fd < 0)
		put_error(); // テキスチャファイルが指定のルートに存在しない又はopenできない
	close(fd);
	printf("%s\n", line);
}

int parse_config(char *line, t_info *info)
{
	if (!strncmp("NO ", line, 3))
		return (insert_texture(&info->config.no, line), 0);
	if (!strncmp("SO ", line, 3))
		return (insert_texture(&info->config.so, line), 0);
	if (!strncmp("WE ", line, 3))
		return (insert_texture(&info->config.we, line), 0);
	if (!strncmp("EA ", line, 3))
		return (insert_texture(&info->config.ea, line), 0);
	else
	{
		printf("未実装\n");
		return 0;
	}
	
	
	

	return (1);
}

void read_file(char *file, t_info *info)
{
	int fd;
	char *line;
	size_t len;
	int in_map = 0;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		put_error();

	while (line = get_next_line(fd))
	{
		if (!in_map)
			in_map = parse_config(line, info);
		if (in_map)
			read_map();
		free(line);
	}
	close(fd);
}

void parse_cub_file(char *file, t_info *info)
{
	check_extenstion(file);
	read_file(file, info);
	
	printf("パース成功\n");


}


// 仮置きメインファイル
int main(int ac, char *av[])
{
	if (ac != 2)
		return (printf("jjj\n"), 1);
	t_info info;

	parse_cub_file(av[1], &info);





	return (0);
}