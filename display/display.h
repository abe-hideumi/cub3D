#ifndef DISPLAY_H
# define DISPLAY_H

# include "../cub3D.h"

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

// texture size
# define TEX_WIDTH 128
# define TEX_HEIGHT 128

// player movement
# define MOVE_SPEED 0.1
# define ROTATE_SPEED 0.05

// event
# define DESTROY_NOTIFY 17

// hit
# define HIT_WALL 1

// keycode
typedef enum e_keycode
{
	KEY_ESC = 65307,
	KEY_LEFT = 65361,
	KEY_RIGHT = 65363,
	KEY_W = 119,
	KEY_A = 97,
	KEY_S = 115,
	KEY_D = 100
}	t_keycode;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_texture
{
	t_img	no;
	t_img	so;
	t_img	we;
	t_img	ea;
	int		f;
	int		c;
}	t_texture;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_player	player;
	t_map		map;
	t_texture	texture;
}	t_game;

typedef struct s_col
{
	int		draw_start;
	int		draw_end;
	int		tex_x;
	double	tex_pos;
	double	tex_step;
	t_img	*tex;
}	t_col;

typedef struct s_ray
{
	int		map_x;
	int		map_y;
	double	dir_x;
	double	dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		side;
	double	perp_wall_dist;
}	t_ray;

bool	display_init(t_game *game, t_info *info);
void	game_render(t_game *game);
void	draw_stripe(t_game *game, t_col *col, int x);
double	multiply(double a, double b);
void	put_pixel(t_img *img, int x, int y, int color);
void	set_ray_step(t_ray *ray, double dir_x, double dir_y);
void	init_side_dist(t_player *player, t_ray *ray, \
			double dir_x, double dir_y);

// hooks
int		key_press(t_keycode keycode, void *param);
int		close_hook(void *param);

// calulation
double	rotate_right_x(double dir_x, double dir_y);
double	rotate_right_y(double dir_x, double dir_y);
double	rotate_left_x(double dir_x, double dir_y);
double	rotate_left_y(double dir_x, double dir_y);

// mock config
bool	game_init(t_game *game);

#endif
