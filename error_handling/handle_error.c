#include "cub3d.h"

void    handle_error(char *err)
{
    if (!err)
        return ;
    write(2, "Error\n", 6);
    write(2, err, ft_strlen(err));
    write(2, "\n", 1);
}