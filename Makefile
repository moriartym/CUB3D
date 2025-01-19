CC = cc

CFLAGS_NORMAL = -Wall -Wextra -Werror

NAME = cub3d

LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

SRCS_NORMAL = get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c \
		cub3d.c \
		map_validation/extract_map.c \
		map_validation/extract_elements.c \
		map_validation/extract_content.c \
		map_validation/check_map.c \
		map_validation/check_map_utils.c \
		error_handling/handle_error.c \

OBJS = $(SRCS_NORMAL:.c=.o)

all: $(NAME)

bonus: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS_NORMAL) -c $< -o $@

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
