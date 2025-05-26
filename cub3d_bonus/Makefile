CC = cc

CFLAGS_NORMAL = -Wall -Wextra -Werror

NAME = cub3D_bonus

LIBFT_DIR = libft
MLX_DIR = "../minilibx-linux"

LIBFT = $(LIBFT_DIR)/libft.a

SRCS_NORMAL = get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c \
		cub3d_bonus.c \
		map_validation_bonus/extract_map_bonus.c \
		map_validation_bonus/extract_elements_bonus.c \
		map_validation_bonus/extract_content_bonus.c \
		map_validation_bonus/check_map_bonus.c \
		map_validation_bonus/check_map_utils_bonus.c \
		error_handling_bonus/handle_error_bonus.c \
		error_handling_bonus/handle_error_map_bonus.c \
		error_handling_bonus/handle_error_utils_bonus.c \
		error_handling_bonus/handle_error_bfs_bonus.c \
		error_handling_bonus/handle_error_data_bonus.c \
		window_bonus/window_bonus.c \
		window_bonus/window_utils_bonus.c \
		window_bonus/init_struct_bonus.c \
		window_bonus/init_win_bonus.c \
		window_bonus/init_enemy_bonus.c \
		window_bonus/init_enemy_bfs_bonus.c \
		window_bonus/init_retry_bonus.c \
		window_bonus/init_big_map_bonus.c \
		minimap_bonus/minimap_bonus.c \
		minimap_bonus/door_minimap_bonus.c \
		minimap_bonus/win_minimap_bonus.c \
		minimap_bonus/enemy_minimap_bonus.c \
		player_bonus/player_bonus.c \
		player_bonus/player_win_bonus.c \
		movement_bonus/movement_bonus.c \
		movement_bonus/update_movement_bonus.c \
		movement_bonus/movement_helper_bonus.c \
		raycast_bonus/raycast_bonus.c \
		raycast_bonus/raycast_3d_bonus.c \
		raycast_bonus/raycast_helper_bonus.c \
		raycast_bonus/textures_bonus.c \
		enemy_bonus/enemy_sprites_bonus.c \
		enemy_bonus/enemy_draw_bonus.c \
		enemy_bonus/enemy_draw_helper_bonus.c \
		enemy_bonus/enemy_move_bonus.c \
		enemy_bonus/enemy_unstuck_bonus.c \
		enemy_bonus/enemy_unstuck_helper_bonus.c \
		door_bonus/door_create_bonus.c \
		door_bonus/door_check_bonus.c \
		door_bonus/door_create_big_bonus.c \

OBJS = $(SRCS_NORMAL:.c=.o)

all: $(NAME)

bonus: $(NAME)

# DELETE THIS BEFORE SUBMISSION
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    MLX_FLAGS = -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
else ifeq ($(UNAME_S),Darwin)
    MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
endif

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(MLX_FLAGS) -L$(LIBFT_DIR) -lft -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS_NORMAL) -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(LIBFT):
	$(MAKE) bonus -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS) $(OBJS_BONUS)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re bonus
