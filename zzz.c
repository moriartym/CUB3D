#include "mlx.h"

#define WIDTH 800
#define HEIGHT 600

typedef struct s_img {
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}   t_img;

typedef struct s_vars {
    void    *mlx;
    void    *win;
    t_img   img;
}   t_vars;

void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char *dst;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

int main(void)
{
    t_vars vars;

    // Init MLX
    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Image Draw");

    // Create image
    vars.img.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
    vars.img.addr = mlx_get_data_addr(vars.img.img,
            &vars.img.bits_per_pixel,
            &vars.img.line_length,
            &vars.img.endian);

    // Draw something in the image buffer
    for (int y = 100; y < 200; y++)
    {
        for (int x = 100; x < 300; x++)
        {
            my_mlx_pixel_put(&vars.img, x, y, 0x00FF00); // Green rectangle
        }
    }

    // Show image in window
    mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);

    mlx_loop(vars.mlx);
    return (0);
}
