#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
#include <fcntl.h>       // open, close
#include <unistd.h>      // read, write, close
#include <stdio.h>       // printf, perror
#include <stdlib.h>      // malloc, free, exit
#include <string.h>      // strerror
#include <sys/time.h>    // gettimeofday
#include <math.h>        //gcc your_program.c -lm
#include <stdio.h>

# include "minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <X11/X.h>

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 512
#define PLAYER_COLOR 0x00FF0000
#define RAYCAST_COLOR 0x0000FF00
#define WALL_COLOR 0x00AAAAAA
#define EMPTY_COLOR 0x404040

#define STRIP_WIDTH 2
#define CEILING_COLOR 0x444444
#define FLOOR_COLOR 0x222222

#define MAP_WIDTH  8
#define MAP_HEIGHT 8
#define TILE_SIZE  64
#define TILE_SIZE_TEXTURE  32

#define PI  3.14159265359
#define P2  (PI / 2)
#define P3  (3 * P2)

#define PLAYER_SIZE  10
#define NUM_RAYS (WINDOW_WIDTH - MAP_WIDTH * TILE_SIZE) / STRIP_WIDTH
#define NUM_RAY 64
#define FOV (PI / 3)
#define MOVEMENT_SPEED 100
#define ROTATION_SPEED 2
#define MAX_DELTA_TIME 0.1 

typedef enum	direction
{
	NOTHING,
	NORTH,
	EAST,
	SOUTH,
	WEST,
	FLOOR,
	CEILING
}				direction;

typedef struct	s_identifier
{
	direction	direction;
	char		*filename;			// need to be freed
}				t_id;

typedef struct  s_map
{
	char	*name;
	
	int		elements_set;
	t_id	north;
	t_id	east;
	t_id	south;
	t_id	west;
	t_id	floor;
	t_id	ceiling;

	int		content_start;
    int		height;
    int		max_length;
    char	**arr;

	int xpos;
	int ypos;
}				t_map;

typedef struct	cub3d
{
	t_map	map;
}				t_cub;

typedef struct s_img {
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}   t_img;

typedef struct s_play {
	float px;
	float py;
	float pa;
	float pdx;
	float pdy;
}   t_play;

typedef struct s_move {
	int move_w;
	int move_a;
	int move_s;
	int move_d;
	int move_al;
	int move_ar;
}   t_move;

typedef struct s_var {
    void *mlx;
    void *win;
	t_map	map;
	t_img   image;
	t_play   player;
	t_move move;
	struct timeval last_time;

} t_var;

typedef struct s_line {
	float px;
	float py;
	float rx;
	float ry;
	float dx;
	float dy;
	int steps;
	float x_inc;
	float y_inc;
} t_line;

typedef struct s_ray {
	int r;
	int mx;
	int my;
	int mp;
	int dof;
	int side; 
	float vx;
	float vy;
	float rx;
	float ry;
	float ra;
	float xo;
	float yo;
	float disV;
	float disH;
	float tan;
} t_ray;

// from extract.c
int		extract_map(t_map *map);
int		check_map_name(char *file);
void    handle_error(char *err);

// from extract_elements.c
int		extract_elements(t_map *map, int fd);
int		verify_id(t_map *map, char **arr, int line);
int		verify_rgb(char *value);
t_id	*set_id(t_id *id, direction value);

// from extract_content.c
int		extract_content(t_map *map, int fd);
void	get_map_height(t_map *map, int fd);
int		fill_map_arr(t_map *map);
void	skip_to_content(t_map *map, int fd);

// from check_map_utils.c
void	find_max_row_length(t_map *map);
void	adjust_map_length(char **map_row, t_map *map);
void	replace_space(t_map *map);

// from check_map.c
void	validate_map_char(t_map *map);
void	check_surrounding(t_map *map, int y, int x);
void	check_wall(t_map *map);
int	check_map(t_map *map);

// from handle_error.c
void	handle_error(char *err);
int		element_err(int line);

// from window.c

int	create_visual(t_cub *cube);
int	close_window(t_var *data);
int	key_hook(int keysym, t_var *data);
void my_mlx_pixel_put(t_img *img, int x, int y, int color);
void create_image_buffer(t_var *data);

// from minimap.c
void    create_minimap(t_var *data);
void draw_tile(t_img *img, int x, int y, int color);
void draw_map(t_var *data, int x, int y);
void player_start(t_var *data, int y, int x);

// from player.c
void draw_player(t_var *data);

//from movement.c
int handle_mouse_move(int x, int y, t_var *data);
int handle_keypress(int keysym, t_var *data);
int handle_keyrelease(int keysym, t_var *data);
void update_movement(t_var *data);
float normalize_radians(float angle);
double get_delta_time(t_var *data);

// from init_struct.c
void init_move(t_var *data);
void init_player(t_var *data);
void init_all(t_var *data, t_cub *cube);

// from raycast.c
void draw_line(t_var *data, t_line line, int color);
void cast_rays(t_var *data, t_ray *ray);
void draw_rays(t_var *data);

// from raycast_helper.c
void cast_vertical (t_var* data, t_ray* ray);
void vertical_dof(t_var* data, t_ray* ray);
void cast_horizontal (t_var *data, t_ray * ray);
void horizontal_dof(t_var* data, t_ray* ray);


#endif