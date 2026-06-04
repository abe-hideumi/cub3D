/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 13:38:20 by knomura           #+#    #+#             */
/*   Updated: 2026/06/04 12:35:26 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include <math.h>
# include "../parse/map.h"
# ifdef __linux__
#  include "../minilibx-linux/mlx.h"
# else
#  include "../minilibx_opengl_20191021/mlx.h"
# endif

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
# define KEY_PRESS 2
# define KEY_RELEASE 3

// ray side
# define X_SIDE 0
# define Y_SIDE 1

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
	bool		key_state[256];
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

void	display_init(t_game *game, t_info *info);
void	game_render(t_game *game);
void	draw_stripe(t_game *game, t_col *col, int x);
void	put_pixel(t_img *img, int x, int y, int color);

// hooks
int		key_down(int keycode, void *param);
int		key_up(int keycode, void *param);
int		game_loop(void *param);
int		close_hook(void *param);

// move utils
void	move_forward(t_game *game);
void	move_back(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);

// calulation
double	rotate_right_x(double dir_x, double dir_y);
double	rotate_right_y(double dir_x, double dir_y);
double	rotate_left_x(double dir_x, double dir_y);
double	rotate_left_y(double dir_x, double dir_y);

// raycasting
void	init_ray(t_game *game, t_ray *ray, int x);

// cleanup
void	cleanup(t_game *game);

#endif
