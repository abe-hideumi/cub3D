#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "map.h"
#include "libft/libft.h"
#include "get_next_line/get_next_line.h"

void *ft_realloc(void *ptr, size_t new_size)
{
	(void)ptr;
	(void)new_size;

	return NULL;
}

bool ft_is_space(char c)
{
	if (c == ' ' || c == '\t')
		return true;
	return false;
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
		put_error("Invalid config: duplicate identifier");
	line += 3;
	while (ft_is_space(*line))
		line++;
	if (*line == '\0' || *line == '\n')
		put_error("Texture path is empty");
	len = ft_strlen(line);
	while (len > 0 && (line[len - 1] == '\n' || ft_is_space(line[len - 1])))
		len--;
	if (len == 0)
		put_error("Texture path is empty");
	*field = ft_substr(line, 0, len);
	if (*field == NULL)
		put_error("Malloc failed");
	fd = open(*field, O_RDONLY);
	if (fd < 0)
		put_error("Texture file not found");
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
		put_error("Color code invalid 0 ~ 255");
	return n;
}

int parse_rgb_to_int(char *line)
{
	int rgb[3];

	if (validate_rgb_format(line))
		put_error("Invalid color format");
	rgb[0] = ft_atoi_rgb(&line);
	rgb[1] = ft_atoi_rgb(&line);
	rgb[2] = ft_atoi_rgb(&line);
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

void parse_texture_color(int *field, char *line)
{
	size_t len;

	printf("1回目:%s|\n", line);
	if (*field != -1)
		put_error("Invalid config: duplicate identifier");
	line += 2;
	while (ft_is_space(*line))
		line++;
	len = ft_strlen(line);
	while (len > 0 && (line[len - 1] == '\n' || ft_is_space(line[len - 1])))
		line[--len] = '\0';
	if (len == 0)
		put_error("Color value is empty");
	*field = parse_rgb_to_int(line);
	printf("2回目:%s|\n", line);
}

static bool is_config_complete(t_config config)
{
	return (config.no && config.so && config.we && config.ea && config.f != -1 && config.c != -1);
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
		if (!is_config_complete(info->config))
			put_error("INVALID OR MISSING CONFIG: CHECK IDENTIFIERS (NO/SO/WE/EA/F/C)");
		// 上のエラー　incomplete config の可能性もあるし　識別子が間違ってる可能性もあるからerrmsg を両方の場合に入るやつ考えて
		return 1;
	}
}

void read_map(char *line, t_info *info)
{
	size_t len;

	printf("line check: %s height:%d\n", line, info->map_info.max_height);
	char **tmp = realloc(info->map_info.map, sizeof(char *) * (info->map_info.max_height + 2));
	if (tmp == NULL)
		put_error("Realloc Failed");
	info->map_info.map = tmp;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[--len] = '\0';
	if (info->map_info.max_width < len)
		info->map_info.max_width = len;
	info->map_info.map[info->map_info.max_height] = ft_strdup(line);
	// NULL チェック
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
		put_error("Cannot open file");
	while ((line = get_next_line(fd)))
	{
		if (!in_map)
			in_map = parse_config(line, info);
		if (in_map)
			read_map(line, info);
		free(line);
	}
	close(fd);
}

static t_char_type is_valid_map_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (CHAR_PLAYER);
	if (c == '0' || c == '1' || c == ' ')
		return (CHAR_MAP);
	return (CHAR_INVALID);
}

static void check_map_char(t_info *info, char *c, int i, int j)
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
		// player を初期化　初期化関数を作る
		*c = 'P';
	}
	else if (ret == CHAR_INVALID)
		put_error("Unallowed char in map");
}

void check_map(t_info *info)
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
			check_map_char(info, &map[i][j], i, j);
			j++;
		}
		i++;
	}
	if (!info->player_dir)
		put_error("No Player");
}

int check_single_direction(char **map, int x, int y)
{
	if (x < 0 || y < 0 || !map[y] || x >= ft_strlen(map[y]) || map[y][x] == ' ')
		return 1;
	return 0;
}

bool check_all_direction(char **map, int x, int y)
{
	int ret;

	ret = check_single_direction(map, x + 1, y);
	ret += check_single_direction(map, x - 1, y);
	ret += check_single_direction(map, x, y + 1);
	ret += check_single_direction(map, x, y - 1);
	
	printf("%d", ret);
	return ret;
}

void check_map_wall(t_info *info)
{
	char **map = info->map_info.map;
	int x;
	int y;

	y = 0;
	while (y < info->map_info.max_height)
	{
		x = 0;
		printf("check\n");
		int len = ft_strlen(map[y]);
		while (x < len)
		{
			printf("x:%d y:%d\n", x, y);
			if (map[y][x] == 'P' || map[y][x] == '0')
				if (check_all_direction(map, x, y))
					put_error("gomi");
			x++;
		}
		y++;
	}

}

void parse_cub_file(char *file, t_info *info)
{
	check_extenstion(file);
	info->player_dir = 0;
	info->config = (t_config){NULL, NULL, NULL, NULL, -1, -1};
	info->map_info = (t_map){0};
	info->map_info.map = malloc(sizeof(char *) * 1);
	if (info->map_info.map == NULL)
		put_error("malloc failed");
	read_file(file, info);
	check_map(info);
	check_map_wall(info);

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
	printf("=== normalized map ===\n");
	printf("width: %d  height: %d\n", info->map_info.max_width, info->map_info.max_height);
	for (int i = 0; i < info->map_info.max_height; i++)
		printf("%s|\n", info->map_info.map[i]);
	printf("player: dir=%c\n", info->player_dir);
	printf("======================\n");
}

// 仮置きメインファイル
int main(int ac, char *av[])
{
	if (ac != 2)
		return (printf("acないよ\n"), 1);
	t_info info;

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