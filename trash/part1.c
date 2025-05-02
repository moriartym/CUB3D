#include "cub3d.h"
#include <math.h>

#define WIDTH 1024
#define HEIGHT 512
#define MAP_WIDTH  8
#define MAP_HEIGHT 8
#define TILE_SIZE  64
#define BORDER_COLOR 0x000000
#define DARK_GREY    0x404040
#define PLAYER_COLOR 0xFF0000
#define PLAYER_SIZE  10
#define PI  3.14159265359
#define P2  (PI / 2)
#define P3  (3 * P2)
#define NUM_RAYS 64
#define FOV (PI / 3)

int map[] = {
    1,1,1,1,1,1,1,1,
    1,0,1,0,0,0,1,1,
    1,0,1,0,0,0,0,1,
    1,0,1,0,0,0,0,1,
    1,0,0,0,0,0,0,1,
    1,0,1,1,0,1,0,1,
    1,0,0,1,0,0,0,1,
    1,1,1,1,1,1,1,1,
};

int close_window(t_var *data)
{
    if (data->mlx && data->win)
        mlx_destroy_window(data->mlx, data->win);
    if (data->mlx)
    {
        mlx_destroy_display(data->mlx);
        free(data->mlx);
    }
    exit(0);
    return 0;
}

void put_pixel(char *addr, int x, int y, int color, int bpp, int line_len)
{
    int offset = y * line_len + x * (bpp / 8);
    *(unsigned int *)(addr + offset) = color;
}

void draw_tile(char *addr, int x, int y, int tile_color, int bpp, int line_len)
{
    for (int i = 0; i < TILE_SIZE; i++)
    {
        for (int j = 0; j < TILE_SIZE; j++)
        {
            int draw_x = x * TILE_SIZE + j;
            int draw_y = y * TILE_SIZE + i;
            int color = (i == 0 || i == TILE_SIZE - 1 || j == 0 || j == TILE_SIZE - 1) ? BORDER_COLOR : tile_color;
            put_pixel(addr, draw_x, draw_y, color, bpp, line_len);
        }
    }
}

void draw_player(char *addr, t_var *data, int bpp, int line_len)
{
    for (int y = data->py; y < data->py + PLAYER_SIZE; y++)
        for (int x = data->px; x < data->px + PLAYER_SIZE; x++)
            put_pixel(addr, x, y, PLAYER_COLOR, bpp, line_len);
}

void draw_player_direction(char *addr, t_var *data, int bpp, int line_len)
{
    int line_length = 30;
    int thickness = 3; // Line thickness
    int start_x = data->px + PLAYER_SIZE / 2;
    int start_y = data->py + PLAYER_SIZE / 2;
    int end_x = start_x + cos(data->pa) * line_length;
    int end_y = start_y + sin(data->pa) * line_length;

    int dx = end_x - start_x;
    int dy = end_y - start_y;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float x_inc = dx / (float)steps;
    float y_inc = dy / (float)steps;
    float x = start_x;
    float y = start_y;

    for (int i = 0; i <= steps; i++) {
        for (int t = -thickness / 2; t < thickness / 2; t++) {
            put_pixel(addr, (int)(x + t), (int)y, 0x00FF00, bpp, line_len); // Green line
        }
        x += x_inc;
        y += y_inc;
    }
}

void cast_horizontal_ray(t_var *data, float ra, float *hx, float *hy, float *disH)
{
	int dof = 0;
	float ry, rx, yo, xo, aTan = -1 / tan(ra);

	*disH = 1e30;
	*hx = data->px;
	*hy = data->py;

	if (ra > PI) {
		ry = (((int)data->py >> 6) << 6) - 0.0001;
		rx = (data->py - ry) * aTan + data->px;
		yo = -64;
		xo = -yo * aTan;
	} else if (ra < PI) {
		ry = (((int)data->py >> 6) << 6) + 64;
		rx = (data->py - ry) * aTan + data->px;
		yo = 64;
		xo = -yo * aTan;
	} else return;

	while (dof < 8) {
		int mx = (int)(rx) >> 6;
		int my = (int)(ry) >> 6;
		int mp = my * MAP_WIDTH + mx;
		if (mp >= 0 && mp < MAP_WIDTH * MAP_HEIGHT && map[mp] == 1) {
			*hx = rx;
			*hy = ry;
			*disH = sqrtf((*hx - data->px) * (*hx - data->px) + (*hy - data->py) * (*hy - data->py));
			break;
		}
		rx += xo;
		ry += yo;
		dof++;
	}
}
void cast_vertical_ray(t_var *data, float ra, float *vx, float *vy, float *disV)
{
	int dof = 0;
	float rx, ry, xo, yo, nTan = -tan(ra);

	*disV = 1e30;
	*vx = data->px;
	*vy = data->py;

	if (ra > P2 && ra < P3) {
		rx = (((int)data->px >> 6) << 6) - 0.0001;
		ry = (data->px - rx) * nTan + data->py;
		xo = -64;
		yo = -xo * nTan;
	} else if (ra < P2 || ra > P3) {
		rx = (((int)data->px >> 6) << 6) + 64;
		ry = (data->px - rx) * nTan + data->py;
		xo = 64;
		yo = -xo * nTan;
	} else return;

	while (dof < 8) {
		int mx = (int)(rx) >> 6;
		int my = (int)(ry) >> 6;
		int mp = my * MAP_WIDTH + mx;
		if (mp >= 0 && mp < MAP_WIDTH * MAP_HEIGHT && map[mp] == 1) {
			*vx = rx;
			*vy = ry;
			*disV = sqrtf((*vx - data->px) * (*vx - data->px) + (*vy - data->py) * (*vy - data->py));
			break;
		}
		rx += xo;
		ry += yo;
		dof++;
	}
}
void draw_single_ray(t_var *data, char *addr, int bpp, int line_len, float x1, float y1, float x2, float y2, int color)
{
	float dx = x2 - x1;
	float dy = y2 - y1;
	int steps = fabsf(dx) > fabsf(dy) ? fabsf(dx) : fabsf(dy);

	if (steps == 0) return;

	float x_inc = dx / steps;
	float y_inc = dy / steps;
	for (int i = 0; i <= steps; i++) {
		put_pixel(addr, (int)x1, (int)y1, color, bpp, line_len);
		x1 += x_inc;
		y1 += y_inc;
	}
}

void draw_3d_view(t_var *data, char *addr, int bpp, int line_len, float dist, int r)
{
    // Correct fish-eye distortion
	int view_start = WIDTH - 512;
    float corrected_dist = dist * cos(data->pa - (data->pa - FOV / 2 + r * (FOV / NUM_RAYS)));
    float lineH = (TILE_SIZE * 320) / corrected_dist;
    if (lineH > HEIGHT) lineH = HEIGHT;
    float lineOffset = (HEIGHT - lineH) / 2;

    int brightness = 255 - (int)(dist * 0.5); // Adjust the multiplier to control fade rate
    if (brightness < 50) brightness = 50;     // Clamp to prevent fully black walls
    int wall_color = (brightness << 16) | (brightness << 8) | brightness; // RGB grayscale
	int startX = view_start + r * (512 / NUM_RAYS);
	for (int y = 0; y < HEIGHT; y++)
    {
        int color = (y < lineOffset || y > lineOffset + lineH) ? 0x202020 : wall_color;
        for (int x = 0; x < (512 / NUM_RAYS); x++)
            put_pixel(addr, startX + x, y, color, bpp, line_len);
    }
}


void draw_rays(t_var *data, char *addr, int bpp, int line_len)
{
    float ra = data->pa - (FOV / 2);
    if (ra < 0) ra += 2 * PI;
    if (ra > 2 * PI) ra -= 2 * PI;

    for (int r = 0; r < NUM_RAYS; r++) {
        float hx, hy, disH, vx, vy, disV;
        cast_horizontal_ray(data, ra, &hx, &hy, &disH);
        cast_vertical_ray(data, ra, &vx, &vy, &disV);

        float rx = disV < disH ? vx : hx;
        float ry = disV < disH ? vy : hy;
        float dist = disV < disH ? disV : disH;

        draw_single_ray(data, addr, bpp, line_len,
            data->px + PLAYER_SIZE / 2,
            data->py + PLAYER_SIZE / 2,
            rx, ry, 0x00FFFF); // Cyan ray

        draw_3d_view(data, addr, bpp, line_len, dist, r);

        ra += FOV / NUM_RAYS;
        if (ra < 0) ra += 2 * PI;
        if (ra > 2 * PI) ra -= 2 * PI;
    }
}




void render_scene(t_var *data)
{
    void *img;
    char *addr;
    int bpp, line_len, endian;

    img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    addr = mlx_get_data_addr(img, &bpp, &line_len, &endian);

    // Fill background
    for (int y = 0; y < HEIGHT; y++)
        for (int x = 0; x < WIDTH; x++)
            put_pixel(addr, x, y, DARK_GREY, bpp, line_len);

    // Draw map
    for (int y = 0; y < MAP_HEIGHT; y++)
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            int tile = map[y * MAP_WIDTH + x];
            int color = (tile == 1) ? 0xFFFFFF : DARK_GREY;
            draw_tile(addr, x, y, color, bpp, line_len);
        }

    // Draw player
    draw_player(addr, data, bpp, line_len);

    // Draw player direction
    draw_player_direction(addr, data, bpp, line_len);

	//raycast
	draw_rays(data, addr, bpp, line_len);

    mlx_put_image_to_window(data->mlx, data->win, img, 0, 0);
    mlx_destroy_image(data->mlx, img);
}



int handle_keypress(int keysym, t_var *data)
{
    if (keysym == XK_Escape)
        close_window(data);
	else if (keysym == XK_a)
	{
        data->pa -= 0.1;
        if (data->pa < 0) data->pa += 2 * PI;
        data->pdx = cos(data->pa) * 5;
        data->pdy = sin(data->pa) * 5;
    }
	else if (keysym == XK_d)
	{
        data->pa += 0.1; // small rotation step
        if (data->pa > 2 * PI) data->pa -= 2 * PI;
        data->pdx = cos(data->pa) * 5;
        data->pdy = sin(data->pa) * 5;
	}
    else if (keysym == XK_w)
    {
        data->px += data->pdx;
        data->py += data->pdy;
    }
    else if (keysym == XK_s)
    {
        data->px -= data->pdx;
        data->py -= data->pdy;
    }

    render_scene(data);
    return 0;
}

int create_visual(t_cub *cub3)
{
    t_var data = {0};

    data.px = 250;
    data.py = 250;
    data.pa = P2;
    data.pdx = cos(data.pa) * 5;
    data.pdy = sin(data.pa) * 5;

    data.mlx = mlx_init();
    if (!data.mlx)
        return 1;

    data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "cub3d");
    if (!data.win)
        return 1;

    render_scene(&data);

    mlx_hook(data.win, DestroyNotify, StructureNotifyMask, &close_window, &data);
    mlx_hook(data.win, KeyPress, KeyPressMask, &handle_keypress, &data);
    mlx_loop(data.mlx);
    return 0;
}
