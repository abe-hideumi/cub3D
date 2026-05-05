# ifndef MAP_H
#define MAP_H

typedef struct s_map
{
	char **map;
	int max_width;
	int max_height;
}		t_map;

typedef struct s_config
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		f;
	int		c;
}		t_config;

typedef struct s_info
{
	char	**lines;
	t_map	map_info;
	char	player_dir;
	int		player_x;
	int		player_y;
}		t_info;

#endif