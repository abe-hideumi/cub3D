#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "map.h"
#include "libft/libft.h"
#include "get_next_line/get_next_line.h"

int ft_is_space(char c)
{
	if (c == ' ' || c == '\t')
		return 1;
	return 0;
}

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
	while (ft_is_space(*line))
		line++;
	if (*line == '\0' || *line == '\n')
		put_error("texture path is empty");
	len = ft_strlen(line);
	while (len > 0 && (line[len - 1] == '\n' || ft_is_space(line[len - 1])))
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

int validate_rgb_format(char *line)
{
	int comma;

	comma = 0;
	if (!ft_isdigit(*line))
		return (-1);
	while (*line)
	{
		if (*line == ',')
		{
			comma++;
			if (!ft_isdigit(*(line + 1)))
				return (-1);
		}
		else if (!ft_isdigit(*line))
			return (-1);
		line++;
	}
	if (comma != 2)
		return (-1);
	return (0);
}

int ft_atoi_rgb(char **s)
{
	int n = 0;

	while (ft_isdigit(**s))
	{
		n = n * 10 + (**s - '0');
		(*s)++;
	}
	if (**s == ',')
		(*s)++;
	if (n < 0 || n > 255)
		put_error("color code invalid 0 ~ 255");
	return n;
}

int parse_rgb_to_int(char *line)
{
	int rgb[3];
	if (validate_rgb_format(line))
		put_error("invalid color format");
	rgb[0] = ft_atoi_rgb(&line);
	rgb[1] = ft_atoi_rgb(&line);
	rgb[2] = ft_atoi_rgb(&line);

	// color code invalid   value 0 ~ 255 22,22,

	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

void parse_texture_color(int *field, char *line)
{
	size_t len;

	printf("1回目:%s|\n", line);
	if (*field != -1)
		put_error("invalid config: duplicate identifier");
	line += 2;
	while (ft_is_space(*line))
		line++;
	len = ft_strlen(line);
	while (len > 0 && (line[len - 1] == '\n' || ft_is_space(line[len - 1])))
		line[--len] = '\0';
	if (len == 0)
		put_error("color value is empty");
	*field = parse_rgb_to_int(line);
	printf("2回目:%s|\n", line);
}

int parse_config(char *line, t_info *info)
{
	while (ft_is_space(*line))
		line++;
	if (*line == '\n')
		return (0);
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
		printf("mapcheck 突入\n");
		// if (is_config_complete(info->config))
		// return 1 する前にconfig の必要データがすべて揃っているか確認
		// もし揃っていなかったら not enough config  check input（要検討）のエラーを出力した後 exitする
		return 1;
	}
}

void read_map(char *line, t_info *info)
{
	printf("line check: %s\n", line);
	ssize_t len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[--len] = '\0';
	if (info->map_info.max_width < len)
		info->map_info.max_width = len;
	info->map_info.map[info->map_info.max_height] = ft_strdup(line);
	info->map_info.max_height++;
	info->map_info.map[info->map_info.max_height] = NULL;
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
		if (!in_map)
			in_map = parse_config(line, info);
		if (in_map)
			read_map(line, info);
		//  使用不可な文字列が存在します。
		free(line);
	}
	close(fd);
}

int is_valid_map_char(char c)
{
	static int player_count = 0;
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		return (2);
	}
	if (c == '0' || c == '1' || c == ' ')
		return (1);
	return (0);
}

// void check_map(t_info *info)
// {
// 	char **raw_map = info->map_info.map;
// 	int i = 0;
// 	int j;

// 	while (i < info->map_info.max_height)
// 	{
// 		j = 0;
// 		while (j < info->map_info.max_width)
// 		{
// 			if (!raw_map[i][j])
// 				map[i][j] = ' ';
// 			else if (is_valid_map_char(raw_map[i][j]) == -1)
// 				put_error("two Player");
// 			else if (is_valid_map_char(raw_map[i][j]) == 0)
// 				put_error("unallowed char");
// 			else if (is_valid_map_char(raw_map[i][j]) == 1)
// 				map[i][j] = raw_map[i][j];
// 			else if (is_valid_map_char(raw_map[i][j]) == 2)
// 			{
// 				if (info->player_dir)
// 					put_error("more than 2 player");
// 				info->player_dir = raw_map[i][j];
// 				map[i][j] = raw_map[i][j];
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

void parse_map(t_info *info)
{
	// check_map(info);

	printf("=== normalized map ===\n");
	printf("width: %d  height: %d\n", info->map_info.max_width, info->map_info.max_height);
	for (int i = 0; i < info->map_info.max_height; i++)
		printf("%s|\n", info->map_info.map[i]);
	printf("player: dir=%c\n", info->player_dir);
	printf("======================\n");
}

void parse_cub_file(char *file, t_info *info)
{
	check_extenstion(file);
	info->config = (t_config){NULL, NULL, NULL, NULL, -1, -1};
	info->map_info = (t_map){0};
	info->map_info.map = malloc(sizeof(char *) * 1000);
	if (info->map_info.map == NULL)
		put_error("malloc failed");
	read_file(file, info);

	printf("=== config ===\n");
	printf("NO: %s|\n", info->config.no ? info->config.no : "(null)");
	printf("SO: %s|\n", info->config.so ? info->config.so : "(null)");
	printf("WE: %s|\n", info->config.we ? info->config.we : "(null)");
	printf("EA: %s|\n", info->config.ea ? info->config.ea : "(null)");
	printf("F:  %x|\n", info->config.f);
	printf("C:  %x|\n", info->config.c);
	printf("==============\n");
	printf("パース成功\n");
	for (int i = 0; i < info->map_info.max_height; i++)
		printf("map : %s|\n", info->map_info.map[i]);
	printf("max width: %d max height: %d\n", info->map_info.max_width, info->map_info.max_height);
	printf("==============\n");

	// これからマップのパースを行う
	parse_map(info);
}

// 仮置きメインファイル
int main(int ac, char *av[])
{
	if (ac != 2)
		return (printf("acないよ\n"), 1);
	t_info info;
	info.player_dir = 0;

	parse_cub_file(av[1], &info);

	free(info.config.no);
	free(info.config.so);
	free(info.config.we);
	free(info.config.ea);
	for (int i = 0; i < info.map_info.max_height; i++)
		free(info.map_info.map[i]);
	free(info.map_info.map);

	return (0);
}