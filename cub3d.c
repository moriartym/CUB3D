#include "cub3d.h"

int main(int argc, char **argv)
{
	t_cub	cub;

	cub = (t_cub){0};
	if (argc != 2)
		return (ft_putstr_fd("./cub3d map.cub\n", 1), 1);
	cub.map.name = argv[1];
	if (extract_map(&cub.map) == 1)
		return (1);
	printf("OK\n");
}
