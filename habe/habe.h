
#ifndef HABE_H
# define HABE_H

# include "cub3D.h"
# include "../libft/libft.h"

# define RED 0xFF0000
# define BLUE 0x0000FF
# define GREEN 0x008000
# define YELLO 0xFFFF00
# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define FOV 90

# define WIDTH 800
# define HEIGHT 600

# define DESTROY_NOTIFY 17

// keycode
# ifdef __APPLE__
# define KEY_ESC 53
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_W 25
# define KEY_A 38
# define KEY_S 39
# define KEY_D 40
# else
#  define KEY_ESC 65307
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
# endif

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_map
{
	char	**map;
	int		width;
	int		height;
}	t_map;

// typedef struct s_wall
// {
// 	char	*tex_no;
// 	char	*tex_so;
// 	char	*tex_we;
// 	char	*tex_ea;
// }	t_wall;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_player	player;
	t_map		map;
	int			floor_color;
	int			ceiling_color;
	// t_wall		wall;
	// t_img		tex[4];
}	t_game;

int		display_init(t_game *game);
int		key_hook(int keycode, void *param);
int		close_hook(t_game *game);
void	game_render(t_game *game);

#endif
