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

// 初期化御願いします
typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_info
{
	t_map		map_info;
	t_config 	config;
	char		player_dir;
	int			player_x;
	int			player_y;
}		t_info;

#endif
