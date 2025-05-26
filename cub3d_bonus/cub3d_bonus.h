/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:41:06 by dfasius           #+#    #+#             */
/*   Updated: 2025/05/26 13:41:10 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

/*------------------------------HEADER------------------------------*/

# include "../minilibx-linux/mlx.h"
# include "libft/libft.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include "get_next_line/get_next_line.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <math.h>    
# include <stdio.h>
# include <stdbool.h>
# include <time.h>

/*------------------------------MACRO------------------------------*/

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1088
# define MINIMAP_SIZE 256
# define ENEMY_SPEED 0.3f
# define MAX_ENEMY 20

# define PI 3.141592653589793238462643383279502884197

# define MINIMAP_TILE 8
# define MINIMAP_TILE_SIZE 32
# define TILE_SIZE  32
# define TILE_SIZE_BIG 8
# define TILE_SIZE_TEXTURE  64
# define DOORWIDTH 8

# define PLAYER_SIZE 2
# define MOVEMENT_SPEED 50
# define ROTATION_SPEED 2

# define SPRITE_SIZE 8
# define ENEMY_MARGIN 3.5f
# define SPRITE_SIZE_MAP 2

# define STRIP_WIDTH 2
# define NUM_RAYS 960
# define DOOR_RAY 20
# define FOV 1.047197551196597746154214461093167628065
# define MAX_DELTA_TIME 0.1
# define MOUSE_SENSITIVITY 0.1

# define PLAYER_COLOR 0x00FF0000
# define ENEMY_COLOR 0xFFFF00
# define RAYCAST_COLOR 0x0000FF00
# define WALL_COLOR 0x00AAAAAA
# define DOOR_COLOR 0x8B4513
# define DOOR_OPEN_COLOR 0xA52A2A
# define EMPTY_COLOR 0x404040
# define WIN_COLOR 0xFFD700
# define BLACK_COLOR 0x000000 
# define DOOR_SIDE_COLOR "208,138,134"

# define EMPTY_SPACE '0'
# define WALL '1'
# define DOORH_CLOSE '2'
# define DOORH_OPEN '3'
# define DOORV_CLOSE '4'
# define DOORV_OPEN '5'
# define DOOR_SPACE '6'
# define WIN_BLOCK '8'

/*------------------------------STRUCT------------------------------*/

typedef enum state
{
	WIN,
	LOSE,
	NOSTATE,
	RETRY
}	t_statenum;

typedef enum textures
{
	NORTH,
	EAST,
	SOUTH,
	WEST,
	FLOOR,
	CEILING,
	DOOR_O,
	DOOR_C,
	DOOR_S,
}	t_textures;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_identifier
{
	t_textures	direction;
	char		*filename;		
	t_img		attr;
	int			color;
}	t_id;

typedef struct s_tex
{
	int		line_h;
	int		line_off;
	float	tx;
	float	ty;
	float	ty_off;
	float	ty_step;
	int		tile_sz;
}	t_tex;

typedef struct s_map
{
	char	**arr;
	char	*name;
	char	**temp_arr;
	char	*temp_str;
	t_id	textures[9];
	int		open_fd;
	int		elements_set;
	int		content_start;
	int		xpos;
	int		ypos;
	int		height;
	int		width;
	int		max_length;
	char	start_dir;
}	t_map;

typedef struct s_play
{
	float	px;
	float	py;
	float	pa;
	float	pdx;
	float	pdy;
}	t_play;

typedef struct s_drawp
{
	int		ipx;
	int		ipy;
	int		rel_x;
	int		rel_y;
	float	offset_x;
	float	offset_y;
	int		draw_x;
	int		draw_y;
}	t_drawp;

typedef struct s_emini
{
	float	ex;
	float	ey;
	int		enemy_tile_x;
	int		enemy_tile_y;
	int		rel_x;
	int		rel_y;
	float	offset_x;
	float	offset_y;
	int		draw_x;
	int		draw_y;
	int		radius;
	int		bx;
	int		by;
	int		px;
	int		py;
}	t_emini;

typedef struct s_move
{
	int	move_w;
	int	move_a;
	int	move_s;
	int	move_d;
	int	move_al;
	int	move_ar;
}	t_move;

typedef struct s_movestat
{
	double	delta_time;
	int		xo;
	int		yo;
	int		ipx;
	int		ipx_add_xo;
	int		ipx_sub_xo;
	int		ipy;
	int		ipy_add_yo;
	int		ipy_sub_yo;
}	t_movestat;

typedef struct s_sprite
{
	int		sprite_size;
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	dist_sq;
	float	min_dist;
	float	dist;
	float	overlap;
	float	adjust_x;
	float	adjust_y;
	float	speed;
	float	margin;
	float	lil_margin;
	int		spx;
	int		spy;
	float	spx_left;
	float	spx_right;
	float	spy_up;
	float	spy_down;
}	t_sprite;

typedef struct s_direction
{
	int	dx;
	int	dy;
}	t_direction;

typedef struct s_minimap
{
	int	start_x;
	int	start_y;
}	t_minimap;

typedef struct s_line
{
	float	px;
	float	py;
	float	rx;
	float	ry;
	float	dx;
	float	dy;
	int		steps;
	float	x_inc;
	float	y_inc;
	int		px_int;
	int		py_int;
}	t_line;

typedef struct s_ray
{
	int		r;
	int		mx;
	int		my;
	int		mp;
	int		dof;
	int		side_h;
	int		side_v;
	float	vx;
	float	vy;
	float	rx;
	float	ry;
	float	ra;
	float	xo;
	float	yo;
	float	dis_v;
	float	dis_h;
	float	tan;
	char	hit_type_h;
	char	hit_type_v;
	float	ori_x;
	float	ori_y;
	int		cur_tile;
	float	angle_step;
}	t_ray;

typedef struct s_edraw
{
	int				anim_sequence[16];
	int				anim_len;
	struct timeval	now;
	double			elapsed;
	float			sx;
	float			sy;
	float			sin_pa;
	float			cos_pa;
	float			dx;
	float			dy;
	float			fov_scale;
	float			proj_x;
	float			sprite_height;
	int				sprite_size;
	int				max_sprite_size;
	float			line_h;
	int				floor_y;
	int				screen_x;
	int				screen_y;
	int				frame;
	t_img			*cur_img;
	int				px;
	int				ray_idx;
	int				py;
	int				tx;
	int				ty;
	int				offset;
	char			*pixel;
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
	unsigned char	a;
	int				color;
	int				x;
	int				y;
}	t_edraw;

typedef struct s_rayhit
{
	int		p_tile_x;
	int		p_tile_y;
	float	p_offset_x;
	float	p_offset_y;
	int		draw_px;
	int		draw_py;
	int		r_tile_x;
	int		r_tile_y;
	float	r_offset_x;
	float	r_offset_y;
	int		draw_rx;
	int		draw_ry;
}	t_rayhit;

typedef struct s_gif
{
	t_img	zero;
	t_img	one;
	t_img	two;
	t_img	three;
	t_img	four;
	t_img	five;
	t_img	six;
	t_img	seven;
	t_img	eight;
}	t_gif;

typedef struct s_win_gif
{
	t_img	zero;
	t_img	one;
	t_img	two;
	t_img	three;
}	t_win_gif;

typedef struct s_place
{
	int	count;
	int	index;
	int	i;
	int	y;
	int	x;
}	t_place;

typedef struct s_bfs
{
	int		empty_spaces;
	int		ipx;
	int		ipy;
	int		dirs[4][2];
	int		*queue_x;
	int		*queue_y;
	bool	**reachable;
	int		front;
	int		rear;
	int		**prev_y;
	int		**prev_x;
}	t_bfs;

typedef struct s_enemy_bfs
{
	int		*queue_x;
	int		*queue_y;
	int		front;
	int		rear;
	bool	**visited;
	int		**prev_x;
	int		**prev_y;
	int		dir[4][2];
	int		width;
	int		height;
	int		goal_x;
	int		goal_y;
	int		start_x;
	int		start_y;
	int		size;
	int		x;
	int		y;
	int		i;
	int		nx;
	int		ny;
	int		tpx;
	int		tpy;
	int		px;
	int		py;
}	t_enemy_bfs;

typedef struct s_state
{
	t_img	lose;
	t_img	win;
	int		state;
}	t_state;

typedef struct s_save
{
	t_sprite	*sprites;
	char		**map;
}	t_save;

typedef struct s_var
{
	void			*mlx;
	void			*win;
	char			**big_map;
	int				big_width;
	int				big_height;
	t_save			save;
	t_map			map;
	t_img			image;
	t_play			player;
	t_move			move;
	t_state			state;
	t_gif			gif;
	t_win_gif		win_gif;
	t_minimap		minimap;
	t_sprite		*sprites;
	t_sprite		win_sprite;
	struct timeval	last_time;
	int				last_mouse_x;
	int				mouse_state;
	int				minimap_offset_x;
	int				minimap_offset_y;
	int				num_sprites;
	float			zbuffer[NUM_RAYS];
	int				current_anim_index;
	struct timeval	last_anim_time;
}	t_var;

/*------------------------------MAP_VALIDATION------------------------------*/

// from extract_map_bonus.c
void		extract_map(t_map *map);
void		check_map_name(char *file);

// from extract_elements_bonus.c
void		extract_elements(t_map *map);
int			verify_id_dir(t_map *map, char **arr, t_id **id);
int			verify_id(t_map *map, char **arr, int line);
int			verify_rgb(char *value);
t_id		*set_id(t_id *id, t_textures value);

// from extract_content_bonus.c
void		extract_content(t_map *map);
void		get_map_height(t_map *map);
void		fill_map_arr(t_map *map);
void		skip_to_content(t_map *map);

// from check_map_utils_bonus.c
void		find_max_row_length(t_map *map);
void		adjust_map_length(char **map_row, t_map *map);
void		replace_space(t_map *map);
void		validate_player(t_map *map, int player);

// from check_map_bonus.c
void		validate_map_char(t_map *map);
void		check_surrounding(t_map *map, int y, int x);
void		check_wall(t_map *map);
void		check_map(t_map *map);
void		change_player(t_map *map);

/*------------------------------ERROR_HANDLING------------------------------*/

// from handle_error_bonus.c
void		handle_error_noexit(char *err, char *msg, t_map *map, t_var *data);
void		handle_error(char *err, char *msg, t_map *map, t_var *data);

// from handle_error_map_bonus.c
int			element_err(int line);
void		clean_map(t_map *map);
void		clean_temp(t_map *map);
void		clean_texture(t_map *map);

// from handle_error_data_bonus.c
void		close_mlx(t_var *data);
void		clean_data(t_var *data);
void		clean_data_texture(t_map *map, t_var *data);
void		free_state_images(t_var *data);
void		free_enemy_gifs(t_var *data);

// from handle_error_utils_bonus.c
void		free_single_img(void **img_ptr, t_var *data);
void		safe_close(int *fd);
void		free_win_gifs(t_var *data);

// from handle_error_bfs_bonus.c
void		free_enemy_bfs(t_var *data, t_bfs *bfs);
void		enemy_bfs_error(t_var *data, t_bfs *bfs, char *msg);
void		free_ebfs(t_enemy_bfs *bfs);
void		enemy_move_bfs_error(t_var *data, t_enemy_bfs *bfs, char *msg);

/*------------------------------WINDOW------------------------------*/

// from window_bonus.c
int			create_visual(t_map *map);
int			close_window(t_var *data);
int			render(t_var *data);

// from init_struct_bonus.c
void		init_player(t_var *data);
void		init_sprites(t_var *data);
void		init_all(t_var *data);
void		init_minimap_offset(t_var *data);

// from window_utils_bonus.c
void		load_single_image(t_var *data, t_img *img, char *path);
void		my_mlx_pixel_put(t_img *img, int x, int y, int color);
void		create_image_buffer(t_var *data);
void		show_lose_screen(t_var *data);
void		show_win_screen(t_var *data);

// from init_win_bonus.c
void		load_win_gifs(t_var *data);
void		place_winning_tiles(t_var *data);
void		change_to_win(t_var *data, t_bfs *bfs, int index);
void		change_win_tile(t_var *data, int x, int y, bool change);

// from init_enemy_bonus.c
void		load_enemy_gifs(t_var *data);
void		place_enemy(t_var *data, t_bfs *bfs);
void		forbidden_enemy(t_var *data, t_bfs *bfs);
void		init_sprites(t_var *data);
void		place_enemy_helper(t_var *data, t_bfs *bfs, t_place *enemy);

// from init_enemy_bfs_bonus.c
void		init_dir( t_bfs *bfs);
void		init_bfs(t_var *data, t_bfs *bfs);
void		bfs_check(t_var *data, t_bfs *bfs, int nx, int ny);
void		do_bfs(t_var *data, t_bfs *bfs);

// from init_retry_bonus.c
void		copy_sprites_save(t_var *data);
void		re_init(t_var *data);

// from init_big_map_bonus.c
void		init_big_map(t_var *data);
void		create_big_map_helper(t_var *data, int y, int x);
void		create_big_map(t_var *data);

/*------------------------------MINIMAP------------------------------*/

// from minimap_bonus.c
void		create_minimap(t_var *data);
void		draw_tile(t_img *img, int x, int y, int color);
void		draw_map(t_var *data, int x, int y);
void		map_shift(t_var *data);
void		clamp_map(t_var *data);

// from enemy_minimap_bonus.c
void		draw_enemies_minimap(t_var *data);
void		draw_enemies_init(t_var *data, t_emini *mini, int i);
void		draw_enemies_loop(t_var *data, t_emini *mini);

// from door_minimap_bonus.c
void		draw_horizontal_door_open(t_img *img, int x, int y, int door_color);
void		draw_vertical_door_open(t_img *img, int x, int y, int door_color);
void		draw_horizontal_door(t_img *img, int x, int y, int door_color);
void		draw_vertical_door(t_img *img, int x, int y, int door_color);
void		check_map_door(t_var *data, int tile, int draw_x, int draw_y);

// froom win_minimap_bonus.c
void		draw_one_winning_tile(t_var *data, int draw_x, int draw_y);
void		draw_winning_tile(t_var *data);

/*------------------------------PLAYER------------------------------*/

// from player_bonus.c
void		draw_player(t_var *data);
void		player_start(t_var *data, int y, int x);
void		player_location(t_var *data, t_drawp *drawp);

// from player_win_bonus.c
void		win(t_var *data);
void		draw_win(t_var *data);

/*------------------------------MOVEMENT------------------------------*/

// from movement_helper_bonus.c
void		mouse_state(t_var *data);

// from update_movement_bonus.c
bool		is_valid_movement( char tile);
void		update_movement(t_var *data);
void		movement_init(t_var *data, t_movestat *movestat);
void		movement_ws(t_var *data, t_movestat *movestat);
void		movement_da(t_var *data, t_movestat *movestat,
				int strafe_ipx, int strafe_ipy);
void		win(t_var *data);

//from movement_bonus.c
int			handle_keypress(int keysym, t_var *data);
int			handle_keyrelease(int keysym, t_var *data);
int			handle_mouse_move(int x, int y, t_var *data);
float		normalize_radians(float angle);
double		get_delta_time(t_var *data);

/*------------------------------RAYCAST------------------------------*/

// from raycast_bonus.c
void		draw_line(t_var *data, t_line line, int color);
void		cast_rays(t_var *data, t_ray *ray);
void		draw_rays(t_var *data);
void		create_rayhit(t_var *data, t_ray *ray,
				t_rayhit *rayhit, int tile_size);

// from raycast_3d_bonus.c
int			get_line_height(float dist, float pa, float ra);
void		init_tile(t_var *data, t_ray *ray, t_tex *tile);
void		draw_3d(t_var *data, t_ray *ray);
void		draw_3d_helper(t_var *data, t_ray *ray, t_tex *tile);
void		draw_wall_strip(t_img *img, int x, int y, int color);

// from raycast_helper_bonus.c
void		cast_vertical(t_var *data, t_ray *ray);
void		vertical_dof(t_var *data, t_ray *ray);
void		cast_horizontal(t_var *data, t_ray *ray);
void		horizontal_dof(t_var *data, t_ray *ray);
bool		is_wall(t_var *data, int x, int y, int notWall);

// from textures_bonus.c
void		load_textures(t_var *data);
int			extract_img(void *mlx, t_img *attr, char *filename, t_var *data);
int			extract_rgb(int *color, char *rgb, t_var *data);
t_img		*get_texture(t_var *data, t_ray *ray);
int			get_color(int x, int y, t_img *tex);

/*------------------------------DOOR------------------------------*/
// from door_check_bonus.c
bool		is_door(char c);
bool		check_door_dof(t_var *data, t_ray *ray, int *found_x, int *found_y);
void		check_for_door_in_fov(t_var *data, int *found_x, int *found_y);
void		update_mxy_from_rxy(t_ray *ray);

//from door_create_bonus.c
void		create_door(t_var *data);
void		open_door(t_var *data);

//from door_create_big_bonus.c
void		create_door_big_map(t_var *data, int y, int x);
void		delete_door_big_map(t_var *data, int y, int x);
void		update_door_big_map(t_var *data, int y, int x);

/*------------------------------ENEMY------------------------------*/

// from enemy_sprites_bonus.c
int			is_player_caught(t_sprite *sp, t_play *player, float radius);
bool		is_cell_valid(t_var *data, float x, float y);
void		resolve_enemy_dist(t_var *data, t_sprite *sp, t_sprite *other);
void		resolve_enemy_collisions(t_var *data, t_sprite *sp);
void		move_enemy_towards_player(t_var *data, t_sprite *sp);

// from enemy_move_bonus.c
int			enemy_left(t_var *data, t_sprite *sp);
int			enemy_right(t_var *data, t_sprite *sp);
int			enemy_up(t_var *data, t_sprite *sp);
int			enemy_down(t_var *data, t_sprite *sp);

// from enemy_unstuck_bonus.c
void		ebfs_five(t_direction *step, t_enemy_bfs *bfs);
t_direction	find_first_step_to_player(t_var *data, t_enemy_bfs *bfs);
void		unstuck_move(t_var *data, t_sprite *sp);

// from enemy_unstuck_helper_bonus.c
void		ebfs_one(t_enemy_bfs *bfs, t_var *data);
void		ebfs_two(t_enemy_bfs *bfs, t_var *data);
void		ebfs_three(t_enemy_bfs *bfs);
void		ebfs_four_helper(char **map, t_enemy_bfs *bfs);
void		ebfs_four(char **map, t_enemy_bfs *bfs);

// from enemy_draw_bonus.c
float		calculate_distance(t_var *data, t_sprite *sp);
void		sort_sprites_by_distance(t_var *data);
void		init_seq(t_edraw *draw);
void		init_enemy_draw(t_var *data, t_edraw *draw);
int			enemy_size(t_var *data, t_edraw *draw, t_sprite *sp);

// from enemy_draw_helper_bonus.c
void		select_frame(t_var *data, t_edraw *draw);
void		screen_rgba( t_edraw *draw);
void		screen_draw_helper(t_var *data, t_edraw *draw);
void		screen_draw(t_var *data, t_edraw *draw);
void		draw_sprites(t_var *data);

void		print_map_and_enemies(t_var *data);

#endif
