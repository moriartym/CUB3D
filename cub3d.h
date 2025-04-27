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

    int		num_player;
}				t_map;

typedef struct	cub3d
{
	t_map	map;
}				t_cub;

typedef struct s_var {
    void *mlx;
    void *win;

    float px, py;
    float pa;
    float pdx, pdy;

	int move_w;
    int move_a;
    int move_s;
    int move_d;

	struct timeval last_time;
} t_var;

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

int	create_visual(t_cub *cub3);
int	close_window(t_var *data);
int	key_hook(int keysym, t_var *data);

#endif