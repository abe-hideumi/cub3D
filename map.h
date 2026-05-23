# ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "libft/libft.h"
#include "get_next_line/get_next_line.h"

typedef enum e_char_type {
	CHAR_INVALID,
	CHAR_PLAYER,
	CHAR_MAP
} t_char_type;

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
	t_player    player;
}		t_info;

// parse_cub_utils.c
void	*ft_realloc(void *ptr, size_t new_size);
bool	ft_is_space(char c);
void	put_error(char *msg);

// parse_cub_file.c
void	parse_cub_file(char *file, t_info *info);

// parse_texture.c
void	parse_texture_img(char **field, char *line);
void	parse_texture_color(int *field, char *line);

// read_file.c
void	read_file(char *file, t_info *info);

// validate_map_chars.c
void	validate_map_chars(t_info *info);

// validate_map_enclosed.c
void	validate_map_enclosed(t_info *info);

#endif
