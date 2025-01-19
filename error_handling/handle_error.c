#include "../cub3d.h"

void	handle_error(char *err)
{
	if (!err)
		return ;
	write(2, "Error\n", 6);
	write(2, err, ft_strlen(err));
	write(2, "\n", 1);
}

int	element_err(int line)
{
	char	*str;

	str = ft_itoa(line);
	if (!line)
		return (ft_error_return("malloc failed"));
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd("Invalid configuration of map elements in line ", 2);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
	free(str);
	return (0);
}
