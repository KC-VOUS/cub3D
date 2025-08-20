#include "../includes/cub.h"

void	f_c(t_mlx *data)
{
	int	y;
	int	x;

	y = 0;
	while (y <= WIN_H / 2)
	{
		x = 0;
		while (x <= WIN_W)
		{
			put_pxl(data, x, y, rgb(data->map.ceiling_r, data->map.ceiling_g, data->map.ceiling_b));
			x++;
		}
		y++;
	}
	y = WIN_H;
	while (y >= WIN_H / 2)
	{
		x = 0;
		while (x <= WIN_W)
		{
			put_pxl(data, x, y, rgb(data->map.floor_r, data->map.floor_g, data->map.floor_b));
			x++;
		}
		y--;
	}
}

void    vertical_texture_line(t_mlx *data, int screen_x, int drawStart, int drawEnd,
                              t_tex *tex, int lineHeight, int texX)
{
    double  step;
    double  texPos;
    int     y;

    step = (double)tex->h / (double)lineHeight;
    texPos = (drawStart - data->map.screen_h / 2.0 + lineHeight / 2.0) * step;

    if (drawStart < 0)
        drawStart = 0;
    if (drawEnd >= data->map.screen_h)
        drawEnd = data->map.screen_h - 1;

    y = drawStart;
    while (y <= drawEnd)
    {
        int texY = (int)texPos;
        if (texY < 0)
            texY = 0;
        if (texY >= tex->h)
            texY = tex->h - 1;
        texPos += step;

        char *p = tex->addr + texY * tex->line_len + texX * (tex->bpp / 8);
        int color = *(int *)p;

        put_pxl(data, screen_x, y, color);
        y++;
    }
}


void get_rays(t_mlx *data, int x, int w)
{
	// data->player.dir_x = -1.0;
	// data->player.dir_y = 0.0;
	// data->player.plane_x = 0.0;
	// data->player.plane_y = 0.66;
	int		h = data->map.screen_h;
	double cameraX = 2 * x / (double)w - 1;
	double rayDirX = data->player.dir_x + data->player.plane_x * cameraX;//
	double rayDirY = data->player.dir_y + data->player.plane_y * cameraX;//
	int mapX = (int)data->player.pos_x;//
	int mapY = (int)data->player.pos_y;//
	double sideDistX;
	double sideDistY;

	double deltaDistX;
	double deltaDistY;

	if (rayDirX == 0)
		deltaDistX = 1e30;
	else
		deltaDistX = fabs(1.0 / rayDirX);

	if (rayDirY == 0)
		deltaDistY = 1e30;
	else
		deltaDistY = fabs(1.0 / rayDirY);

	double perpWallDist;

	int stepX;
	int stepY;

	int hit = 0;
	int side;

	if (rayDirX < 0)
	{
		stepX = -1;
		sideDistX = (data->player.pos_x - mapX) * deltaDistX;//
	}
	else
	{
		stepX = 1;
		sideDistX = (mapX + 1.0 - data->player.pos_x) * deltaDistX;//
	}
	if (rayDirY < 0)
	{
		stepY = -1;
		sideDistY = (data->player.pos_y - mapY) * deltaDistY;//
	}
	else
	{
		stepY = 1;
		sideDistY = (mapY + 1.0 - data->player.pos_y) * deltaDistY;//
	}
	while(hit == 0)
	{
		if (sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			mapX += stepX;
			side = 0;
		}
		else
		{
			sideDistY += deltaDistY;
			mapY += stepY;
			side = 1;
		}
		if (data->map.map[mapX][mapY] == '1')//
			hit = 1;
	}
	if (side == 0)
		perpWallDist = (sideDistX - deltaDistX);
	else
		perpWallDist = (sideDistY - deltaDistY);
	int lineHeight = (int)(h / perpWallDist);
	int drawStart = -lineHeight / 2 + h / 2;
	if (drawStart < 0)
		drawStart = 0;
	int drawEnd = lineHeight / 2 + h / 2;
	if (drawEnd >= h)
		drawEnd = h - 1;

	t_tex *texture;
if (side == 0) // vertical wall
{
    if (rayDirX > 0)
        texture = &data->image.south;
    else
        texture = &data->image.north;
}
else // horizontal wall
{
    if (rayDirY > 0)
        texture = &data->image.east;
    else
        texture = &data->image.west;
}
    double wallX;
    if (side == 0)
        wallX = data->player.pos_y + perpWallDist * rayDirY;
    else
        wallX = data->player.pos_x + perpWallDist * rayDirX;
    wallX -= floor(wallX);

    // coordonnée X texture
    int texX = (int)(wallX * (double)texture->w);
    if ((side == 0 && rayDirX > 0) || (side == 1 && rayDirY < 0))
        texX = texture->w - texX - 1;

    // dessiner ligne verticale avec texture
    vertical_texture_line(data, x, drawStart, drawEnd, texture, lineHeight, texX);
}

void	handle_movement(t_mlx *data)
{
	double movespeed = 0.08;
	double rotspeed = 0.025;
	if (data->player.up == 1)
	{
		if (data->map.map[(int)(data->player.pos_x + data->player.dir_x * movespeed)][(int)(data->player.pos_y)] != '1')
			data->player.pos_x += data->player.dir_x * movespeed;
		if (data->map.map[(int)(data->player.pos_x)][(int)(data->player.pos_y + data->player.dir_y * movespeed)] != '1')
			data->player.pos_y += data->player.dir_y * movespeed;
	}
	if (data->player.down == 1)
	{
		if (data->map.map[(int)(data->player.pos_x - data->player.dir_x * movespeed)][(int)(data->player.pos_y)] == '0')
			data->player.pos_x -= data->player.dir_x * movespeed;
		if (data->map.map[(int)(data->player.pos_x)][(int)(data->player.pos_y - data->player.dir_y * movespeed)] == '0')
			data->player.pos_y -= data->player.dir_y * movespeed;
	}
	if (data->player.r_right == 1)
	{
		double oldDirX = data->player.dir_x;
		data->player.dir_x = data->player.dir_x * cos(-rotspeed) - data->player.dir_y * sin(-rotspeed);
		data->player.dir_y = oldDirX * sin(-rotspeed) + data->player.dir_y * cos(-rotspeed);

		double oldPlaneX = data->player.plane_x;
		data->player.plane_x = data->player.plane_x * cos(-rotspeed) - data->player.plane_y * sin(-rotspeed);
		data->player.plane_y = oldPlaneX * sin(-rotspeed) + data->player.plane_y * cos(-rotspeed);
	}
	if (data->player.r_left == 1)
	{
		double oldDirX = data->player.dir_x;
		data->player.dir_x = data->player.dir_x * cos(rotspeed) - data->player.dir_y * sin(rotspeed);
		data->player.dir_y = oldDirX * sin(rotspeed) + data->player.dir_y * cos(rotspeed);

		double oldPlaneX = data->player.plane_x;
		data->player.plane_x = data->player.plane_x * cos(rotspeed) - data->player.plane_y * sin(rotspeed);
		data->player.plane_y = oldPlaneX * sin(rotspeed) + data->player.plane_y * cos(rotspeed);
	}
	if (data->player.right == 1)
	{
		if (data->map.map[(int)(data->player.pos_x + data->player.dir_y * (movespeed
				* 2))][(int)data->player.pos_y] != '1')
			data->player.pos_x += data->player.dir_y * movespeed;
		if (data->map.map[(int)data->player.pos_x][(int)(data->player.pos_y - data->player.dir_x
			* (movespeed * 2))] != '1')
			data->player.pos_y -= data->player.dir_x * movespeed;
	}
	if (data->player.left == 1)
	{
		if (data->map.map[(int)(data->player.pos_x - data->player.dir_y * (movespeed
				* 2))][(int)data->player.pos_y] != '1')
			data->player.pos_x -= data->player.dir_y * movespeed;
		if (data->map.map[(int)data->player.pos_x][(int)(data->player.pos_y + data->player.dir_x
			* (movespeed * 2))] != '1')
			data->player.pos_y += data->player.dir_x * movespeed;
	}
}

int	raycasting(t_mlx *data)
{
	int		w = WIN_W;

	f_c(data);
	int x = 0;
	while (x < w)
	{
		get_rays(data, x, w);
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	handle_movement(data);
	mlx_destroy_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, data->map.screen_w, data->map.screen_h);
	if (!data->img)
		return (printf("Error\nImage fail\n"), -1);
	reset_player_move(data);
	return (0);
}
