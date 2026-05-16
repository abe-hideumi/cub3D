#ifndef DISPLAY_H
# define DISPLAY_H

# include "../cub3D.h"
# include "../map.h"
# include "../libft/libft.h"

// colors
# define RED 0xFF0000
# define BLUE 0x0000FF
# define GREEN 0x008000
# define YELLOW 0xFFFF00
# define BLACK 0x000000
# define WHITE 0xFFFFFF

// display size
# define WIDTH 1600
# define HEIGHT 1200

// player movement
# define MOVE_SPEED 0.1
# define ROT_SPEED 0.05

// event
# define DESTROY_NOTIFY 17

// keycode
# ifdef __APPLE__
#  define KEY_ESC 53
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_W 25
#  define KEY_A 38
#  define KEY_S 39
#  define KEY_D 40
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

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_player	player;
	t_map		map;
	t_config	config;
	// t_img		tex[4];
}	t_game;

typedef struct s_ray
{
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		side;
	double	perp_wall_dist;
}	t_ray;

int		display_init(t_game *game);
int		key_hook(int keycode, void *param);
int		close_hook(t_game *game);
void	game_render(t_game *game);
double	multiply(double a, double b);
void	put_pixel(t_img *img, int x, int y, int color);
void	set_ray_step(t_ray *ray, double dir_x, double dir_y);
void	init_side_dist(t_player *player, t_ray *ray, \
			double dir_x, double dir_y);

// mock config
void	player_init(t_player *player);
int		map_init(t_map *map);
int		game_init(t_game *game);

#endif
