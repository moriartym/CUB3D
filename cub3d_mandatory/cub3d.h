/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:51:45 by dfasius           #+#    #+#             */
/*   Updated: 2025/05/26 13:51:47 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*------------------------------HEADER------------------------------*/

# include "../minilibx-linux/mlx.h"
# include "libft/libft.h"
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
# include <X11/keysym.h>
# include <X11/X.h>

/*------------------------------MACRO------------------------------*/

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1088

# define PI 3.141592653589793238462643383279502884197

# define TILE_SIZE  32
# define TILE_SIZE_TEXTURE  64

# define PLAYER_SIZE 2
# define MOVEMENT_SPEED 50
# define ROTATION_SPEED 2

# define STRIP_WIDTH 2
# define NUM_RAYS 960
# define FOV 1.047197551196597746154214461093167628065
# define MAX_DELTA_TIME 0.1

# define EMPTY_SPACE '0'
# define WALL '1'

/*------------------------------STRUCT------------------------------*/

typedef enum textures
{
	NORTH,
	EAST,
	SOUTH,
	WEST,
	FLOOR,
	CEILING,
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
	t_id	textures[6];
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

typedef struct s_ray
{
	int		r;
	int		mx;
	int		my;
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
}	t_ray;

typedef struct s_var
{
	void			*mlx;
	void			*win;
	t_map			map;
	t_img			image;
	t_play			player;
	t_move			move;
	struct timeval	last_time;
	float			zbuffer[NUM_RAYS];
}	t_var;

/*------------------------------MAP_VALIDATION------------------------------*/

// from extract_map.c
void		extract_map(t_map *map);
void		check_map_name(char *file);

// from extract_elements.c
void		extract_elements(t_map *map);
int			verify_id_dir(t_map *map, char **arr, t_id **id);
int			verify_id(t_map *map, char **arr, int line);
int			verify_rgb(char *value);
t_id		*set_id(t_id *id, t_textures value);

// from extract_content.c
void		extract_content(t_map *map);
void		get_map_height(t_map *map);
void		fill_map_arr(t_map *map);
void		skip_to_content(t_map *map);

// from check_map_utils.c
void		find_max_row_length(t_map *map);
void		adjust_map_length(char **map_row, t_map *map);
void		replace_space(t_map *map);
void		validate_player(t_map *map, int player);

// from check_map.c
void		validate_map_char(t_map *map);
void		check_surrounding(t_map *map, int y, int x);
void		check_wall(t_map *map);
void		check_map(t_map *map);
void		change_player(t_map *map);

/*------------------------------ERROR_HANDLING------------------------------*/

// from handle_error.c
void		handle_error_noexit(char *err, char *msg, t_map *map, t_var *data);
void		handle_error(char *err, char *msg, t_map *map, t_var *data);

// from handle_error_map.c
int			element_err(int line);
void		clean_map(t_map *map);
void		clean_temp(t_map *map);
void		clean_texture(t_map *map);

// from handle_error_data.c
void		close_mlx(t_var *data);
void		clean_data(t_var *data);
void		clean_data_texture(t_map *map, t_var *data);

// from handle_error_utils.c
void		free_single_img(void **img_ptr, t_var *data);
void		safe_close(int *fd);

/*------------------------------WINDOW------------------------------*/

// from window.c
int			create_visual(t_map *map);
int			close_window(t_var *data);
int			render(t_var *data);

// from init_struct.c
void		init_player(t_var *data);
void		init_all(t_var *data);

// from window_utils.c
void		load_single_image(t_var *data, t_img *img, char *path);
void		my_mlx_pixel_put(t_img *img, int x, int y, int color);
void		create_image_buffer(t_var *data);

/*------------------------------PLAYER------------------------------*/

// from player.c
void		player_start(t_var *data, int y, int x);

/*------------------------------MOVEMENT------------------------------*/

// from update_movement.c
bool		is_valid_movement( char tile);
void		update_movement(t_var *data);
void		movement_init(t_var *data, t_movestat *movestat);
void		movement_ws(t_var *data, t_movestat *movestat);
void		movement_da(t_var *data, t_movestat *movestat,
				int strafe_ipx, int strafe_ipy);

//from movement.c
int			handle_keypress(int keysym, t_var *data);
int			handle_keyrelease(int keysym, t_var *data);
float		normalize_radians(float angle);
double		get_delta_time(t_var *data);

/*------------------------------RAYCAST------------------------------*/

// from raycast.c
void		cast_rays(t_ray *ray);
void		draw_rays(t_var *data);

// from raycast_3d.c
int			get_line_height(float dist, float pa, float ra);
void		init_tile(t_var *data, t_ray *ray, t_tex *tile);
void		draw_3d(t_var *data, t_ray *ray);
void		draw_3d_helper(t_var *data, t_ray *ray, t_tex *tile);
void		draw_wall_strip(t_img *img, int x, int y, int color);

// from raycast_helper.c
void		cast_vertical(t_var *data, t_ray *ray);
void		vertical_dof(t_var *data, t_ray *ray);
void		cast_horizontal(t_var *data, t_ray *ray);
void		horizontal_dof(t_var *data, t_ray *ray);
bool		is_wall(t_var *data, int x, int y);

// from textures.c
void		load_textures(t_var *data);
int			extract_img(void *mlx, t_img *attr, char *filename, t_var *data);
int			extract_rgb(int *color, char *rgb, t_var *data);
t_img		*get_texture(t_var *data, t_ray *ray);
int			get_color(int x, int y, t_img *tex);

#endif
