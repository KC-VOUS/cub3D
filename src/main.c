/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsingh <fsingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 20:13:51 by sdakhlao          #+#    #+#             */
/*   Updated: 2025/08/15 18:24:22 by fsingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

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
	double rayDirX = data->player.dir_x + data->player.plane_y * cameraX;
	double rayDirY = data->player.dir_y + data->player.plane_x * cameraX;
	int mapX = (int)data->player.pos_y;
	int mapY = (int)data->player.pos_x;
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
		sideDistX = (data->player.pos_y - mapX) * deltaDistX;
	}
	else
	{
		stepX = 1;
		sideDistX = (mapX + 1.0 - data->player.pos_y) * deltaDistX;
	}
	if (rayDirY < 0)
	{
		stepY = -1;
		sideDistY = (data->player.pos_x - mapY) * deltaDistY;
	}
	else
	{
		stepY = 1;
		sideDistY = (mapY + 1.0 - data->player.pos_x) * deltaDistY;
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
		if (data->map.map[mapX][mapY] == '1')
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

int	has_xpm(const char *path)
{
	int	len;
	
	if (!path)
		return (0);
	len = ft_strlen(path);
	if (len < 4)
		return (0);
	return (ft_strncmp(path + (len - 4), ".xpm", 4) == 0);
}

void	*check_texture_path(char *path, void *mlx)
{
	int		w;
	int		h;
	void	*img;

	w = 32;
	h = 32;
	if (!has_xpm(path))
		return (NULL);
	img = mlx_xpm_file_to_image(mlx, path, &w, &h);
	if (!img)
		return (NULL);
	return (img);
}

int	check_all_textures(void *mlx, t_mlx *data)
{
	if (!(data->image.north = check_texture_path(data->image.north_path, mlx))
		|| !(data->image.south = check_texture_path(data->image.south_path, mlx))
		|| !(data->image.east = check_texture_path(data->image.east_path, mlx))
		|| !(data->image.west = check_texture_path(data->image.west_path, mlx)))
		return (0);
	return (1);
}

int		init_image(t_mlx *data, t_details *details)
{
	data->image.north_path = ft_strdup(details->north);
	if (!data->image.north_path)
		return (0);
	data->image.south_path = ft_strdup(details->south);
	if (!data->image.south_path)
		return (0);
	data->image.east_path = ft_strdup(details->east);
	if (!data->image.east_path)
		return (0);
	data->image.west_path = ft_strdup(details->west);
	if (!data->image.west_path)
		return (0);
	return (1);
}

int		init_map(t_mlx *data, t_details *details)
{
	data->map.map = NULL;
	data->map.map = dup_map(details->map.map);
	if (!data->map.map)
		return (0);
	data->map.floor_r = details->floor_r;
	data->map.floor_g = details->floor_g;
	data->map.floor_b = details->floor_b;
	data->map.ceiling_r = details->ceiling_r;
	data->map.ceiling_g = details->ceiling_g;
	data->map.ceiling_b = details->ceiling_b;
	data->map.texture_w = 64;
	data->map.texture_h = 64;
	data->map.screen_w = 640;
	data->map.screen_h = 480;
	data->map.width = details->map.width - 1;
	data->map.height = details->map.height - 1;
	return (1);
}

void	fill_plane(t_mlx *data, t_details *details)
{
	double	fov_factor = 0.66;

	data->player.plane_x = -details->dir_y * fov_factor;
	data->player.plane_y = details->dir_x * fov_factor;
}

int		init_data(t_mlx *data, t_details *details)
{
	if (!init_image(data, details))
		return (0);
	if (!init_map(data, details))
		return (0);
	data->player.pos_x = details->player_pos_x;
	data->player.pos_y = details->player_pos_y;
	data->player.dir_x = details->dir_x;
	data->player.dir_y = details->dir_y;
	fill_plane(data, details);
	data->player.time = 0;
	data->player.up = 0;
	data->player.down = 0;
	data->player.left = 0;
	data->player.right = 0;
	data->player.r_left = 0;
	data->player.r_right = 0;
	return (1);
}

void	init_mlx(t_details *details)
{
	t_mlx	data;

	data.x = 13;
	data.y = 12;
	if (!init_data(&data, details))
	{
		free_details(details);
		return;
	}
	free_details(details);
	data.mlx = mlx_init();
	if (!check_all_textures(data.mlx, &data))
	{
		write(2, "Error: Invalid texture file(s)\n", 31);
		free_all(&data);
	}
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
	t_details	details;

	if (argc == 2)
	{
		cp_file(argv[1], &details);
		init_mlx(&details);
	}
	else
	{
		write(2, "Error: Wrong number of arguments\n", 34);
		write(2, "Expected: ./cub3D exemple.cub\n", 31);
		exit(EXIT_SUCCESS);
	}
}
