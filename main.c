/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdakhlao <sdakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 20:13:51 by sdakhlao          #+#    #+#             */
/*   Updated: 2025/07/23 23:38:19 by sdakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	**allocate_map(t_map *map)
{
	int	i;
	int	**nmap;

	nmap = malloc(map->height * sizeof(int *));
	if (!nmap)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		nmap[i] = malloc(map->width * sizeof(int));
		if (!nmap[i])
		{
			while (i > 0)
				free(nmap[--i]);
			free(nmap);
			return (NULL);
		}
		i++;
	}
	return (nmap);
}

void	fill_map(t_map *map)
{
	int temp_map[24][24] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	for (int y = 0; y < map->height; y++)
		for (int x = 0; x < map->width; x++)
			map->map[y][x] = temp_map[y][x];
}

int	init_map(t_mlx *data)
{
	memset(&data->map, 0, sizeof(t_map));
	data->map.width = 24;
	data->map.height = 24;
	data->map.texture_w = 64;
	data->map.texture_h = 64;
	data->map.screen_w = 640;
	data->map.screen_h = 480;
	data->map.map = allocate_map(&data->map);
	if (!data->map.map)
	{
		exit(EXIT_FAILURE);
		return (-1);
	}
	fill_map(&data->map);
	return (0);
}

void	init_player(t_mlx *data)
{
	data->player.pos_x = 22.0;
	data->player.pos_y = 12.0;
	data->player.dir_x = -1.0;
	data->player.dir_y = 0.0;
	data->player.plane_x = 0.0;
	data->player.plane_y = 0.66;
	data->player.time = 0;
	data->player.up = 0;
	data->player.down = 0;
	data->player.left = 0;
	data->player.right = 0;
	data->player.r_left = 0;
	data->player.r_right = 0;
}

int	quit(t_mlx *data)
{
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(EXIT_FAILURE);
}

int	rgb(int r, int g, int b)
{
	return (0 << 24 | r << 16 | g << 8 | b);
}

void	put_pxl(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > WIN_W || y < 0 || y > WIN_H)
	{
		printf("Error\nPixel off limit\n");
		quit(data);
	}
	dst = data->addr + (y * data->size_line + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

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
			put_pxl(data, x, y, rgb(186, 85, 211));
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
			put_pxl(data, x, y, rgb(0, 128, 128));
			x++;
		}
		y--;
	}
}

void	draw(t_mlx *data)
{
	put_pxl(data, data->x, data->y, 0x00FF0000);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

int	key_hook(int key_code, t_mlx *data)
{
	if (key_code == XK_Escape)
		quit(data);
	else if (key_code == XK_w)
	{
		data->y -=1;
		draw(data);
	}
	else if (key_code == XK_a)
	{
		data->x -=1;
		draw(data);
	}
	else if (key_code == XK_s)
	{
		data->y +=1;
		draw(data);
	}
	else if (key_code == XK_d)
	{
		data->x +=1;
		draw(data);
	}
	return (0);
}

void	vertical_line(t_mlx *data, int x, int drawStart, int drawEnd, int color)
{
	if (x > data->map.screen_w || x < 0)
		return ;
	while (drawStart <= drawEnd)
	{
		put_pxl(data, x, drawStart, color);
		drawStart++;
	}
}

void get_rays(t_mlx *data, int x, int w)
{
	int		h = data->map.screen_h;
	double cameraX = 2 * x / (double)w - 1;
	double rayDirX = data->player.dir_x + data->player.plane_x * cameraX;
	double rayDirY = data->player.dir_y + data->player.plane_y * cameraX;
	int mapX = (int)data->player.pos_x;
	int mapY = (int)data->player.pos_y;
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
		sideDistX = (data->player.pos_x - mapX) * deltaDistX;
	}
	else
	{
		stepX = 1;
		sideDistX = (mapX + 1.0 - data->player.pos_x) * deltaDistX;
	}
	if (rayDirY < 0)
	{
		stepY = -1;
		sideDistY = (data->player.pos_y - mapY) * deltaDistY;
	}
	else
	{
		stepY = 1;
		sideDistY = (mapY + 1.0 - data->player.pos_y) * deltaDistY;
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
		if (data->map.map[mapX][mapY] > 0)
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

	int color = 0;

	if (data->map.map[mapX][mapY] == 1)
		color = rgb(255, 0, 0);
	else if (data->map.map[mapX][mapY] == 2)
		color = rgb(0, 255, 0);
	else if (data->map.map[mapX][mapY] == 3)
		color = rgb(0, 0, 255);
	else if (data->map.map[mapX][mapY] == 4)
		color = rgb(255, 255, 255);
	else
		color = rgb(255, 255, 0);
	if (side == 1)
	{
		color -= 15;
	}
	vertical_line(data, x, drawStart, drawEnd, color);
}

void	reset_player_move(t_mlx *data)
{
	data->player.up = 0;
	data->player.down = 0;
	data->player.left = 0;
	data->player.right = 0;
	data->player.r_right = 0;
	data->player.r_left = 0;
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
	mlx_destroy_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, data->map.screen_w, data->map.screen_h);
	if (!data->img)
		return (printf("Error\nImage fail\n"), -1);
	reset_player_move(data);
	return (0);
}

void	init_mlx(void)
{
	t_mlx	data;

	data.x = 13;
	data.y = 12;
	if (init_map(&data) == -1)
		return;
	init_player(&data);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, 640, 480, "cub3D");
	data.img = mlx_new_image(data.mlx, 640, 480);
	data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.size_line, &data.endian);
	mlx_hook(data.win, KeyPress, KeyPressMask, &key_hook, &data);
	mlx_hook(data.win, 17, 0, &quit, &data);
	mlx_loop_hook(data.mlx, raycasting, &data);
	mlx_loop(data.mlx);
}

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		cp_file(argv[1]);
		init_mlx();
	}
	else
	{
		write(2, "Error: Wrong number of arguments\n", 34);
		write(2, "Expected: ./cub3D exemple.cub\n", 31);
		exit(EXIT_SUCCESS);
	}
}
