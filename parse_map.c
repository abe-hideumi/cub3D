#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "map.h"
#include "libft/libft.h"
#include "get_next_line/get_next_line.h"

void put_error(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

void check_extenstion(char *map_name)
{
	size_t len;

	len = ft_strlen(map_name);
	if (len < 5 || ft_strncmp(".cub", map_name + len - 4, 4))
		printf("Invalid file extension. Must be .cub\n");
}

void parse_texture_img(char **field, char *line)
{
	size_t len;
	int fd;

	printf("1回目:%s|\n", line);
	if (*field != NULL)
		put_error("invalid config: duplicate identifier");
	line += 3;
	while (*line == ' ')
		line++;
	if (*line == '\0' || *line == '\n')
		put_error("texture path is empty");
	len = ft_strlen(line);
	while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == ' '))
		len--;
	if (len == 0)
		put_error("texture path is empty");
	*field = ft_substr(line, 0, len);
	if (*field == NULL)
		put_error("malloc failed");
	fd = open(*field, O_RDONLY);
	if (fd < 0)
		put_error("texture file not found");
	close(fd);
	printf("2回目:%s|\n", line);
}

void split_atoi_rgb(char *line, int rgb[])
{
	int i = 0;

	


}
int validate_rgb_format(char *line)
{
	int comma;

	comma = 0;

	while(*line)

	
}

int parse_rgb_to_int(char *line)
{
	int rgb[3];
	if (validate_rgb_format(line))
	{
		printf("error  \ninvalid color format\n"); // 要修正
	}
	split_atoi_rgb(line, rgb);
	// color code invalid
	// color code invalid   value 0 ~ 255
	
	
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

void parse_texture_color(int *field, char *line)
{
	size_t len;
	int fd;

	printf("1回目:%s|\n", line);
	if (*field != -1)
		put_error("invalid config: duplicate identifier");
	line += 2;
	while (*line == ' ')
		line++;
	if (*line == '\0' || *line == '\n')
		put_error("texture path is empty");
	*field = parse_rgb_to_int(line);
	printf("2回目:%s|\n", line);
}

int parse_config(char *line, t_info *info)
{
	if (!ft_strncmp("NO ", line, 3))
		return (parse_texture_img(&info->config.no, line), 0);
	if (!ft_strncmp("SO ", line, 3))
		return (parse_texture_img(&info->config.so, line), 0);
	if (!ft_strncmp("WE ", line, 3))
		return (parse_texture_img(&info->config.we, line), 0);
	if (!ft_strncmp("EA ", line, 3))
		return (parse_texture_img(&info->config.ea, line), 0);
	if (!ft_strncmp("F ", line, 2))
		return (parse_texture_color(&info->config.f, line), 0);
	if (!ft_strncmp("C ", line, 2))
		return (parse_texture_color(&info->config.c, line), 0);
	else
	{

		printf("未実装map\n");
		return 0;
		//  本当はin_mapに入れるためにreturn 1
		// return 1 する前にconfig の必要データがすべて揃っているか確認
		// もし揃っていなかったら not enough config  check input（要検討）のエラーを出力した後 exitする
	}

	return (1);
}

void read_file(char *file, t_info *info)
{
	int fd;
	char *line;
	int in_map = 0;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		put_error("cannot open file");
	while ((line = get_next_line(fd)))
	{
		if (line[0] == '\n')
		{
			free(line);
			continue;
		}
		if (!in_map)
			in_map = parse_config(line, info);
		// if (in_map)
		// 	read_map();
		//  使用不可な文字列が存在します。
		free(line);
	}
	close(fd);
}

void parse_cub_file(char *file, t_info *info)
{
	check_extenstion(file);
	info->config = (t_config){NULL, NULL, NULL, NULL, -1, -1};
	read_file(file, info);

	printf("=== config ===\n");
	printf("NO: %s|\n", info->config.no ? info->config.no : "(null)");
	printf("SO: %s|\n", info->config.so ? info->config.so : "(null)");
	printf("WE: %s|\n", info->config.we ? info->config.we : "(null)");
	printf("EA: %s|\n", info->config.ea ? info->config.ea : "(null)");
	printf("F:  %d|\n", info->config.f);
	printf("C:  %d|\n", info->config.c);
	printf("==============\n");
	printf("パース成功\n");
}

// 仮置きメインファイル
int main(int ac, char *av[])
{
	if (ac != 2)
		return (printf("acないよ\n"), 1);
	t_info info;

	parse_cub_file(av[1], &info);

	return (0);
}